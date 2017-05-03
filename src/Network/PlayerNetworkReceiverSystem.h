//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKRECEIVER_H
#define PV264_PROJECT_PLAYERNETWORKRECEIVER_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "../Core/ComponentManager.h"
#include "API/Client/PlayerClient.h"

template <typename TSettings>
class PlayerNetworkReceiverSystem{
    using SystemSignature_Network = Signature<NetworkId, Transform>;
private:
    ComponentManager<TSettings>* m_componentManager;
    PlayerClient* playerClient;

    /**
     * call this when received positions from the server
     * @param ids
     * @param transforms
     */
    void updatePositions(const std::vector<NetworkId>& ids, const std::vector<Transform>& transforms){
        m_componentManager->forEntitiesMatching<SystemSignature_Network>([&ids, &transforms](auto& id, auto& transform){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i] == id)
                    transform = transforms[i];
            }
        });
    }

    /**
     * call this with callback when received gamestarted from the server
     */
    void gameStarted(){

    }



};

#endif //PV264_PROJECT_PLAYERNETWORKRECEIVER_H
