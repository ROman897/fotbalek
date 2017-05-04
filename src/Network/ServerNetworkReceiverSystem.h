//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Components/Physic/RigidBody.h"
#include "../Constants/GameConstants.h"
#include "API/Server/PlayerServer.h"
#include "../Constants/ServerGameConstants.h"
#include "../SettingsDefines.h"
#include "../Utils/Timer.h"

void applyInputForce(RigidBody& body, const MovementInputHolder& inputHolder, float coef){
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
    PlayerServer* m_PlayerServer;
    bool m_initialized;
    using SystemSignature_Network_Rigid = Signature<NetworkId, RigidBody>;

    void updateInputs(std::vector<NetworkId> ids, std::vector<MovementInputHolder> inputs){
        m_componentManager->forEntitiesMatching<SystemSignature_Network_Rigid>([&ids, &inputs](auto& id, auto& body){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i] == id)
                    applyInputForce(body, inputs[i], ServerGameConstants::kInputMovementCoefficient);
            }
        });
    }

    void gameStarted(){
        auto& players = m_PlayerServer->getPlayers();
        Id i = 0;
        m_componentManager->forEntitiesMatching<SystemSignature_Network>([&players, &i](NetworkId* id, Transform* transform){
            id->id = players[i].id;
            transform->m_position = ServerGameConstants::startingPositions[i];
        });
        m_initialized = true;
    }

    void run(){
        Timer timer;
        timer.start();

        while(true){

            if (! m_PlayerServer->hasStarted())
                continue;
            if (! m_initialized)
                gameStarted();
            if (timer.getTime() < ClientGameConstants::kClientNetworkReceiverDt)
                continue;

            auto& data = m_PlayerServer->getData();
            if (! data.isValid())
                continue;

            auto& ids = data.getIds();
            auto& inputs = data.getInputs();
            updateInput(ids, inputs);


            if (m_componentManager->shouldQuit()){
                break;
            }
        }

    }

public:
    ServerNetworkReceiverSystem() : m_initialized(false) {

    }

    void setServer(PlayerServer* server){
        m_PlayerServer = server;
    }

    void start(){
        run();
    }
};

#endif //PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
