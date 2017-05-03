//
// Created by pnavratil on 4/5/17.
//

#ifndef PV264_PROJECT_PLAYER_SERVER_H
#define PV264_PROJECT_PLAYER_SERVER_H

#ifndef MAX_PLAYERCOUNT
#define MAX_PLAYERCOUNT 6
#endif // MAX_PLAYERCOUNT

#ifndef PORT_NUMBER
#define PORT_NUMBER 13000
#endif // PORT_NUMBER

#include <string>
#include <boost/asio.hpp>
//#include "../../../RigidBody.h"
//#include "../../../Ball.h"
#include "UdpServer.h"
#include <iostream>
#include <thread>

class PlayerServer {
    //using udp = boost::asio::ip::udp;
    //using IOService = boost::asio::io_service;


    struct Client {
        std::string m_name;
        //RigidBody m_object;
    };

    //std::thread m_networkThr;
    //std::vector<std::experimental::optional<Client>> m_clients;
    UdpServer m_commServer;

    void startComm(UdpServer &srv);

public:
    PlayerServer() {
        //m_clients.resize(MAX_PLAYERCOUNT);
        try {
            //m_networkThr = std::thread([this](){m_commServer.init();});
            m_commServer.init();
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
            std::exit(1);
        }
    }

    ~PlayerServer() {
        //m_networkThr.join();
    }

    void run();
};

#endif //PV264_PROJECT_PLAYER_SERVER_H
