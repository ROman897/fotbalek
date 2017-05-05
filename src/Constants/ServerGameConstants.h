//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_SERVERGAMECONSTANTS_H
#define PV264_PROJECT_SERVERGAMECONSTANTS_H

#include <SDL_quit.h>
#include "../Utils/declarations.h"

struct ServerGameConstants{

//----------------------Physics
static constexpr Uint32 kPhysicAccumulatorLimit = 20U;
static constexpr float kPhysicFps = 60;
static constexpr float kPhysicDeltaTime = 1 / kPhysicFps;
static constexpr float kInputMovementCoefficient = 10;
//-------------------//Physics

//---------------------Colliders
static const Vector_Float kPlayerColliderCenter;
static const float kPlayerColliderRadius;
static const Vector_Float kBallColliderCenter;
static const float kBallColliderRadius;
//---------------------//Colliders

//----------------------Rigid bodies
    static const float kPlayerInverseMass;
    static const float kPlayerRestitution;
    static const float kPlayerSpeedDecrement;

    static const float kBallInverseMass;
    static const float kBallRestitution;
    static const float kBallSpeedDecrement;
//----------------------//Rigid Bodies

//----------------------Barriers
    static const Vector_Float kBarriersTopLeft;
    static const Vector_Float kLeftBarrier_Pos;
    static const Vector_Float kSideBarrier_BotRight;
    static const Vector_Float kTopBarrier_Pos;
    static const Vector_Float kUpDownBarrier_BotRight;
    static const Vector_Float kBotBarrier_Pos;
    static const Vector_Float kRightBarrier_Pos;
//------------------------//Barriers

//------------------------Goals
    static const Vector_Float kLeftGoalPos;
    static const Vector_Float kRightGoalPos;
    static const Vector_Float kGoalBotRight;
    static const std::string kLeftGoalTag;
    static const std::string kRightGoalTag;
//--------------------------//Goals

//--------------------Player constants
static constexpr int kMaxNumberOfPlayers = 4;
static constexpr int portNumber = 13000; //modify also ClientGameConstants.cpp
static const Vector_Float startingPositions[kMaxNumberOfPlayers];
//--------------------//Player Constants

//---------------------Game Time
static const float kGameTime;
//---------------------//Game Time
};

#endif //PV264_PROJECT_SERVERGAMECONSTANTS_H
