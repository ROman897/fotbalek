//
// Created by pnavratil on 5/4/17.
//

#ifndef PV264_PROJECT_SERVEROBJECTSSPAWNER_H
#define PV264_PROJECT_SERVEROBJECTSSPAWNER_H

#include "Core/GameEngine.h"
#include "Core/EngineSettings.h"
#include "Components/Transform.h"
#include "Utils/declarations.h"
#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Graphic/GraphicSystem.h"
#include "Components/Physic/RigidBody.h"
#include "Physic/PhysicSystem.h"
#include "SettingsDefines.h"
#include "Game_Logic/PlayerLogicSystem.h"
#include "Network/ServerNetworkSenderSystem.h"
#include "Network/ServerNetworkReceiverSystem.h"

using sysSettings_Server = SystemSettings <ServerNetworkSenderSystem<settings>>;
using externalSysSettings_Server = SystemSettings<PhysicSystem<settings >, ServerNetworkReceiverSystem<settings>>;

using EngineType_Server = GameEngine<settings, sysSettings_Server, externalSysSettings_Server >;

Id spawnPlayer_Server(EngineType_Server& gameEngine);


Id spawnBall_Server(EngineType_Server& gameEngine);

Id spawnBarrier_Server(EngineType_Server& gameEngine, Vector_Float position, const Vector_Float &m_bottomRight);

Id spawnGoalTrigger_Server(EngineType_Server& gameEngine, Vector_Float position, const std::string& tag);





#endif //PV264_PROJECT_SERVEROBJECTSSPAWNER_H
