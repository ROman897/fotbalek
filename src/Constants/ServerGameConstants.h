//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_SERVERGAMECONSTANTS_H
#define PV264_PROJECT_SERVERGAMECONSTANTS_H

#include <SDL_quit.h>

struct ServerGameConstants{

//----------------------Physics
static constexpr Uint32 kPhysicAccumulatorLimit = 20U;
static constexpr float kPhysicFps = 60;
static constexpr float kPhysicDeltaTime = 1 / kPhysicFps;
static constexpr float kInputMovementCoefficient = 10;
//-------------------//Physics

//--------------------Player constants
static constexpr int kMaxNumberOfPlayers = 4;
static const Vector_Float startingPositions[kMaxNumberOfPlayers];
};

#endif //PV264_PROJECT_SERVERGAMECONSTANTS_H
