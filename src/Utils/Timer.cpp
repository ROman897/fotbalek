//
// Created by roman on 31.1.2017.
//

#include "Timer.h"
#include <SDL_timer.h>

Timer::Timer()
    : m_StartTime(0U), m_PausedTime(0U), m_Paused(false), m_Started(false) {}

Uint32 Timer::getTime() {
  if (!isStarted())
    return 0U;
  if (!isPaused())
    return SDL_GetTicks() - m_StartTime;

  return m_PausedTime - m_StartTime;
}

void Timer::resetTime() { m_StartTime = SDL_GetTicks(); }

bool Timer::isPaused() { return m_Paused; }

bool Timer::isStarted() { return m_Started; }

void Timer::pause() {
  m_Paused = true;
  m_PausedTime = SDL_GetTicks();
}

void Timer::start() {
  m_Started = true;
  m_Paused = false;
  m_StartTime = SDL_GetTicks();
}

void Timer::stop() { m_Started = false; }

void Timer::unpause() {
  m_Paused = false;
  m_StartTime = SDL_GetTicks();
}