//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "API/Server/Server.h"

template <typename TSettings>
class ServerNetworkSenderSystem{
    using SystemSignature_Network = Signature<NetworkId, Transform>;
private:
    ComponentManager<TSettings>* m_componentManager;
    Server* m_playerServer;
    Id m_GameStateChangeId;
    GameStateChange m_StateChange;

    void prepareData(std::vector<NetworkId>& ids, std::vector<Transform>& transforms){
        m_componentManager->template forEntitiesMatching_S<SystemSignature_Network>([&ids, &transforms](NetworkId* id, Transform* transform){
            ids.push_back(*id);
            transforms.push_back(*transform);

        });
    }

public:

    void setManager(ComponentManager<TSettings> *manager){
        m_componentManager = manager;
    }
    void start(){
        m_GameStateChangeId = m_componentManager->template findEntityMatching<SystemSignature_GameStateChange>();
    }

    void setServer(Server* server){
        m_playerServer = server;
    }

    void run(float dt){
        std::cout << "server sender run" << std::endl;
        if (! m_playerServer->hasStarted())
            return;

        m_componentManager->template forEntityMatching_S<SystemSignature_GameStateChange>(m_GameStateChangeId, [this](GameStateChange* state){
            m_StateChange = *state;
        });

        if (m_StateChange.m_GameOver || m_StateChange.m_Team1Scored || m_StateChange.m_Team2Scored){
            //m_playerServer->sendStateChange(m_StateChange);
            m_StateChange.m_Team2Scored = false;
            m_StateChange.m_Team1Scored = false;
            m_StateChange.m_GameOver = false;
            return;
        }

        std::vector<NetworkId> ids;
        std::vector<Transform> transforms;
        prepareData(ids, transforms);
        std::cout << "server system prepared data length: " << transforms.size() << std::endl;
        m_playerServer->sendData(ids, transforms);
    }

};

#endif //PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H
