#include "ServerGameConstants.h"

//----------------------------Starting Positions
const Vector_Float ServerGameConstants::kStartingPositions[kMaxNumberOfPlayers] = {{20,20}, {200,200}/*, {400,400}, {600,600}*/};
const Vector_Float ServerGameConstants::kBallStartingPosition = {500, 500};
//---------------------------//Starting Positions

//---------------------Colliders
const Vector_Float ServerGameConstants::kPlayerColliderCenter = {0, 0};
const float ServerGameConstants::kPlayerColliderRadius = 32;
const CollisionLayers ServerGameConstants::kPlayerCollisionLayer = PLAYERS;
const Vector_Float ServerGameConstants::kBallColliderCenter = {0,0};
const float ServerGameConstants::kBallColliderRadius = 20;
const CollisionLayers ServerGameConstants::kBallCollisionLayer = BALL;
//---------------------//Colliders


//-----------------------Collision Layers
const bool ServerGameConstants::kCollisionMatrix[kNumberOfCollisionLayers][kNumberOfCollisionLayers] = {{false, true, true, false}, {true, false, true, true},
                                                               {true, true, true, false}, {false, true, false, false}};
//----------------------//Collision Layers

//----------------------Rigid bodies
const float ServerGameConstants::kPlayerInverseMass = 1000;
const float ServerGameConstants::kPlayerRestitution = 0.8;
const float ServerGameConstants::kPlayerSpeedDecrement = 0.98;

const float ServerGameConstants::kBallInverseMass = 2;
const float ServerGameConstants::kBallRestitution = 0.6;
const float ServerGameConstants::kBallSpeedDecrement = 0.99;
//----------------------//Rigid Bodies


//------------------------Goals
const Vector_Float ServerGameConstants::kLeftGoalPos = {850,400};
const Vector_Float ServerGameConstants::kRightGoalPos = {50,400};
const Vector_Float ServerGameConstants::kGoalBotRight = {100,50};
const std::string ServerGameConstants::kLeftGoalTag = "leftGoal";
const std::string ServerGameConstants::kRightGoalTag = "rightGoal";
const CollisionLayers ServerGameConstants::kGoalCollisionLayer = GOALS;
//--------------------------//Goals

//---------------------Game Time
const float ServerGameConstants::kGameTime = 300;
//---------------------//Game Time

//----------------------Barriers
const Vector_Float ServerGameConstants::kBarriersTopLeft = {0, 0};
const Vector_Float ServerGameConstants::kLeftBarrier_Pos = {0,0};
const Vector_Float ServerGameConstants::kSideBarrier_BotRight = {50, 1000};
const Vector_Float ServerGameConstants::kTopBarrier_Pos = {0, 0};
const Vector_Float ServerGameConstants::kUpDownBarrier_BotRight = {50, 800};
const Vector_Float ServerGameConstants::kBotBarrier_Pos = {0, 850};
const Vector_Float ServerGameConstants::kRightBarrier_Pos = {1000, 0};
const CollisionLayers ServerGameConstants::kBarrierCollisionLayer = BOUNDARIES;
//------------------------//Barriers