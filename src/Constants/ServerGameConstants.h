//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_SERVERGAMECONSTANTS_H
#define PV264_PROJECT_SERVERGAMECONSTANTS_H

#include <SDL_quit.h>
#include "../Utils/declarations.h"

enum CollisionLayers{
    BOUNDARIES,
    BALL,
    PLAYERS,
    GOALS
};

struct ServerGameConstants{

//----------------------Physics
static constexpr Uint32 kPhysicAccumulatorLimit = 20U;
static constexpr float kPhysicFps = 60;
static constexpr float kPhysicDeltaTime = 1 / kPhysicFps;
static constexpr float kInputMovementCoefficient = 50;
//-------------------//Physics

//-----------------------Collision Layers
static constexpr int kNumberOfCollisionLayers = 4;
static const bool kCollisionMatrix[kNumberOfCollisionLayers][kNumberOfCollisionLayers];
//----------------------//Collision Layers


//---------------------Colliders
static const Vector_Float kPlayerColliderCenter;
static const float kPlayerColliderRadius;
static const CollisionLayers kPlayerCollisionLayer;
static const Vector_Float kBallColliderCenter;
static const float kBallColliderRadius;
static const CollisionLayers kBallCollisionLayer;
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
    static const CollisionLayers kBarrierCollisionLayer;
//------------------------//Barriers

//------------------------Goals
    static const Vector_Float kLeftGoalPos;
    static const Vector_Float kRightGoalPos;
    static const Vector_Float kGoalBotRight;
    static const std::string kLeftGoalTag;
    static const std::string kRightGoalTag;
    static const CollisionLayers kGoalCollisionLayer;
//--------------------------//Goals

//--------------------Player constants
static constexpr int kMaxNumberOfPlayers = 2;
static constexpr int portNumber = 13000; //modify also ClientGameConstants.cpp

//--------------------//Player Constants

//---------------------Starting Positions
static const Vector_Float kStartingPositions[kMaxNumberOfPlayers];
    static const Vector_Float kBallStartingPosition;
//---------------------//Starting Positions

//----------------------Waiting Times
static constexpr float kWaitingToResetPositionsTime = 1;
static constexpr float kWaitingToResumeGameTime = 2;

//---------------------Game Time
static const float kGameTime;
//---------------------//Game Time
};

#endif //PV264_PROJECT_SERVERGAMECONSTANTS_H
