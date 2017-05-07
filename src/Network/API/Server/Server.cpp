#include "Server.h"

Server::Server() : m_gameStarted(false) {
    std::lock_guard<std::mutex> playersLock(m_playersMutex);
    m_clients.resize(ServerGameConstants::kMaxNumberOfPlayers);
    m_socket.bind(udp::endpoint(udp::v4(), ServerGameConstants::portNumber));

}
Server::~Server() {
    respondAll("disconnect");
    stop();
}

void Server::listen() {
    //std::cout << "listen()\n";
    m_socket.async_receive_from(boost::asio::buffer(m_buffer),
                               m_pending,
                               boost::bind(&Server::handleRequest,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void Server::handleRequest(ErrorCode &error, size_t transferred) {
    if (error) {
        if (error == boost::asio::error::eof) {
            for (auto &i : m_clients) {
                if (i && endpointEq(m_pending, i->m_endpoint)) {
                    abandonClient(i->baseInfo.m_id);
                    return;
                }
            }
        }
        std::cerr << "Server::handleRequest:" << error.message();
    }
    std::string message(m_buffer.begin(), m_buffer.begin() + transferred);

    //test
    //std::cout << "received: " << transferred << " msg: " << message << " from: " << m_pending.address() << std::endl;

    parseInput(message, transferred);
    listen();
}

void Server::sendData(const std::vector<NetworkId> &ids, const std::vector<Transform> &transforms) {
    std::string message{};
    for (size_t i = 0; i < ids.size(); ++i) {
        const auto &position = transforms[i].m_position;
        message += std::to_string(ids[i].id) + "_" + std::to_string(position.m_x) + ";" + std::to_string(position.m_y) + ",";
    }
    respondAll(message);
}

void Server::respondAll(const std::string &response) {
    for (auto &i : m_clients) {
        if (i)
            respond(i->m_endpoint, response);
    }
}

void Server::respond(const udp::endpoint &cl, const std::string &response) {
    //std::lock_guard<std::mutex> lk(m_sktMtx);  na co to tu je?
    //std::cout << "sending to " << cl.address() << ":" << cl.port() << "msg: " << response << '\n';
    m_socket.async_send_to(boost::asio::buffer(response), cl,
                           boost::bind(&Server::handleErrors,
                                      this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}

void Server::init() {
    listen();
}

void Server::handleErrors(ErrorCode &err, size_t trans) {
    if ( err ) {
        std::cerr << "Client error: " << err.message() << "bytes transferred: " << trans  << ", exiting" << std::endl;
        std::exit( 1 );
    }
}

void Server::emplaceClient(udp::endpoint endpoint, size_t trans) {
    if (m_clientNr >= ServerGameConstants::kMaxNumberOfPlayers) {
        respond(endpoint, {"full\n"});
        return;
    }

    std::string newName(&m_buffer[2], &m_buffer[trans]);
    unsigned short viable_index = ServerGameConstants::kMaxNumberOfPlayers - 1;
    for (unsigned short i = 0; i < ServerGameConstants::kMaxNumberOfPlayers; ++i) {
        if (!m_clients[i] && viable_index == ServerGameConstants::kMaxNumberOfPlayers - 1)
            viable_index = i;
        if (m_clients[i] && endpointEq(m_clients[i]->m_endpoint, endpoint)) {
            respond(endpoint, {"you've already logged in\n"});
            return;
        }
    }

    for (auto &client : m_clients) {
        if (client && client->baseInfo.m_name == newName) {
            respond(endpoint, "A player with that name is already present\n");
            return;
        }
    }
    m_clients[viable_index] = std::make_unique<Client>(std::move(endpoint), std::move(newName), viable_index + 1);
	m_clients[viable_index]->baseInfo.m_team = m_clientNr >= ServerGameConstants::kMaxNumberOfPlayers / 2;

    //test
    std::cout << "new guy's name: " << m_clients[viable_index]->baseInfo.m_name << " id: " << m_clients[viable_index]->baseInfo.m_id <<std::endl;

    ++m_clientNr;
    int team = m_clients[viable_index]->baseInfo.m_team;

    //test
    std::cout << "port: " << m_clients[viable_index]->m_endpoint.port() << '\n';

    respond(m_clients[viable_index]->m_endpoint, { std::to_string(viable_index + 1) + ":" + std::to_string(team)});
    if (m_clientNr == ServerGameConstants::kMaxNumberOfPlayers) {
		std::cout << "starting game" << std::endl;
        std::string startMessage("s;");
        for (auto &client : m_clients) {
            startMessage += client ? std::to_string(client->baseInfo.m_id) +
                                "_" + client->baseInfo.m_name +
                                "_" + (client->baseInfo.m_team ? "1" : "0") + "."
                              : ""; // <<< should not happen
        }
        std::cout << "startMessage: " << startMessage << std::endl;
		for (size_t j = 0; j < 10; ++j) {
			respondAll(startMessage);
		}
        m_gameStarted.store(true);
    }
}


void Server::abandonClient(size_t client_index) {
    m_clients[client_index - 1] = nullptr;
    --m_clientNr;
    std::cout << "client " << client_index << " has disconnected\n";
}

void Server::parseInput(const std::string &message, size_t length) {
    enum class state {
        init,
        new_pl,
        ind,
        discnct_1,
        discnct_2
    };

    size_t index = 0;
    size_t index_start = 0;
    state currSt = state::init;
    for (size_t i = 0; i < length; ++i) {
        switch (currSt) {
			case state::init : {
				if (std::isdigit(message[i])) {
					index_start = i;
					currSt = state::ind;
				} else if (message[i] == 'i') {
					currSt = state::new_pl;
				} else if (message[i] == 'e') {
					currSt = state::discnct_1;
				} else {
					return;
				}
				break;
			}
			case state::new_pl : {
				if (message[i] == '?' && length > 2)
					emplaceClient(m_pending, length);
				return;
			}
			case state::ind : {
				if (std::isdigit(message[i]))
					continue;
				if (message[i] == '_') {
					index = static_cast<size_t>(std::stol(message.substr(index_start, i - index_start)));
					if (!m_clients[index - 1] || !endpointEq(m_pending, m_clients[index - 1]->m_endpoint))
						return;
					//test
					//std::cout << "client " << index << " sent " << message;
					//std::cout << std::endl << "port: " << m_clients[index - 1]->m_endpoint.port() << '\n';
					parseMessage(index, message.substr(2));
				}
				return;
			}
			case state::discnct_1 : {
				if (message[i] != 'n')
					return;
				currSt = state::discnct_2;
				break;
			}
			case state::discnct_2 : {
				if (message[i] != 'd')
					return;
				for (auto &client : m_clients) {
					if (client && endpointEq(client->m_endpoint, m_pending)) {
						abandonClient(client->baseInfo.m_id);
						return;
					}
				}
				return;
			}
        }
    }
}

void Server::parseMessage(Id index, const std::string &message) {
    //std::lock_guard<std::mutex> lock(m_mutex);
    std::lock_guard<std::mutex> messageGuard(m_messageMutex);
    MovementInputHolder newMovement;
    //std::cout << "received movement !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    for (auto i : message) {
        switch (i) {
            case 'u': {
                newMovement.moveUp = true;
                newMovement.moveVertical = true;
                break;
            }
            case 'd': {
                newMovement.moveUp = false;
                newMovement.moveVertical = true;
                break;
            }
            case 'l': {
                newMovement.moveRight = false;
                newMovement.moveHorizontal = true;
                break;
            }
            case 'r': {
                newMovement.moveRight = true;
                newMovement.moveHorizontal = true;
                break;
            }
            default:
                break;
        }
    }
    //newMovement.valid = true;
    m_message.setValid(true);
    m_message.addTransform(newMovement);
    m_message.addNetworkId(NetworkId(index));
}

bool Server::endpointEq(const udp::endpoint &a, const udp::endpoint &b) const {
    return a.address() == b.address();
}

std::vector<Player> Server::getPlayers() const {
    std::vector<Player> result;
    for (const auto &client : m_clients) {
        if (client)
            result.push_back(client->baseInfo);
    }
    return result;
}

Message<MovementInputHolder> &Server::getMessage() {
    return m_message;
}


bool Server::hasStarted() const {
    return m_gameStarted.load();
}

void Server::gameOver(int team1, int team2) {
	std::string message {"e;"};
	message += std::to_string(team1) + ":" + std::to_string(team2);
	respondAll(message);
}

void Server::sendStateChange(const GameStateChange &stateChange) {
    std::string message{"c;"};
	if (stateChange.m_GameOver) {
		message += "g";
	}
	if (stateChange.m_Team1Scored) {
		message += "1";
	}
	if (stateChange.m_Team2Scored) {
		message += "2";
	}
	respondAll(message);
}
