//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKRECEIVER_H
#define PV264_PROJECT_PLAYERNETWORKRECEIVER_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "../Core/ComponentManager.h"

template <typename TSettings>
class PlayerNetworkReceiverSystem{
    using SystemSignature_Network = Signature<NetworkId, Transform>;
private:
    ComponentManager<TSettings>* m_componentManager;

    void updatePositions(std::vector<NetworkId>& ids, std::vector<Transform>& transforms){
        m_componentManager->forEntitiesMatching<SystemSignature_Network>([&ids, &transforms](auto& id, auto& transform){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i] == id)
                    transform = transforms[i];
            }
        });
    }
};

#endif //PV264_PROJECT_PLAYERNETWORKRECEIVER_H
