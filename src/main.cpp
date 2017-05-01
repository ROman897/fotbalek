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
#include "Components/Graphic/Layers/RenderingLayer_Foreground.h"
#include "Components/Graphic/Layers/RenderingLayer_Background.h"
#include "Components/Graphic/Layers/RenderingLayer_UI.h"
#include "SettingsDefines.h"
#include "Game_Logic/InputSystem.h"


template<typename... Sigs> constexpr decltype(hana::make_tuple(hana::type_c<Sigs>...)) SignatureSettings<Sigs...>::signatureList;

template<typename Settings> constexpr decltype(hana::replicate<hana::tuple_tag>(SignatureManager<Settings>::b,
                           hana::length(Settings::signatureSettings::signatureList))) SignatureManager<Settings>::m_signatures;


//auto SignatureSettings <rectangleSignature, TransformSignature >::template <>signatureList;
//constexpr auto ComponentSettings <Transform, RectangleShape>:: componentList;
int main() {
    namespace hana = boost::hana;
    using namespace hana::literals;

    // example usage of how this model works

    //settings set;

    // define which systems will the engine use
    using sysSettings = SystemSettings <GraphicSystem<settings >, PhysicSystem<settings >, InputSystem<settings>>;
    // define full settings of the engine




    GameEngine<settings, sysSettings > gameEngine;
    Id id = gameEngine.spawnGameObject();
    Id id2 = gameEngine.spawnGameObject();
    Vector_Float pos = {23.47f ,200};
    Vector_Float pos2 = {451.43f, 200};
    gameEngine.addComponent<Transform>(id, pos);
    SDL_Color color = {.r = 255, .g = 0, .b = 0, .a = 255};
    SDL_Color color2 = {.r = 0, .g = 255, .b = 0, .a = 255};
    gameEngine.addComponent<RectangleShape>(id, -100, -100, 200, 200, color );
    gameEngine.addComponent<Transform>(id2, pos2);
    gameEngine.addComponent<RectangleShape>(id2, -50, -50, 100, 100, color2);
    Vector_Float vel = {5.0f, 0.0f};
    Vector_Float force = {0.0f, 0.0f};

    gameEngine.addComponent<RigidBody>(id, 1.0f, 10.0f, vel, force, 1.001f);
    Vector_Float vel2 = {0.0f, 0.0f};
    gameEngine.addComponent<RigidBody>(id2, 0.0f, 1.0f, vel2, force, 1.001f );

    Vector_Float leftTop = {-100.0f, -100.0f};
    Vector_Float rightBot = {100.0f, 100.0f};
    gameEngine.addComponent<RectangleCollider>(id, leftTop, rightBot);

    leftTop = {-50.0f, -50.0f};
    rightBot = {50.0f, 50.0f};
    gameEngine.addComponent<RectangleCollider>(id2, leftTop, rightBot);

    Id pitchId = gameEngine.spawnGameObject();
    Vector_Float pitchPos = {0.0f, 0.0f};
    Vector_Float spriteOffset = {0.0f, 0.0f};
    gameEngine.addComponent<Transform>(pitchId, pitchPos);
    gameEngine.addComponent<Sprite>(pitchId, spriteOffset, GameConstants::kPitchSpritePath, true);

    gameEngine.addComponent<RenderingLayer_Foreground>(id);
    gameEngine.addComponent<RenderingLayer_Foreground>(id2);
    gameEngine.addComponent<RenderingLayer_Background>(pitchId);


    Id arrowId = gameEngine.spawnGameObject("arrow");
    Vector_Float arrowPos = {200, 200};
    gameEngine.addComponent<Transform>(arrowId, arrowPos);
    gameEngine.addComponent<Sprite>(arrowId);

    auto& graphicSystem =  gameEngine.getSystem<GraphicSystem<settings >>();
    auto& physicSystem = gameEngine.getSystem<PhysicSystem<settings >>();
    graphicSystem.initialize();


    while (true) {
        graphicSystem.draw();
        physicSystem.runPhysicUpdate(0.1f);

    }


}