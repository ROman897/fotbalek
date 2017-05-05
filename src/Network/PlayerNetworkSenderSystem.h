//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H

#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Core/ComponentManager.h"
#include "API/Client/Client.h"

template <typename TSettings>
class PlayerNetworkSenderSystem{


private:
    ComponentManager<TSettings>* m_componentManager;
    // id of a gameobject that has NetworkId and MovementInputHolder components
    Id id;

    MovementInputHolder * m_inputHolder;

    Client* m_playerClient;

    bool prepareData(MovementInputHolder* inputHolder){
        bool result = false;
        m_componentManager->template forEntityMatching<SystemSignature_Network_Input>(id, [this, &result](MovementInputHolder* _inputHolder){
            if (! _inputHolder->valid)
                return;
            m_inputHolder = _inputHolder;
            _inputHolder->valid = false;
            result = true;
        });
        return result;
    }

    void sendData(){
        if (! m_playerClient->hasStarted())
            return;
        if (prepareData(m_inputHolder)) {
            m_playerClient->sendData(*m_inputHolder);

        }

    }



public:
    void setPlayerClient(Client* playerClient){
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
