//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Components/Physic/RigidBody.h"
#include "../Utils/GameConstants.h"

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
    using SystemSignature_Network_Rigid = Signature<NetworkId, RigidBody>;

    void updateInput(std::vector<NetworkId> ids, std::vector<MovementInputHolder> inputs){
        m_componentManager->forEntitiesMatching<SystemSignature_Network_Rigid>([&ids, &inputs](auto& id, auto& body){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i] == id)
                    applyInputForce(body, inputs[i], GameConstants::kInputMovementCoefficient);
            }
        });
    }
};

#endif //PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
