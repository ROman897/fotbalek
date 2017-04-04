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
    Uint32 mStartTime;

    //The ticks stored when the timer was paused
    Uint32 mPausedTime;

    //The timer status
    bool mPaused;
    bool mStarted;
};


#endif //PV264_PROJECT_TIMER_H
