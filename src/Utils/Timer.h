//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_TIMER_H
#define PV264_PROJECT_TIMER_H


#include <SDL_quit.h>

class Timer {
public:
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    void resetTime();

    //Gets the timer's time
    Uint32 getTime();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint32 m_StartTime;

    //The ticks stored when the timer was paused
    Uint32 m_PausedTime;

    //The timer status
    bool m_Paused;
    bool m_Started;
};


#endif //PV264_PROJECT_TIMER_H
