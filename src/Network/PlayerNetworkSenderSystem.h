//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Logic/MovementInputHolder.h"
#include "../Core/ComponentManager.h"
#include "API/Client/Client.h"
#include "../SettingsDefines.h"

template <typename TSettings>
class PlayerNetworkSenderSystem{


private:
    ComponentManager<TSettings>* m_componentManager;
    // id of a gameobject that has NetworkId and MovementInputHolder components
    Id id;
    bool m_started;

    MovementInputHolder m_inputHolder;

    Client* m_playerClient;

    bool prepareData(MovementInputHolder& inputHolder){
        bool result = false;
        m_componentManager->template forEntityMatching_S<SystemSignature_Network_Input>(id, [this, &result](MovementInputHolder* _inputHolder){
            if (! _inputHolder->valid)
                return;
            m_inputHolder = *_inputHolder;
            _inputHolder->moveHorizontal = false;
            _inputHolder->moveVertical = false;
            _inputHolder->valid = false;
            result = true;
        });
        return result;
    }

    void sendData(){
        if (!m_started && ! m_playerClient->hasStarted())
            return;
        m_started = true;
        if (prepareData(m_inputHolder)) {
            //std::cout << "moving horizontal: " << m_inputHolder.moveHorizontal << std::endl;
            //std::cout << "moving vertical: " << m_inputHolder.moveVertical << std::endl;
            m_playerClient->sendData(m_inputHolder);

        }

    }



public:

    PlayerNetworkSenderSystem() : m_started(false){

    }
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
