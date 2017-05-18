//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_SERVERGAMECONSTANTS_H
#define PV264_PROJECT_SERVERGAMECONSTANTS_H

#include "../Utils/Declarations.h"
#include <SDL_quit.h>
#include <string>

enum CollisionLayers { BOUNDARIES, BALL, PLAYERS, GOALS };

struct ServerGameConstants {

  //----------------------Physics
  static constexpr Uint32 kPhysicAccumulatorLimit = 20U;
  static constexpr float kPhysicFps = 90;
  static constexpr float kPhysicDeltaTime = 1 / kPhysicFps;
  static constexpr float kInputMovementCoefficient = 10;
  //-------------------//Physics

  //-----------------------Collision Layers
  static constexpr int kNumberOfCollisionLayers = 4;
  static const bool kCollisionMatrix[kNumberOfCollisionLayers]
                                    [kNumberOfCollisionLayers];
  //----------------------//Collision Layers

  //---------------------Colliders
  static const Vector_Float kPlayerColliderTopLeft;
  static const Vector_Float kPlayerColliderBottomRight;
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
  static const Vector_Float kLeftTopBarrier_Pos;
  static const Vector_Float kLeftBotBarrier_Pos;
  static const Vector_Float kSideBarrier_BotRight;
  static const Vector_Float kSideBarrier_TopLeft;
  static const Vector_Float kTopBarrier_Pos;
  static const Vector_Float kUpDownBarrier_BotRight;
  static const Vector_Float kUpDownBarrier_TopLeft;
  static const Vector_Float kBotBarrier_Pos;
  static const Vector_Float kRightTopBarrier_Pos;
  static const Vector_Float kRightBotBarrier_Pos;
  static const CollisionLayers kBarrierCollisionLayer;

  static const float kBarrierInverseMass;
  static const float kBarrierRestitution;
  static const float kBarrierMaxVelocity;
  static const float kBarrierSpeedDecrement;

  static const float kLeftBoundary;
  static const float kRightBoundary;
  static const float kUpBoundary;
  static const float kDownBoundary;
  //------------------------//Barriers

  //------------------------Goals
  static const Vector_Float kLeftGoalPos;
  static const Vector_Float kRightGoalPos;
  static const Vector_Float kGoalBotRight;
  static const std::string kLeftGoalTag;
  static const std::string kRightGoalTag;
  static const CollisionLayers kGoalCollisionLayer;
  //--------------------------//Goals

  //-----------------------max Velocities
  static const float kPlayerMaxVelocity;
  static const float kBallMaxVelocity;
  //-----------------------//max velocities

  //--------------------Player constants
  static constexpr int kMaxNumberOfPlayers = 4;
  static constexpr int portNumber = 13000; // modify also
                                           // ClientGameConstants.cpp

  //--------------------//Player Constants

  //---------------------Starting Positions
  static const Vector_Float kStartingPositions[kMaxNumberOfPlayers];
  static const Vector_Float kBallStartingPosition;
  //---------------------//Starting Positions

  //----------------------Waiting Times
  static constexpr float kWaitingToResetPositionsTime = 25;
  static constexpr float kWaitingToResumeGameTime = 20;

  //---------------------Game Time
  static const float kGameTime;
  //---------------------//Game Time
};

#endif // PV264_PROJECT_SERVERGAMECONSTANTS_H
