#include "Client.h"

Client::Client() {
	m_gameStarted.store(false);
	m_gameEnded.store(false);
	m_stateChanged.store(false);
	std::cout << "Enter your name:" << std::endl;
	std::string input;
	getline(std::cin, input);
	m_me.m_name = input;
	std::cout << "Hi " << input << " we are now connecting you to the server!" << std::endl;
}

Client::~Client() {
	disconnect();
	stop();
}

void Client::askForId() {
    std::cout << "askForId()\n";
	m_socket.async_send(boost::asio::buffer("i?" + m_me.m_name), boost::bind(&Client::handleErrors,
																  this,
																  boost::asio::placeholders::error,
																  boost::asio::placeholders::bytes_transferred));
	m_socket.async_receive(boost::asio::buffer(m_buffer), boost::bind(&Client::parseId,
																	 this,
																	 boost::asio::placeholders::error,
																	 boost::asio::placeholders::bytes_transferred));
}

void Client::connect(const std::string &host, const std::string &port) {
	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), host, port);
	m_serverEnd = *resolver.resolve(query);
	try {
		m_socket.connect( m_serverEnd );
		std::cout << "connected" << std::endl;
		askForId();
	} catch ( std::exception &ex ) {
		std::cerr << "connection error: " << ex.what() << std::endl;
		throw;
	}
	while (!hasId) {
		sleep(1);
	}
	startReceiving();
}

void Client::startReceiving() {
	m_socket.async_receive(boost::asio::buffer(m_buffer), boost::bind(&Client::handleData,
																	this,
																	boost::asio::placeholders::error,
																	boost::asio::placeholders::bytes_transferred));
}

void Client::handleData(ErrorCode &err, size_t trans) {
	if (!err)
	{
        std::lock_guard<std::mutex> message_lock (m_messageMutex);
		std::string message(m_buffer.begin(), trans);
		parseMessage(message);
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}
	startReceiving();
}

void Client::parseMessage(std::string &input) {
	Message<Transform> newMessage;
	enum class state {
		init,
		getX,
		getY,
		index,
		starting,
		startIndex,
		startName,
		end1,
		end2,
		stateChange
	};

	size_t index_start = 0;
	float x;
	float y;
	state currSt = state::init;

	Id id = 0;
	std::string name{};
	bool team;
	unsigned trueTeam = 0;
	unsigned falseTeam = 0;
	bool started = false;
	for (size_t i = 0; i < input.size(); ++i) {
		switch (currSt) {
			case state::init : {
				if (std::isdigit(input[i])) {
					index_start = i;
					currSt = state::index;
				} else if (input[i] == '.' || input[i] == ',') {
					continue;
				} else if (input[i] == 's') {
					if (m_gameStarted.load()) {
						return;
					}
					currSt = state::starting;
					started = true;
				} else if (input[i] == 'e') {
					currSt = state::end1;
					++i;
				} else if (input[i] == 'c') {
					currSt = state::stateChange;
					++i;
				} else {
					std::cerr << "wrong message was received" << std::endl;
					std::cerr << "message was: " << input << " i = " << i << " char: " << input[i] << std::endl;
					return;
				}
				break;
			}
			case state::index : {
				if (std::isdigit(input[i]))
					continue;
				if (input[i] == '_') {
					NetworkId newId;
					newId.id = std::stoul(input.substr(index_start, i - index_start));;
					newMessage.addNetworkId(newId);
					currSt = state::getX;;
				}
				break;
			}
			case state::getX : {
				size_t next;
				x = std::stof(input.substr(i), &next);
				i += next;
				currSt = state::getY;
				break;
			}
			case state::getY : {
				if (input[i] == ';') {
					continue;
				}
				size_t next;
				y = std::stof(input.substr(i), &next);
				i += next;
				newMessage.addTransform(Transform(Vector_Float(x, y)));
				currSt = state::init;
				break;
			}
			case state::starting : {
				if (input[i] == ';' || input[i] == '.') {
					continue;
				}
				std::cout << "starting:msg: " << input << std::endl;
				if (std::isdigit(input[i]))
					index_start = i;
				currSt = state::startIndex;
				break;
			}
			case state::startIndex : {
				if (std::isdigit(input[i]))
					continue;
				if (input[i] == '_') {
					id = std::stoul(input.substr(index_start, i - index_start));
					index_start = i + 1;
					currSt = state::startName;
				}
				break;
			}
			case state::startName : {
				if (input[i] != '_')
					continue;
				name = input.substr(index_start, i - index_start);
				team = input[i + 1] == '1';
				std::lock_guard<std::mutex> players_lock (m_playersMutex);
				m_players.push_back(Player(name, id, team));
				currSt = state::starting;
				++i;
				break;
			}
			case state::end1 : {
				if (input[i] != ':')
					continue;
				trueTeam = static_cast<unsigned>(std::stoul(input.substr(2, i - 2)));
				index_start = i + 1;
				currSt = state::end2;
				break;
			}
			case state::end2 : {
				falseTeam = static_cast<unsigned>(std::stoul(input.substr(index_start, i - index_start)));
				std::lock_guard<std::mutex> scoreLock (m_scoreMutex);
				m_score = Score(trueTeam, falseTeam);
				m_gameEnded.store(true);
				break;
			}
			case state::stateChange : {
				GameStateChange newState;
				if (input[i] == 'g') {
					newState.m_GameOver = true;
				}
				if (input[i] == '1') {
					newState.m_Team1Scored = true;
				}
				if (input[i] == '2') {
					newState.m_Team2Scored = true;
				}
				std::lock_guard<std::mutex> stateLock (m_stateChangeMutex);
				m_stateChanged.store(true);
				m_state = std::move(newState);
			}
		}
	}
	if (!m_gameStarted.load()) {
		m_gameStarted.store(started);
	}
	newMessage.setValid(true);//vyriesit messageID
	m_lastMessage = std::move(newMessage);
}

void Client::parseId(ErrorCode &err, size_t trans) {
	if (!err)
	{
		std::string message(m_buffer.begin(), trans);
		auto index = message.find(":");
		try {
			m_me.m_id = static_cast<Id>(std::stoul(message));
			m_me.m_team = static_cast<bool>(std::stoul(message.substr(index + 1)));
		}catch (std::exception &ex) {
			std::cerr << "parseId() failed: " << ex.what() << std::endl;
		}
		std::cout << "received id: " << m_me.m_id  << "team: " << m_me.m_team << std::endl;
		hasId = true;
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}

}

void Client::sendData(const MovementInputHolder &inputHolder) {
	std::string message {};
	if (inputHolder.moveHorizontal) {
		if (inputHolder.moveRight) {
			message += "r";
		} else {
			message += "l";
		}
	}
	if (inputHolder.moveVertical) {
		if (inputHolder.moveUp) {
			message += "u";
		} else {
			message += "d";
		}
	}
	message += ".";
	send(message);
}

void Client::send(const std::string &input) {
	std::string message {std::to_string(m_me.m_id) + "_" + input};
	m_socket.async_send(boost::asio::buffer(message.data(), message.size()), boost::bind(&Client::handleErrors,
															   this,
															   boost::asio::placeholders::error,
															   boost::asio::placeholders::bytes_transferred));
}

void Client::handleErrors( ErrorCode &error, std::size_t bytes_transferred )
{
	if ( error ) {
		std::cerr << "Client error: " << error.message() << "bytes transferred: " << bytes_transferred  << ", exiting" << std::endl;
		std::exit( 1 );
	}
}

void Client::disconnect() {
	send("end");
}

const std::vector<Player> &Client::getPlayers() {
	return m_players;
}

const Player &Client::getMe() const {
	return m_me;
}

Message<Transform> &Client::getMessage() {
	return m_lastMessage;
}

bool Client::hasStarted() const {
	return m_gameStarted.load();
}

const Score &Client::getScore() const {
	return m_score;
}

bool Client::hasEnded() const {
	return m_gameEnded.load();
}

bool Client::hasStateChanged() const {
	return m_stateChanged.load();
}

const GameStateChange &Client::getState() const {
	return m_state;
}

void Client::resetStateChanged() {
	m_stateChanged.store(false);
}

void Client::resetState() {
	m_state.m_GameOver = false;
	m_state.m_Team1Scored = false;
	m_state.m_Team2Scored = false;
}
