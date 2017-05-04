//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H

#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Core/ComponentManager.h"
#include "API/Client/PlayerClient.h"

template <typename TSettings>
class PlaynerNetworkSenderSystem{


private:
    ComponentManager<TSettings>* m_componentManager;
    // id of a gameobject that has NetworkId and MovementInputHolder components
    Id id;

    const NetworkId* m_networkId;
    MovementInputHolder * m_inputHolder;

    PlayerClient* m_playerClient;

    bool prepareData(const NetworkId* networkId, MovementInputHolder* inputHolder){
        bool result = false;
        m_componentManager->template forEntityMatching<SystemSignature_Network_Input>(id, [&networkId, &inputHolder, &result](const NetworkId* _networkId, MovementInputHolder* _inputHolder){
            if (! _inputHolder->valid)
                return;
            networkId = _networkId;
            inputHolder = _inputHolder;
            _inputHolder->valid = false;
            result = true;
        });
        return result;
    }

    void sendData(){
        if (prepareData(m_networkId, m_inputHolder)) {
            m_playerClient->sendData(*m_networkId, *m_inputHolder);
            std::cout << "sending data on client sender system" << std::endl;
        }

    }



public:
    void setPlayerClient(PlayerClient* playerClient){
        m_playerClient = playerClient;
    }

    void setManager(ComponentManager<TSettings>* manager){
        m_componentManager = manager;
    }

    void start(){
        id = m_componentManager->template findEntityMatching<SystemSignature_Network_Input>();
    }

    void run(float dt){
        sendData();
    }

};

#endif //PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
