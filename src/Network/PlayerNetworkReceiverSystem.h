//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKRECEIVER_H
#define PV264_PROJECT_PLAYERNETWORKRECEIVER_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "../Core/ComponentManager.h"
#include "API/Client/PlayerClient.h"
#include "../Utils/Timer.h"
#include "../SettingsDefines.h"

template <typename TSettings>
class PlayerNetworkReceiverSystem{
private:
    ComponentManager<TSettings>* m_componentManager;
    PlayerClient* m_playerClient;
    Timer timer;

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

    void gameStarted(){
        // here we need to set all ids and set player visuals to match their respective teams
       const std::vector<Player> & players = m_playerClient->getPlayers();
        Id i = 0;
        m_componentManager->forEntitiesMatching<SystemSignature_Network_Graphic>([&players, &i](NetworkId* id, Sprite* sprite, Label* label){
            id->id = players[i].id;
            sprite->enabled = true;
            //sprite->m_texturePath =
            // need to set sprite based on which team the client is in
            label->enabled = true;
            label->m_text = players[i].name;
            // need to set label color based on which team the client is in
        });
    }

public:

    void setPlayerClient(PlayerClient* playerClient){
        m_playerClient = playerClient;
    }

void start(){
    run();
}

    void run(){
        while (true){


            if (m_componentManager->shouldQuit())
                break;
        }
    }



};

#endif //PV264_PROJECT_PLAYERNETWORKRECEIVER_H
