#ifndef PV264_PROJECT_PLAYER_CLIENT_H
#define PV264_PROJECT_PLAYER_CLIENT_H

#include <boost/bind.hpp>
#include <iostream>
#include <cstdlib>
#include <mutex>

#include "UdpBase.h"
#include "Player.h"
#include "Message.h"
#include "../../../Components/Logic/MovementInputHolder.h"
#include "../../../Components/Network/NetworkId.h"
#include "../../../Components/Transform.h"
#include "Score.h"

class Client : UdpBase {

	std::atomic_bool m_gameStarted;
	udp::endpoint m_serverEnd;
	Player m_me;
	Message<Transform> m_lastMessage;
public:
	mutable std::mutex m_messageMutex;
	mutable std::mutex m_playersMutex;
	mutable std::mutex m_scoreMutex;
private:
	std::vector<Player> m_players;
	Score m_score;
	bool hasId = false;
	std::atomic_bool m_gameEnded;
	/*uint64_t m_myCounter;
	uint64_t m_serverCounter;*/

	void startReceiving();

	void handleData(ErrorCode &err, size_t trans);

	void parseId(ErrorCode &err, size_t trans);

	void parseMessage(std::string &message);

	void send(const std::string &input);

	void handleErrors(ErrorCode &error, std::size_t bytes_transferred );

	void askForId();

	void disconnect();


public:

	Client();

	~Client();

	void connect( const std::string &host, const std::string &port);

	void sendData(const MovementInputHolder& inputHolder);

	const std::vector<Player> &getPlayers();

	const Player &getMe() const;

	Message<Transform> &getMessage();

	bool hasStarted() const;

	const Score &getScore() const;

	bool hasEnded() const;

};

#endif //PV264_PROJECT_PLAYER_CLIENT_H
