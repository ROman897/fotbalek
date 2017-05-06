//
// Created by roman on 6.5.2017.
//

#ifndef PV264_PROJECT_GAMESTATECHANGE_H
#define PV264_PROJECT_GAMESTATECHANGE_H

struct GameStateChange{
    bool m_Team1Scored;
    bool m_Team2Scored;
    bool m_GameOver;

    GameStateChange(bool m_Team1Scored, bool m_Team2Scored, bool m_GameOver) : m_Team1Scored(m_Team1Scored),
                                                                               m_Team2Scored(m_Team2Scored),
                                                                               m_GameOver(m_GameOver) {}
    GameStateChange() : m_Team1Scored(false), m_Team2Scored(false), m_GameOver(false) {}
};
#endif //PV264_PROJECT_GAMESTATECHANGE_H
