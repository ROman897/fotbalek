#include "UdpServer.h"
#include <boost/bind.hpp>
#include <iostream> //potom prec
#include <functional>
#include <cmath>

void UdpServer::listen() {
    m_socket.async_receive_from(boost::asio::buffer(m_buffer),
                               m_pending,
                               boost::bind(&UdpServer::handleRequest,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleRequest(const boost::system::error_code& error, size_t transferred) {
    if (transferred > BUFFER_LEN) { //je to nutne? co to ma robit?
        listen();
        return;
    }
    if (error) {
        if (error == boost::asio::error::eof) {
            for (auto &i : m_clients) {
                if (i && endptEq(m_pending, i->m_endpt)) {
                    abandonClient(i->baseInfo.m_id);
                    return;
                }
            }
        }
		std::cerr << "UdpServer::handleRequest:" << error.message();
        //std::cerr << "vyplo ta\n";
        //std::exit(1); client sa pri chybe neukonci tak som to zakomentoval aj tu
    }
	std::string message(m_buffer.data(), m_buffer.data() + transferred);
	//debug
    std::cout << "received: " << transferred << " msg: " << message << " from: " << m_pending.address() << std::endl;

    parseInput(message, transferred);
    listen();
}

void UdpServer::respond(const udp::endpoint &cl, const std::string &response) {
    std::cout << "sending to " << cl.address() << ":" << cl.port() << '\n';
    m_socket.async_send_to(boost::asio::buffer(response),
                          cl,
                          boost::bind(&UdpServer::responseHandler,
                                      this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}

void UdpServer::respondAll(const std::string &response) {
    for (auto &i : m_clients) {
        if (i)
            respond(i->m_endpt, response);
    }
}

void UdpServer::init() {
    listen();
    //dispatch();
}

void UdpServer::responseHandler(const boost::system::error_code &err, size_t trans) {
	if ( err ) {
		std::cerr << "Client error: " << err.message() << "bytes transferred: " << trans  << ", exiting\n";
		std::exit( 1 );
	}
}

void UdpServer::emplaceClient(udp::endpoint endpt, size_t trans) {
    if (m_clientNr >= MAX_PLAYERCOUNT) {
        respond(endpt, {"full\n"});
        return;
    }

    //poslat mu jeho index a indexy vsetkych aj s menami + vsetkym ostatnym jeho meno a index
    std::string newName(&m_buffer[2], &m_buffer[trans]);
    unsigned short viable_index = MAX_PLAYERCOUNT - 1;
    for (unsigned i = 0; i < MAX_PLAYERCOUNT; ++i) {
        if (!m_clients[i] && viable_index == MAX_PLAYERCOUNT - 1)
            viable_index = i;
        if (m_clients[i] && endptEq(m_clients[i]->m_endpt, endpt)) {
            respond(endpt, {"you've already logged in\n"});
            return;
        }
    }

    for (auto &i : m_clients) {
        if (i && i->baseInfo.m_name == newName) {
            respond(endpt, "A player with that name is already present\n");
            return;
        }
    }
    m_clients[viable_index] = std::make_unique<Client>(std::move(endpt), std::move(newName), viable_index);
    std::cout << "new guy's name: " << m_clients[viable_index]->baseInfo.m_name << std::endl;
    ++m_clientNr;
    std::cout << "port: " << m_clients[viable_index]->m_endpt.port() << '\n'; //prerob aby to bolo id:[1/0] podla toho v akom je to teame zapisane ako 0 alebo 1
    /*respond(m_clients[viable_index]->m_endpt, {std::string("you got a new index: ") +            ^
                                              std::to_string(viable_index) +                       ^
										  	  "\n"});											   ^*/
	respond(m_clients[viable_index]->m_endpt, { std::to_string(viable_index) + ":1"}); //prerobit viz vyssie
}

//void UdpServer::abandonClient(unsigned short client_index) {
void UdpServer::abandonClient(size_t client_index) {
    m_clients[client_index] = nullptr;
    --m_clientNr;
    std::cout << "client " << client_index << " has disconnected\n";
}

//void UdpServer::parseInput(size_t length) {
void UdpServer::parseInput(const std::string &message, size_t length) {
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
            //if (std::isdigit(m_buffer[i])) {
			if (std::isdigit(message[i])) {
                index_start = i;
                currSt = state::ind;
            //} else if (m_buffer[i] == 'i') {
			} else if (message[i] == 'i') {
                currSt = state::new_pl;
            //} else if (m_buffer[i] == 'e') {
			} else if (message[i] == 'e') {
                currSt = state::discnct_1;
            } else {
                return;
            }
            break;
        }
        case state::new_pl : {
            //if (m_buffer[i] == '?' && length > 2)
			if (message[i] == '?' && length > 2)
                emplaceClient(m_pending, length);
            return;
        }
        case state::ind : {
            if (std::isdigit(message[i]))
                continue;
            if (message[i] == '_') {
                //index = indexFromBuffer(index_start, i - 1);
				index = static_cast<size_t>(std::stol(message.substr(index_start, i - index_start)));
                if (!m_clients[index] || !endptEq(m_pending, m_clients[index]->m_endpt))
                    return;
                //m_clients[index]->swapBuffers(m_buffer);
                //m_clients[index]->setNewData(true);
                //m_clients[index]->data()[length] = '\0'; // <<< mozno nebude treba, este zistit ako sa bude spravat
                std::cout << "client " << index << " sent " << message;
				/*for (size_t j = 0; j < length; ++j) {
					std::cout << m_clients[index]->data()[j];
				}*/
                std::cout << std::endl << "port: " << m_clients[index]->m_endpt.port() << '\n';
				parseMessage(index, message.substr(2));
                //respond(m_clients[index]->m_endpt, "jaaaaaaaaj ty kkt");
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
            //for (auto &i : m_clients) {
			for (auto &client : m_clients) {
                if (i && endptEq(client->m_endpt, m_pending)) {
                    //abandonClient(i->m_index);
					abandonClient(client->baseInfo.m_id);
                    return;
                }
            }
            return;
        }
        }
    }
}

void UdpServer::parseMessage(Id index, const std::string &message) {
	std::lock_guard<std::mutex> lock(m_mutex);
	MovementInputHolder newMovement;
	for (auto i : message) {
		switch (i) {
			case 'u': {
				newMovement.moveUp = true;
				newMovement.moveVertical = true;
			}
			case 'd': {
				newMovement.moveUp = false;
				newMovement.moveVertical = true;
			}
			case 'l': {
				newMovement.moveRight = false;
				newMovement.moveHorizontal = true;
			}
			case 'r': {
				newMovement.moveRight = true;
				newMovement.moveHorizontal = true;
			}
			default:
				break;
		}
	}
	newMovement.valid = true;
	m_message.addTransform(newMovement);
	m_message.addNetworkId(NetworkId(index));
}

/*size_t UdpServer::indexFromBuffer(int start, int end) {
    unsigned pow = 0;
    size_t res = 0;

    for (int i = end; i >= start; --i) {
        res += (m_buffer[i] - '0') * std::pow(10, pow);
        ++pow;
    }
    return res;
}*/

bool UdpServer::endptEq(const udp::endpoint &a, const udp::endpoint &b) const {
    return a.address() == b.address();
}

std::vector<Player> UdpServer::getPlayers() const {
    std::vector<Player> result;
	for (const auto &i : m_clients) {
        result.push_back(i->baseInfo);
    }
	return result;
}

Message<MovementInputHolder> &UdpServer::getMessage() {
	m_lock.lock();
	return m_message;
}

void UdpServer::releaseMessage() {
	m_message.setValid(false);
	m_lock.unlock();
}

/*
const boost::array<char, 128> &UdpServer::Client::data() const {
    return m_buffer; // rozmyslet ako s tread-safety
}

boost::array<char, 128> &UdpServer::Client::data() {
    return m_buffer; // rozmyslet ako s tread-safety
}

bool UdpServer::Client::newData() const {
    std::unique_lock<std::mutex> lk(m_lk);
    bool res = m_newData;
    lk.unlock();
    //m_alarm.notify_all();
    return res;
}

void UdpServer::Client::setNewData(bool val) {
    std::unique_lock<std::mutex> lk(m_lk);
    m_newData = val;
    lk.unlock();
    m_alarm.notify_all();
}

void UdpServer::Client::swapBuffers(boost::array<char, BUFFER_LEN> &other) {
    std::unique_lock<std::mutex> lk(m_lk);
    std::swap(m_buffer, other);
    lk.unlock();
    m_alarm.notify_all();
}
*/
