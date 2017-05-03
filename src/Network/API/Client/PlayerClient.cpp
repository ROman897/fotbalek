#include "PlayerClient.h"

PlayerClient::PlayerClient() {
	std::cout << "Enter your name:" << std::endl;
	std::string input;
	getline(std::cin, input);
	m_me.name = input;
	std::cout << "Hi " << input << " we are now connecting you to the server!" << std::endl;
}

PlayerClient::~PlayerClient() {
	stop();
}

int main( int argc, char **argv ) {
	if ( argc != 3 ) {
		std::cerr << "Invalid number of arguments passed\n"
				  << "usage: fotbalek host port \n";  //upravit mozno na 13000 defaultne
		return 1;
	}
	PlayerClient player;
	player.connect(argv[1], argv[2]);
	player.disconnect();
	return 0;
}

void PlayerClient::askForId() {
	m_socket.async_send(boost::asio::buffer("i?" + m_me.name), boost::bind(&PlayerClient::handleErrors,
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

	//na testovanie
	while (true) {
		std::string line;
		getline(std::cin, line);
		if (line.compare("quit") == 0) {
			break;
		} else {
			startSending(line);
		}
	}
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
		std::cout << "hej nieco doslo " << message << " velkosti:" << trans << std::endl;
		parseMessage(message);
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}
	startReceiving();
}

void PlayerClient::parseMessage(const std::string &message) {
	Message newMessage;
	//rozparsuj spravu
}


void PlayerClient::parseId(ErrorCode &err, size_t trans) {
	if (!err)
	{
		std::string message(m_buffer.data(), m_buffer.data() + trans);
		auto index = message.find(":");
		m_me.id = static_cast<uint8_t>(std::stoul(message.substr(index + 1)));
		std::cout << "dosla ti odpoved na i? " << message << " velkosti:" << trans << std::endl;
	}
	else
	{
		std::cerr << "NetworkClient::handle_receive:" << err.message();
	}

}

void PlayerClient::sendData(const NetworkId& id, const MovementInputHolder& inputHolder) {
	//vytvor spravu a zavolaj startSending
}

void PlayerClient::startSending(const std::string &input) {
	using namespace std::placeholders;
	std::cout << "nieco posielam" << std::endl;
	std::string message {std::to_string(m_me.id) + "_" + input + "."};
	m_socket.async_send(boost::asio::buffer(message.data(), message.size()), boost::bind(&PlayerClient::handleErrors,
															   this,
															   boost::asio::placeholders::error,
															   boost::asio::placeholders::bytes_transferred));
}

void PlayerClient::handleErrors( ErrorCode &error, std::size_t bytes_transferred )
{
	if ( error ) {
		std::cerr << "Client error: " << error.message() << "bytes transfered: " << bytes_transferred  << ", exiting\n";
		std::exit( 1 );
	}
}

void PlayerClient::disconnect() {
	startSending("disconnecting");
	stop();
}

const std::vector<Player> &PlayerClient::getPlayers() const {
	return m_players;
}

const Player &PlayerClient::getMe() const {
	return m_me;
}
