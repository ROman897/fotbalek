//
// Created by pnavratil on 5/4/17.
//

#ifndef PV264_PROJECT_SERVEROBJECTSSPAWNER_H
#define PV264_PROJECT_SERVEROBJECTSSPAWNER_H

#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Components/Physic/RigidBody.h"
#include "Components/Transform.h"
#include "Core/EngineSettings.h"
#include "Core/GameEngine.h"
#include "Game_Logic/PlayerLogicSystem.h"
#include "Game_Logic/ServerLogicSystem.h"
#include "Graphic/GraphicSystem.h"
#include "Network/ServerNetworkReceiverSystem.h"
#include "Network/ServerNetworkSenderSystem.h"
#include "Physic/PhysicSystem.h"
#include "SettingsDefines.h"
#include "Utils/Declarations.h"

using sysSettings_Server = SystemSettings<ServerNetworkSenderSystem<settings>,
                                          ServerLogicSystem<settings>>;
using externalSysSettings_Server =
    SystemSettings<PhysicSystem<settings>,
                   ServerNetworkReceiverSystem<settings>>;

using EngineType_Server =
    GameEngine<settings, sysSettings_Server, externalSysSettings_Server>;

Id spawnPlayer_Server(EngineType_Server &gameEngine);

Id spawnBall_Server(EngineType_Server &gameEngine);

Id spawnBarrier_Server(EngineType_Server &gameEngine, Vector_Float position,
                       const Vector_Float &topLeft,
                       const Vector_Float &m_bottomRight);

Id spawnGoalTrigger_Server(EngineType_Server &gameEngine, Vector_Float position,
                           const std::string &tag);

Id spawnManager_Server(EngineType_Server &gameEngine);

#endif // PV264_PROJECT_SERVEROBJECTSSPAWNER_H
