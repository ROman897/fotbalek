//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H

#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Core/ComponentManager.h"

template <typename TSettings>
class PlaynerNetworkSenderSystem{
    using SystemSignature_Network_Input = Signature<NetworkId, MovementInputHolder>;

private:
    ComponentManager<TSettings>* m_componentManager;
    // id of a gameobject that has NetworkId and MovementInputHolder components
    Id id;

    PlayerClient* playerClient;

    void prepareData(const NetworkId* networkId, MovementInputHolder* inputHolder){
        m_componentManager->forEntityMatching<SystemSignature_Network_Input>(id, [&networkId, &inputHolder](const NetworkId* _networkId, MovementInputHolder* _inputHolder){
            networkId = _networkId;
            inputHolder = _inputHolder;
            _inputHolder->valid = false;
        });
    }

public:
    void sendData(){
        const NetworkId* id;
        MovementInputHolder * inputHolder;

    }
};

#endif //PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
