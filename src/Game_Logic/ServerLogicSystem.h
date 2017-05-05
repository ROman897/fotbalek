//
// Created by roman on 5.5.2017.
//

#ifndef PV264_PROJECT_SERVERLOGICSYSTEM_H
#define PV264_PROJECT_SERVERLOGICSYSTEM_H

#include "../Core/ComponentManager.h"
#include "../Constants/ServerGameConstants.h"

template <typename TSettings>
class ServerLogicSystem{
    ComponentManager<TSettings>* m_manager;
    int m_team1Score, m_team2Score;
    float m_time;
    Id m_LeftGoalId;
    Id m_RIghtGoalId;

public:
    void setManager(ComponentManager<TSettings >* manager){
        m_manager = manager;
    }

    void start(){
        m_LeftGoalId = m_manager->findGameObjectByTag(ServerGameConstants::kLeftGoalTag);
        m_RIghtGoalId = m_manager->findGameObjectByTag(ServerGameConstants::kRightGoalTag);
    }

    void run(float dt){
        m_time += dt;
        if (m_time > ServerGameConstants::kGameTime){
            // game is over, now we need to let the players know
        }
    }

    ServerLogicSystem() : m_team1Score(0), m_team2Score(0), m_time(0) {}
};
#endif //PV264_PROJECT_SERVERLOGICSYSTEM_H
