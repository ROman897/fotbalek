//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Components/Network/NetworkId.h"
#include "../Components/Logic/MovementInputHolder.h"
#include "../Components/Physic/RigidBody.h"
#include "../Constants/GameConstants.h"
#include "API/Server/Server.h"
#include "../Constants/ServerGameConstants.h"
#include "../SettingsDefines.h"
#include "../Utils/Timer.h"

inline void applyInputForce(RigidBody& body, const MovementInputHolder& inputHolder, float coef){
    if (inputHolder.moveVertical){
        int dir = inputHolder.moveUp ? 1 : -1;
        body.m_velocity.m_y += dir * coef;
    }

    if (inputHolder.moveHorizontal){
        int dir = inputHolder.moveRight ? 1 : -1;
        body.m_velocity.m_x += dir * coef;
    }

    if (inputHolder.shoot){
        // TODO not yet implemented
    }
}


template <typename TSettings>
class ServerNetworkReceiverSystem{

private:
    ComponentManager<TSettings>* m_componentManager;
    Server* m_UdpServer;
    bool m_initialized;
    Id m_GameStateId;


    void updateInputs(std::vector<NetworkId> ids, std::vector<MovementInputHolder> inputs){
        m_componentManager->template forEntitiesMatching_S<SystemSignature_Network_Rigid>([&ids, &inputs](NetworkId* id, RigidBody* body){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i].id == id->id)
                    applyInputForce(*body, inputs[i], ServerGameConstants::kInputMovementCoefficient);
            }
        });
    }

    void gameStarted(){

        std::lock_guard<std::mutex> messageMutex(m_UdpServer->m_playersMutex);
        const auto& players = m_UdpServer->getPlayers();
        std::cout << "received number of players: " << players.size() << std::endl;
        std::cout << "first player: " << players[0].m_name << "id: " << players[0].m_id << std::endl;
        std::cout << "second player: " << players[1].m_name << "id: " << players[1].m_id << std::endl;
        Id i = 0;
        std::lock_guard<std::mutex> lock(m_componentManager->componentsMutex);
        m_componentManager->template forEntitiesMatching<SystemSignature_Network_Player>([&players, &i](NetworkId* id, Transform* transform, PlayerComp* playerComp){
            id->id = players[i].m_id;
            transform->m_position = ServerGameConstants::kStartingPositions[i];
            ++i;
        });

        m_componentManager->template forEntitiesMatching<SystemSignature_Ball>([](Transform* transform, BallComp* ballComp){
            transform->m_position = ServerGameConstants::kBallStartingPosition;
        });
        m_initialized = true;
    }

    void run(){
        Timer timer;
        timer.start();

        while(true){


            if (timer.getTime() < ClientGameConstants::kClientNetworkReceiverDt)
                continue;
            timer.resetTime();

            if (m_componentManager->shouldQuit()){
                break;
            }


            if (!m_initialized && ! m_UdpServer->hasStarted())
                continue;
            if (! m_initialized) {
                gameStarted();
                timer.resetTime();
                continue;
            }


            std::cout << "before message lock" << std::endl;
            std::lock_guard<std::mutex> messageMutex(m_UdpServer->m_messageMutex);
            std::cout << "after message lock" << std::endl;
            auto& data = m_UdpServer->getMessage();
            if (! data.isValid())
                continue;

            std::cout << "after data validation" << std::endl;
            bool accept;
            m_componentManager->template forEntityMatching_S<SystemSignature_GameState>(m_GameStateId, [&accept](GameState* state){
                accept = state->m_ReceiveInput;
            });
            std::cout << "after input validation" << std::endl;
            auto& ids = data.getIds();
            auto& inputs = data.getMovements();
            if (! ids.empty()){
                std::cout << "received movement from id: " << ids[0].id << std::endl;
            }
            updateInputs(ids, inputs);



        }

    }

public:

    void setManager(ComponentManager<TSettings> *manager){
        m_componentManager = manager;
    }

    ServerNetworkReceiverSystem() : m_initialized(false) {

    }

    void setServer(Server* server){
        m_UdpServer = server;
    }

    void start(){
        m_GameStateId = m_componentManager->template findEntityMatching<SystemSignature_GameState>();

        run();
    }
};

#endif //PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
