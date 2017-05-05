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
    void prepareData(std::vector<NetworkId>& ids, std::vector<Transform>& transforms){
        m_componentManager->template forEntitiesMatching<SystemSignature_Network>([&ids, &transforms](NetworkId* id, Transform* transform){
            ids.push_back(*id);
            transforms.push_back(*transform);

        });
    }

public:

    void setManager(ComponentManager<TSettings> *manager){
        m_componentManager = manager;
    }
    void start(){
    }

    void setServer(Server* server){
        m_playerServer = server;
    }

    void run(float dt){
        if (! m_playerServer->hasStarted())
            return;
        std::vector<NetworkId> ids;
        std::vector<Transform> transforms;
        prepareData(ids, transforms);
        std::cout << "server system prepared data length: " << transforms.size() << std::endl;
        m_playerServer->sendData(ids, transforms);
    }

};

#endif //PV264_PROJECT_SERVERNETWORKSENDERSYSTEM_H
