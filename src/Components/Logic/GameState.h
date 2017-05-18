//
// Created by roman on 5.5.2017.
//

#ifndef PV264_PROJECT_GAMESTATE_H
#define PV264_PROJECT_GAMESTATE_H
struct GameState{
	bool m_ReceiveInput;

    GameState(bool m_ReceiveInput) : m_ReceiveInput(m_ReceiveInput) {}
    GameState() : m_ReceiveInput(true) {};
};

#endif //PV264_PROJECT_GAMESTATE_H
