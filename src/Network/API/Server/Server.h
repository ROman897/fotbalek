#ifndef UDPSERVER
#define UDPSERVER

#include <boost/bind.hpp>
#include <memory>
#include <mutex>
#include "../Client/UdpBase.h"
#include "../Client/Player.h"
#include "../../../Utils/Declarations.h"
#include "../../../Components/Logic/MovementInputHolder.h"
#include "../Client/Message.h"
#include "../../../Constants/ServerGameConstants.h"
#include "../../../Components/Transform.h"
#include "../../../Components/Network/GameStateChange.h"

class Server : UdpBase {

	struct Client {
        Client(udp::endpoint &&endpoint, const std::string &name, Id index) : m_endpoint(endpoint), baseInfo(name, index) {}

        const udp::endpoint m_endpoint;
		Player baseInfo;
        Id lastMessage;
    };

	std::atomic_bool m_gameStarted;
    udp::endpoint m_pending;
    std::vector<std::unique_ptr<Client>> m_clients;
    unsigned short m_clientNr = 0;
	Message<MovementInputHolder> m_message;

    void listen();


	void handleRequest(ErrorCode &error, size_t transferred);

    void respond(const udp::endpoint &cl, const std::string &response);

    void respondAll(const std::string &response);

    void emplaceClient(udp::endpoint endpt, size_t trans);

	void handleErrors(ErrorCode &err, size_t trans);

    void abandonClient(size_t client_index); //index as stored in struct Player

	void parseInput(const std::string &message, size_t length);

	void parseMessage(size_t index, const std::string &message);

    bool endpointEq(const udp::endpoint &a, const udp::endpoint &b) const;

public:

    mutable std::mutex m_messageMutex;
    mutable std::mutex m_playersMutex;

	Server();

	~Server();

    void init();

	std::vector<Player> getPlayers() const;

	Message<MovementInputHolder> &getMessage();
	
	void sendData(const std::vector<NetworkId> &ids, const std::vector<Transform> &transforms);

	void sendStateChange(const GameStateChange &StateChange);

	void gameOver(int team1, int team2);

	bool hasStarted() const;
};

#endif // UDPSERVER
