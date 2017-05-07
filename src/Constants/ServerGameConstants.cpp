#include "ServerGameConstants.h"

//----------------------------Starting Positions
const Vector_Float ServerGameConstants::kStartingPositions[kMaxNumberOfPlayers] = {{20,20}, {200,200}/*, {400,400}, {600,600}*/};
const Vector_Float ServerGameConstants::kBallStartingPosition = {500, 500};
//---------------------------//Starting Positions

//---------------------Colliders
const Vector_Float ServerGameConstants::kPlayerColliderTopLeft = {-28, -28};
const Vector_Float ServerGameConstants::kPlayerColliderBottomRight = {28, 28};
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
const float ServerGameConstants::kPlayerInverseMass = 1.0f;
const float ServerGameConstants::kPlayerRestitution = 0.8f;
const float ServerGameConstants::kPlayerSpeedDecrement = 0.98f;

const float ServerGameConstants::kBallInverseMass = 2.0f;
const float ServerGameConstants::kBallRestitution = 0.6f;
const float ServerGameConstants::kBallSpeedDecrement = 0.99f;
//----------------------//Rigid Bodies

//-----------------------max Velocities
const float ServerGameConstants::kPlayerMaxVelocity = 50.0f;
const float ServerGameConstants::kBallMaxVelocity = 70.0f;
//-----------------------//max velocities

//------------------------Barriers
const float ServerGameConstants::kLeftBoundary = 50.0f;
const float ServerGameConstants::kRightBoundary = 1050.0f;
const float ServerGameConstants::kUpBoundary = 850.0f;
const float ServerGameConstants::kDownBoundary = 50.0f;
//------------------------//Barriers

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