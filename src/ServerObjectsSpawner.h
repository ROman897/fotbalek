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
#include "Game_Logic/InputSystem.h"
#include "Network/ServerNetworkSenderSystem.h"
#include "Network/ServerNetworkReceiverSystem.h"

using sysSettings = SystemSettings <ServerNetworkSenderSystem<settings>, ServerNetworkReceiverSystem<settings>>;
using externalSysSettings = SystemSettings<PhysicSystem<settings >>;

using EngineType_Server = GameEngine<settings, sysSettings, externalSysSettings >;

#endif //PV264_PROJECT_SERVEROBJECTSSPAWNER_H
