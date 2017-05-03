#ifndef PV264_PROJECT_PLAYER_CLIENT_H
#define PV264_PROJECT_PLAYER_CLIENT_H

#define MAX_OBJECTCOUNT 7

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <deque>
#include <vector>
#include <queue>

#include "UdpBase.h"
#include "Player.h"
#include "Message.h"
//#include "../../../Vector2.h"

class PlayerClient : UdpBase {
	using udp = boost::asio::ip::udp;
	using ErrorCode = const boost::system::error_code;

	//std::function<navratovy typ(argumenty)
	std::function<void()> gameStarted;
	udp::endpoint m_serverEnd;
	Player m_me;
	//pridat ID sprav a counter
	Message m_lastMessage;
	std::vector<Player> m_players;

public:

	PlayerClient();

	~PlayerClient();

	void connect( const std::string &host, const std::string &port);

	void startReceiving();

	void handleData(ErrorCode &err, size_t trans);

	void parseId(ErrorCode &err, size_t trans);

	void parseMessage(const std::string &message) {

	}

	void sendData(/*const NetworkId& id, const MovementInputHolder& inputHolder*/);

	void startSending(const std::string &input);

	void handleErrors(ErrorCode &error, std::size_t bytes_transferred );

	void askForId();

	void disconnect();

	const std::vector<Player> &getPlayers() const;

	const Player &getMe() const;

};

#endif //PV264_PROJECT_PLAYER_CLIENT_H
