//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKRECEIVER_H
#define PV264_PROJECT_PLAYERNETWORKRECEIVER_H

#include "../Components/Network/NetworkId.h"
#include "../Components/Transform.h"
#include "../Constants/GameConstants.h"
#include "../Core/ComponentManager.h"
#include "../SettingsDefines.h"
#include "../Utils/Timer.h"
#include "API/Client/Client.h"

template <typename TSettings> class PlayerNetworkReceiverSystem {
private:
  ComponentManager<TSettings> *m_componentManager;
  Client *m_playerClient;
  Timer m_timer;
  bool m_initialized;
  Id m_StateChangeId;

  /**
   * call this when received positions from the server
   * @param ids
   * @param transforms
   */
  void updatePositions(const std::vector<NetworkId> &ids,
                       const std::vector<Transform> &transforms) {
    m_componentManager->template forEntitiesMatching_S<SystemSignature_Network>(
        [&ids, &transforms](NetworkId *id, Transform *transform) {
          for (int i = 0; i < ids.size(); ++i) {
            if (ids[i].id == id->id)
              *transform = transforms[i];
          }
        });
  }

  void gameStarted() {
    std::cout << "game started" << std::endl;
    // here we need to set all ids and set player visuals to match their
    // respective teams
    std::lock_guard<std::mutex> playersGuard(m_playerClient->m_playersMutex);
    const std::vector<Player> &players = m_playerClient->getPlayers();
    Id i = 0;
    std::lock_guard<std::mutex> lock(m_componentManager->componentsMutex);
    m_componentManager
        ->template forEntitiesMatching<SystemSignature_Network_Graphic>(
            [&players, &i](NetworkId *id, Sprite *sprite, Label *label) {
              id->id = players[i].m_id;
              sprite->m_enabled = true;
              sprite->m_texturePath =
                  players[i].m_team
                      ? ClientGameConstants::kPlayerSpritePath_Team1
                      : ClientGameConstants::kPlayerSpritePath_Team2;
              // need to set sprite based on which team the client is in
              label->m_Enabled = true;
              label->m_text = players[i].m_name;
              ++i;
            });
    Id ballId = m_componentManager->findGameObjectByTag("ball");
    m_componentManager
        ->template forEntityMatching<SystemSignature_SpriteGraphic>(
            ballId, [](Sprite *sprite, Transform *transform) {
              sprite->m_enabled = true;

            });

    m_initialized = true;
  }

  void runUpdate() {
    if (m_playerClient->hasStateChanged()) {
      std::lock_guard<std::mutex> stateGuard(
          m_playerClient->m_stateChangeMutex);
      GameStateChange change = m_playerClient->getState();
      std::cout << "team 1 scored: " << change.m_Team1Scored << std::endl;
      std::cout << "team 2 scored: " << change.m_Team2Scored << std::endl;
      m_componentManager
          ->template forEntityMatching_S<SystemSignature_GameStateChange>(
              m_StateChangeId, [change](GameStateChange *_change) {
                std::cout << "state changed" << std::endl;
                *_change = change;
              });
      m_playerClient->resetState();
      m_playerClient->resetStateChanged();
    }

    std::lock_guard<std::mutex> messageGuard(m_playerClient->m_messageMutex);
    auto &message = m_playerClient->getMessage();
    if (!message.isValid())
      return;
    auto &ids = message.getIds();
    auto &transforms = message.getMovements();
    updatePositions(ids, transforms);
    ids.clear();
    transforms.clear();
    message.setValid(false);
  }

public:
  void setManager(ComponentManager<TSettings> *manager) {
    m_componentManager = manager;
  }

  void setPlayerClient(Client *playerClient) { m_playerClient = playerClient; }

  PlayerNetworkReceiverSystem() : m_initialized(false) {}

  void start() {

    m_StateChangeId =
        m_componentManager
            ->template findEntityMatching<SystemSignature_GameStateChange>();
    run();
  }

  void run() {
    Timer timer;
    timer.start();

    while (true) {

      if (timer.getTime() < ClientGameConstants::kClientNetworkReceiverDt)
        continue;

      timer.resetTime();
      if (m_componentManager->shouldQuit()) {
        break;
      }
      if (!m_initialized && !m_playerClient->hasStarted()) {
        continue;
      }
      if (!m_initialized) {
        gameStarted();
        continue;
      }
      runUpdate();
    }
  }
};

#endif // PV264_PROJECT_PLAYERNETWORKRECEIVER_H
