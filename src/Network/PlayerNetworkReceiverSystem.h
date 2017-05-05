//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKRECEIVER_H
#define PV264_PROJECT_PLAYERNETWORKRECEIVER_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "../Core/ComponentManager.h"
#include "API/Client/Client.h"
#include "../Utils/Timer.h"
#include "../SettingsDefines.h"
#include "../Constants/GameConstants.h"

template <typename TSettings>
class PlayerNetworkReceiverSystem{
private:
    ComponentManager<TSettings>* m_componentManager;
    Client* m_playerClient;
    Timer m_timer;
    bool m_initialized;

    /**
     * call this when received positions from the server
     * @param ids
     * @param transforms
     */
    void updatePositions(const std::vector<NetworkId>& ids, const std::vector<Transform>& transforms){
        m_componentManager->template forEntitiesMatching<SystemSignature_Network>([&ids, &transforms](NetworkId* id, Transform* transform){
            for (int i =0; i < ids.size(); ++i){
                if (ids[i].id == id->id)
                    *transform = transforms[i];
            }
        });
    }

    void gameStarted(){
        // here we need to set all ids and set player visuals to match their respective teams
        std::lock_guard<std::mutex> playersGuard(m_playerClient->m_playersMutex);
       const std::vector<Player> & players = m_playerClient->getPlayers();
        Id i = 0;
        m_componentManager->template forEntitiesMatching<SystemSignature_Network_Graphic>([&players, &i](NetworkId* id, Sprite* sprite, Label* label){
            id->id = players[i].m_id;
            sprite->m_enabled = true;
            sprite->m_texturePath = players[i].m_team ? ClientGameConstants::kPlayerSpritePath_Team1 : ClientGameConstants::kPlayerSpritePath_Team2;
            // need to set sprite based on which team the client is in
            label->enabled = true;
            label->m_text = players[i].m_name;
        });
        Id ballId = m_componentManager->findGameObjectByTag("ball");
        m_componentManager->template forEntityMatching<SystemSignature_SpriteGraphic >(ballId, [](Sprite *sprite, Transform* transform){
            sprite->m_enabled = true;

        });

        m_initialized = true;
    }


    void runUpdate(){
        if (! m_playerClient->hasStarted())
            return;
        if (! m_initialized){
            gameStarted();
        }
        std::lock_guard<std::mutex> messageGuard(m_playerClient->m_messageMutex);
        auto& message = m_playerClient->getMessage();
        if (!message.isValid())
            return;
        auto& ids = message.getIds();
        auto& transforms = message.getMovements();
        std::cout << "received number of positions: " << transforms.size() << std::endl;
        updatePositions(ids, transforms);
    }

public:

    void setManager(ComponentManager<TSettings>* manager){
        m_componentManager = manager;
    }

    void setPlayerClient(Client* playerClient){
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
