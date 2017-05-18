//
// Created by roman on 5.5.2017.
//

#ifndef PV264_PROJECT_SERVERLOGICSYSTEM_H
#define PV264_PROJECT_SERVERLOGICSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Constants/ServerGameConstants.h"
#include "../SettingsDefines.h"
#include "../Components/Network/GameStateChange.h"

template <typename TSettings>
class ServerLogicSystem{
    ComponentManager<TSettings>* m_manager;
    int m_teamLeftScore, m_teamRightScore;
    float m_time;
    Id m_LeftGoalId;
    Id m_RightGoalId;
    Id m_stateHolderId;
    Id m_GameStateChangeId;
    bool m_WaitingToResetPositions;
    bool m_WaitingToResumeGame;
    float m_WaitingTime;



    void resetPositions(){
        std::cout << "physical restore of positions" << std::endl;
        int i = 0;
        m_manager->template forEntitiesMatching<SystemSignature_Player_Rigid>([&i](RigidBody* body, Transform* transform, PlayerComp* playerComp){
            transform->m_position = ServerGameConstants::kStartingPositions[i];
            body->m_velocity = {0,0};
            body->m_activeForce = {0,0};
            ++i;
        });

        m_manager->template forEntitiesMatching<SystemSignature_Ball_Rigid>([] (RigidBody* body, Transform* transform, BallComp* ballComp){
            transform->m_position = ServerGameConstants::kBallStartingPosition;
            body->m_velocity = {0,0};
            body->m_activeForce = {0,0};
        });
    }

public:
    void setManager(ComponentManager<TSettings >* manager){
        m_manager = manager;
    }

    void start(){
        m_LeftGoalId = m_manager->findGameObjectByTag(ServerGameConstants::kLeftGoalTag);
        m_RightGoalId = m_manager->findGameObjectByTag(ServerGameConstants::kRightGoalTag);
        m_stateHolderId = m_manager->template findEntityMatching<SystemSignature_GameState>();
        m_GameStateChangeId = m_manager->template findEntityMatching<SystemSignature_GameStateChange>();
    }

    void run(float dt){
        // this ensures that this method has components locked for the whole scope
        std::lock_guard<std::mutex> lock(m_manager->componentsMutex);
        m_time += dt;
        if (m_time > ServerGameConstants::kGameTime){
            std::cout << "game over!!!!" << std::endl;
            // game is over, now we need to let the players know
            m_manager->template forEntityMatching<SystemSignature_GameState>(m_stateHolderId, [](GameState* state){
                state->m_ReceiveInput = false;
            });

            m_manager->template forEntityMatching<SystemSignature_GameStateChange>(m_GameStateChangeId, [] (GameStateChange* change) {
                change->m_GameOver = true;
            });
            // now we may want to call quit after we send game over message to other players

            return;
        }
        if (m_WaitingToResetPositions){
            m_WaitingTime += dt;
            if (m_WaitingTime > ServerGameConstants::kWaitingToResetPositionsTime){
                std::cout << "reset positions" << std::endl;
                // here we reset positions and set receive input to false
                resetPositions();
                m_manager->template forEntityMatching<SystemSignature_GameState>(m_stateHolderId, [](GameState* state){
                    state->m_ReceiveInput = false;
                });

                m_WaitingTime = 0;
                m_WaitingToResetPositions = false;
                m_WaitingToResumeGame = true;
            }
            return;
        }
        if (m_WaitingToResumeGame){

            m_WaitingTime += dt;
            if (m_WaitingTime > ServerGameConstants::kWaitingToResumeGameTime){
                std::cout << "resume game" << std::endl;

                m_manager->template forEntityMatching<SystemSignature_GameState>(m_stateHolderId, [](GameState* state){
                    state->m_ReceiveInput = true;
                });
                // here we set receive input to true
                m_WaitingTime = 0;
                m_WaitingToResumeGame = false;

                m_manager->template forEntityMatching<SystemSignature_ColliderTrigger>(m_LeftGoalId, [this](ColliderTrigger* trigger) {
                    trigger->m_Triggered = false;
                });

                m_manager->template forEntityMatching<SystemSignature_ColliderTrigger>(m_RightGoalId, [this](ColliderTrigger* trigger) {
                    trigger->m_Triggered = false;
                });
            }
            return;
        }



        m_manager->template forEntityMatching<SystemSignature_ColliderTrigger>(m_LeftGoalId, [this](ColliderTrigger* trigger){
            if (!trigger->m_Triggered)
                return;
            std::cout << "left goal scored" << std::endl;
            trigger->m_Triggered = false;
            m_manager->template forEntityMatching<SystemSignature_GameStateChange>(m_GameStateChangeId, [] (GameStateChange* change) {
                change->m_Team1Scored = true;
            });
            m_WaitingToResetPositions = true;
        } );

        m_manager->template forEntityMatching<SystemSignature_ColliderTrigger>(m_RightGoalId, [this](ColliderTrigger* trigger){
            if (! trigger->m_Triggered)
                return;
            trigger->m_Triggered = false;
            m_manager->template forEntityMatching<SystemSignature_GameStateChange>(m_GameStateChangeId, [] (GameStateChange* change) {
                change->m_Team2Scored = true;
            });
            m_WaitingToResetPositions = true;
        } );
    }
    ServerLogicSystem() : m_teamLeftScore(0), m_teamRightScore(0), m_time(0) {}
};
#endif //PV264_PROJECT_SERVERLOGICSYSTEM_H
