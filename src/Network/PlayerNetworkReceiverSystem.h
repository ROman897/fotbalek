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
#include "../Constants/GameConstants.h"

template <typename TSettings>
class PlayerNetworkReceiverSystem{
private:
    ComponentManager<TSettings>* m_componentManager;
    PlayerClient* m_playerClient;
    Timer m_timer;
    bool m_initialized;

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
            sprite->m_texturePath = players[i].m_team ? ClientGameConstants::kPlayerSpritePath_Team1 : ClientGameConstants::kPlayerSpritePath_Team2;
            // need to set sprite based on which team the client is in
            label->enabled = true;
            label->m_text = players[i].name;
        });
        m_initialized = true;
    }


    void runUpdate(){
        if (! m_playerClient->hasStarted())
            return;
        if (! m_initialized){
            gameStarted();
        }
        auto& message = m_playerClient->getMessage();
        if (!message.isValid())
            return;
        auto& ids = message.getIds();
        auto& transforms = message.getTransforms();
        updatePositions(ids, transforms);
        message.releaseMessage();
    }

public:

    void setPlayerClient(PlayerClient* playerClient){
        m_playerClient = playerClient;
    }

    PlayerNetworkReceiverSystem() : m_initialized(false) {

    }


void start(){
    run();

}

    void run(){
        Uint32 accumulator = 0;
        Timer timer;
        timer.start();

        Uint32 frameStart = timer.getTime();
        timer.resetTime();

        while (true){
            accumulator += timer.getTime() - frameStart;

            frameStart = timer.getTime();

            if (accumulator > GameConstants::kEngineAccumulatorLimit)
                accumulator = GameConstants::kEngineAccumulatorLimit;

            while (accumulator > ClientGameConstants::kClientNetworkReceiverDt) {
                runUpdate();
                accumulator -= GameConstants::kEngineDeltaTime;
            }

            if (m_componentManager->shouldQuit()){
                break;
            }
        }
    }



};

#endif //PV264_PROJECT_PLAYERNETWORKRECEIVER_H
