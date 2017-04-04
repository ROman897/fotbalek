//
// Created by roman on 31.1.2017.
//

#include <SDL_timer.h>
#include "Timer.h"

Timer::Timer()
        : mStartTime(0U)
        , mPausedTime(0U)
        , mPaused(false)
        , mStarted(false)
{
}

Uint32 Timer::getTime()
{
    if (!isStarted())
        return 0U;
    if (!isPaused())
        return SDL_GetTicks() - mStartTime;

    return mPausedTime - mStartTime;
}

void Timer::resetTime()
{
    mStartTime = SDL_GetTicks();
}

bool Timer::isPaused()
{
    return mPaused;
}

bool Timer::isStarted()
{
    return mStarted;
}

void Timer::pause()
{
    mPaused = true;
    mPausedTime = SDL_GetTicks();
}

void Timer::start()
{
    mStarted = true;
    mPaused = false;
    mStartTime = SDL_GetTicks();
}

void Timer::stop()
{
    mStarted = false;
}

void Timer::unpause()
{
    mPaused = false;
    mStartTime = SDL_GetTicks();
}