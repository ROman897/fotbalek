//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "API/Server/UdpServer.h"

template <typename TSettings>
class ServerNetworkSenderSystem{
    using SystemSignature_Network = Signature<NetworkId, Transform>;
private:
    ComponentManager<TSettings>* m_componentManager;
    UdpServer* m_playerServer;
    void prepareData(std::vector<NetworkId>& ids, std::vector<Transform>& transforms){
        m_componentManager->forEntitiesMatching<SystemSignature_Network>([&ids, &transforms](auto& id, auto& transform){
            ids.push_back(id);
            transforms.push_back(transform);

        });
    }

public:
    void start(){
    }

    void setServer(UdpServer* server){
        m_playerServer = server;
    }

    void run(float dt){
        std::vector<NetworkId> ids;
        std::vector<Transform> transforms;
        prepareData(ids, transforms);
        m_playerServer->sendData(ids, transforms);
    }

};

#endif //PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H
