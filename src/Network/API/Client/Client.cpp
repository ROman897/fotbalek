#include "Client.h"

Client::Client() /*: m_myCounter(0), m_serverCounter(0)*/ {
	m_gameStarted.store(false);
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
		std::string message(m_buffer.begin(), m_buffer.begin() + trans);
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
		end2
	};
	std::cout << input << std::endl;
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
	try {
		for (size_t i = 0; i < input.size(); ++i) {
			switch (currSt) {
				case state::init : {
					if (std::isdigit(input[i])) {
						index_start = i;
						currSt = state::index;
					} else if (input[i] == '.') {
						continue;
					} else if (input[i] == 's') {
						currSt = state::starting;
					} else if (input[i] == 'e') {
						currSt = state::end1;
						++i;
					} else {
						std::cerr << "wrong message was received" << std::endl;
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
						currSt = state::getX;
						index_start = i + 1;
					}
					break;
				}
				case state::getX : {
					size_t next;
					x = std::stof(input.substr(index_start), &next);
					i = next;
					currSt = state::getY;
					break;
				}
				case state::getY : {
					if (input[i] == ';') {
						continue;
					}
					size_t next;
					y = std::stof(input.substr(index_start), &next);
					i = next;
					newMessage.addTransform(Transform(Vector_Float(x, y)));
					currSt = state::init;
					break;
				}
				case state::starting : {
					if (input[i] == ';' || input[i] == '.') {
						continue;
					}
					started = true;
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
					team = input[i + 1];
					std::lock_guard<std::mutex> players_lock (m_playersMutex);
					m_players.push_back(Player(name, id, team));
					currSt = state::starting;
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
					if (input[i] != ':')
						continue;
					falseTeam = static_cast<unsigned>(std::stoul(input.substr(index_start, i - index_start)));
					//print results
					break;
				}
			}
		}
		m_gameStarted.store(started);
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		std::cout << "zparsoval som msg" << std::endl;
	}
	newMessage.setValid(true);//vyriesit messageID
	std::lock_guard<std::mutex> message_lock (m_messageMutex);
	m_lastMessage = std::move(newMessage);
	std::cout << "move-ol som msg" << std::endl;
}

void Client::parseId(ErrorCode &err, size_t trans) {
	if (!err)
	{
		std::string message(m_buffer.begin(), m_buffer.begin() + trans);
		auto index = message.find(":");
		std::cout << "msg: " << message << " index: " << index << std::endl;
		try {
			m_me.m_id = static_cast<Id>(std::stoul(message));
			m_me.m_team = static_cast<bool>(std::stoul(message.substr(index + 1)));
		}catch (std::exception &ex) {
			std::cerr << "parseId failed : " << ex.what() << std::endl;
		}
		std::cout << "received id: " << m_me.m_id  << "team: " << m_me.m_team << std::endl;
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
