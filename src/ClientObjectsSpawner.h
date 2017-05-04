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
#include "Game_Logic/InputSystem.h"
#include "Network/PlayerNetworkSenderSystem.h"


template<typename... Sigs> constexpr decltype(hana::make_tuple(hana::type_c<Sigs>...)) SignatureSettings<Sigs...>::signatureList;

//template<typename Settings> constexpr decltype(hana::replicate<hana::tuple_tag>(SignatureManager<Settings>::b,
                                                                                //hana::length(Settings::signatureSettings::signatureList))) SignatureManager<Settings>::m_signatures;

using sysSettings = SystemSettings <GraphicSystem<settings >, InputSystem<settings >, PlaynerNetworkSenderSystem<settings>>;
using externalSysSettings = SystemSettings<PhysicSystem<settings >>;

using EngineType_Client = GameEngine<settings, sysSettings, externalSysSettings >;


Id spawnButton(EngineType_Client& gameEngine, const std::string& tag, const std::string& upTag,
               const std::string& downTag, Vector_Float position,const std::string& text);

Id spawnMenuPanel(EngineType_Client& gameEngine);

Id spawnPlayer(EngineType_Client& gameEngine);


Id spawnBall(EngineType_Client& gameEngine);

Id spawnBarrier(EngineType_Client& gameEngine, Vector_Float position, const Vector_Float &m_topLeft, const Vector_Float &m_bottomRight);






#endif //PV264_PROJECT_CLIENTOBJECTSSPAWNER_H
