#include "ServerGameConstants.h"
const Vector_Float ServerGameConstants::startingPositions[kMaxNumberOfPlayers] = {{20,20}, {200,200}/*, {400,400}, {600,600}*/};

//---------------------Colliders
const Vector_Float ServerGameConstants::kPlayerColliderCenter = {0, 0};
const float ServerGameConstants::kPlayerColliderRadius = 32;
const Vector_Float ServerGameConstants::kBallColliderCenter = {0,0};
const float ServerGameConstants::kBallColliderRadius = 20;
//---------------------//Colliders

//----------------------Rigid bodies
const float ServerGameConstants::kPlayerInverseMass = 1;
const float ServerGameConstants::kPlayerRestitution = 0.8;
const float ServerGameConstants::kPlayerSpeedDecrement = 0.7;

const float ServerGameConstants::kBallInverseMass = 2;
const float ServerGameConstants::kBallRestitution = 0.6;
const float ServerGameConstants::kBallSpeedDecrement = 0.95;
//----------------------//Rigid Bodies


//------------------------Goals
const Vector_Float ServerGameConstants::kLeftGoalPos = {850,400};
const Vector_Float ServerGameConstants::kRightGoalPos = {50,400};
const Vector_Float ServerGameConstants::kGoalBotRight = {100,50};
const std::string ServerGameConstants::kLeftGoalTag = "leftGoal";
const std::string ServerGameConstants::kRightGoalTag = "rightGoal";
//--------------------------//Goals

//---------------------Game Time
const float ServerGameConstants::kGameTime = 300;
//---------------------//Game Time