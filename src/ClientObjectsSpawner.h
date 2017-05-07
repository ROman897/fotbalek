//
// Created by roman on 2.5.2017.
//

#ifndef PV264_PROJECT_CLIENTOBJECTSSPAWNER_H
#define PV264_PROJECT_CLIENTOBJECTSSPAWNER_H


#include <iostream>
//#include "asio.hpp"
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
#include "Network/PlayerNetworkSenderSystem.h"
#include "Network/PlayerNetworkReceiverSystem.h"


template<typename... Sigs> constexpr decltype(hana::make_tuple(hana::type_c<Sigs>...)) SignatureSettings<Sigs...>::signatureList;

//template<typename Settings> constexpr decltype(hana::replicate<hana::tuple_tag>(SignatureManager<Settings>::b,
                                                                                //hana::length(Settings::signatureSettings::signatureList))) SignatureManager<Settings>::m_signatures;

using sysSettings = SystemSettings <GraphicSystem<settings >, PlayerLogicSystem<settings >, PlayerNetworkSenderSystem<settings>>;
using externalSysSettings = SystemSettings<PlayerNetworkReceiverSystem<settings>>;

using EngineType_Client = GameEngine<settings, sysSettings, externalSysSettings >;


Id spawnButton(EngineType_Client& gameEngine, const std::string& tag, const std::string& upTag,
               const std::string& downTag, Vector_Float position,const std::string& text);

Id spawnMenuPanel(EngineType_Client& gameEngine);

Id spawnPlayer_Client(EngineType_Client& gameEngine);

Id spawnPitch(EngineType_Client& gameEngine);

Id spawnSelectionArrow(EngineType_Client& gameEngine);

Id spawnBall_Client(EngineType_Client& gameEngine);

Id spawnBarrier(EngineType_Client& gameEngine, Vector_Float position, const Vector_Float &m_topLeft, const Vector_Float &m_bottomRight);

Id spawnManager_Client(EngineType_Client &gameEngine);

Id spawnLabel(EngineType_Client& gameEngine, const std::string& tag, const std::string& text);






#endif //PV264_PROJECT_CLIENTOBJECTSSPAWNER_H
