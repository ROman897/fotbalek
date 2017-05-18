#include "ServerGameConstants.h"

//----------------------------Starting Positions
const Vector_Float
    ServerGameConstants::kStartingPositions[kMaxNumberOfPlayers] = {
        {300, 400}, {300, 700}};//, {700, 300}, {700, 700}}; //, {600,300},
                                                         //{600,500}};//,
                                                         //{200,200}/*,
                                                         //{400,400},
                                                         //{600,600}*/};
const Vector_Float ServerGameConstants::kBallStartingPosition = {500, 500};
//---------------------------//Starting Positions

//---------------------Colliders
const Vector_Float ServerGameConstants::kPlayerColliderTopLeft = {-28, -28};
const Vector_Float ServerGameConstants::kPlayerColliderBottomRight = {28, 28};
const CollisionLayers ServerGameConstants::kPlayerCollisionLayer = PLAYERS;
const Vector_Float ServerGameConstants::kBallColliderCenter = {0, 0};
const float ServerGameConstants::kBallColliderRadius = 20;
const CollisionLayers ServerGameConstants::kBallCollisionLayer = BALL;
//---------------------//Colliders

//-----------------------Collision Layers
const bool ServerGameConstants::kCollisionMatrix[kNumberOfCollisionLayers]
                                                [kNumberOfCollisionLayers] = {
                                                    {false, true, true, false},
                                                    {true, false, true, true},
                                                    {true, true, true, false},
                                                    {false, true, false,
                                                     false}};
//----------------------//Collision Layers

//----------------------Rigid bodies
const float ServerGameConstants::kPlayerInverseMass = 1.0f;
const float ServerGameConstants::kPlayerRestitution = 0.8f;
const float ServerGameConstants::kPlayerSpeedDecrement = 0.98f;

const float ServerGameConstants::kBallInverseMass = 4.0f;
const float ServerGameConstants::kBallRestitution = 0.4f;
const float ServerGameConstants::kBallSpeedDecrement = 0.998f;
//----------------------//Rigid Bodies

//-----------------------max Velocities
const float ServerGameConstants::kPlayerMaxVelocity = 40.0f;
const float ServerGameConstants::kBallMaxVelocity = 50.0f;
//-----------------------//max velocities

//------------------------Barriers
const float ServerGameConstants::kLeftBoundary = 50.0f;
const float ServerGameConstants::kRightBoundary = 1050.0f;
const float ServerGameConstants::kUpBoundary = 850.0f;
const float ServerGameConstants::kDownBoundary = 50.0f;
//------------------------//Barriers

//------------------------Goals
const Vector_Float ServerGameConstants::kLeftGoalPos = {50, 450};
const Vector_Float ServerGameConstants::kRightGoalPos = {1045, 450};
const Vector_Float ServerGameConstants::kGoalBotRight = {50, 200};
const std::string ServerGameConstants::kLeftGoalTag = "leftGoal";
const std::string ServerGameConstants::kRightGoalTag = "rightGoal";
const CollisionLayers ServerGameConstants::kGoalCollisionLayer = GOALS;
//--------------------------//Goals

//---------------------Game Time
const float ServerGameConstants::kGameTime = 1200;
//---------------------//Game Time

//----------------------Barriers
const Vector_Float ServerGameConstants::kLeftTopBarrier_Pos = {65, 50};
const Vector_Float ServerGameConstants::kLeftBotBarrier_Pos = {65, 850};
const Vector_Float ServerGameConstants::kSideBarrier_BotRight = {50, 600};
const Vector_Float ServerGameConstants::kSideBarrier_TopLeft = {0, 0};
const Vector_Float ServerGameConstants::kTopBarrier_Pos = {400, 45};
const Vector_Float ServerGameConstants::kUpDownBarrier_BotRight = {800, 50};
const Vector_Float ServerGameConstants::kUpDownBarrier_TopLeft = {-800, -50};
const Vector_Float ServerGameConstants::kBotBarrier_Pos = {400, 855};
const Vector_Float ServerGameConstants::kRightTopBarrier_Pos = {1030, 50};
const Vector_Float ServerGameConstants::kRightBotBarrier_Pos = {1030, 850};

const float ServerGameConstants::kBarrierInverseMass = 0.0f;
const float ServerGameConstants::kBarrierRestitution = 0.5f;
const float ServerGameConstants::kBarrierMaxVelocity = 0.0f;
const float ServerGameConstants::kBarrierSpeedDecrement = 0.0f;
const CollisionLayers ServerGameConstants::kBarrierCollisionLayer = BOUNDARIES;
//------------------------//Barriers
