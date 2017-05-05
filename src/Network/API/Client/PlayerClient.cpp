#include "PlayerClient.h"

PlayerClient::PlayerClient() : m_lock(m_mutex) {
	m_gameStarted.store(false);
	std::cout << "Enter your name:" << std::endl;
	std::string input;
	getline(std::cin, input);
	m_me.m_name = input;
	std::cout << "Hi " << input << " we are now connecting you to the server!" << std::endl;
}

PlayerClient::~PlayerClient() {
	disconnect();
	stop();
}

void PlayerClient::askForId() {
	m_socket.async_send(boost::asio::buffer("i?" + m_me.m_name), boost::bind(&PlayerClient::handleErrors,
																  this,
																  boost::asio::placeholders::error,
																  boost::asio::placeholders::bytes_transferred));
	m_socket.async_receive(boost::asio::buffer(m_buffer), boost::bind(&PlayerClient::parseId,
																	 this,
																	 boost::asio::placeholders::error,
																	 boost::asio::placeholders::bytes_transferred));
}

void PlayerClient::connect(const std::string &host, const std::string &port) {
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

void PlayerClient::startReceiving() {
	m_socket.async_receive(boost::asio::buffer(m_buffer), boost::bind(&PlayerClient::handleData,
																	this,
																	boost::asio::placeholders::error,
																	boost::asio::placeholders::bytes_transferred));
}

void PlayerClient::handleData(ErrorCode &err, size_t trans) {
	if (!err)
	{
		std::string message(m_buffer.data(), m_buffer.data() + trans);
		parseMessage(message);
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}
	startReceiving();
}

void PlayerClient::parseMessage(std::string &input) {
	Message<Transform> newMessage;
	enum class state {
		init,
		getX,
		getY,
		index,
		starting,
		startIndex,
		startName
	};

	size_t index_start = 0;
	float x;
	float y;
	state currSt = state::init;

	Id id = 0;
	std::string name{};
	bool team;

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
				input = input.substr(next);
				currSt = state::getY;
				break;
			}
			case state::getY : {
				if (input[i] == ';') {
					continue;
				}
				size_t next;
				y = std::stof(input.substr(index_start), &next);
				input = input.substr(next + 1);
				newMessage.addTransform(Transform (Vector_Float(x, y)));
				currSt = state::init;
				break;
			}
			case state::starting : {
				if (input[i] == ';' || input[i] == '.') {
					continue;
				}
				if (std::isdigit(input[i]))
					index_start = i;
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
				m_players.push_back(Player(name, id, team));
				currSt = state::starting;
				break;
			}
		}
	}
	newMessage.setValid(true);
	m_lastMessage = std::move(newMessage);
}

void PlayerClient::parseId(ErrorCode &err, size_t trans) {
	if (!err)
	{
		std::string message(m_buffer.data(), m_buffer.data() + trans);
		auto index = message.find(":");
		m_me.m_id = static_cast<Id>(std::stoul(message));
		m_me.m_team = static_cast<bool>(std::stoul(message.substr(index + 1)));
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}

}

void PlayerClient::sendData(const MovementInputHolder &inputHolder) {
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

void PlayerClient::send(const std::string &input) {
	std::string message {std::to_string(m_me.m_id) + "_" + input};
	m_socket.async_send(boost::asio::buffer(message.data(), message.size()), boost::bind(&PlayerClient::handleErrors,
															   this,
															   boost::asio::placeholders::error,
															   boost::asio::placeholders::bytes_transferred));
}

void PlayerClient::handleErrors( ErrorCode &error, std::size_t bytes_transferred )
{
	if ( error ) {
		std::cerr << "Client error: " << error.message() << "bytes transferred: " << bytes_transferred  << ", exiting" << std::endl;
		std::exit( 1 );
	}
}

void PlayerClient::disconnect() {
	send("end");
}

const std::vector<Player> &PlayerClient::getPlayers() const {
	return m_players;
}

const Player &PlayerClient::getMe() const {
	return m_me;
}

Message<Transform> &PlayerClient::getMessage() {
	m_lock.lock();
	return m_lastMessage;
}

void PlayerClient::releaseMessage() {
	m_lastMessage.setValid(false);
	m_lock.unlock();
}


bool PlayerClient::hasStarted() const {
	return m_gameStarted.load();
}

