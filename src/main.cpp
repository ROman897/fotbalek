#include <iostream>
//#include "asio.hpp"
#include "Core/GameEngine.h"
#include "Core/EngineSettings.h"
#include "Components/Transform.h"
#include "Utils/declarations.h"
#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Graphic/GraphicSystem.h"
#include "Components/Physic/RigidBody.h"


// first we need to specify which components will the engine keep track of
using compSettings = ComponentSettings <Transform, RectangleShape, RigidBody>;
//compSettings comps;
// define a sample signature
using rectangleSignature = Signature <RectangleShape, Transform>;
//rectangleSignature rec;
// define which signatures will the engine use
using sigSettings = SignatureSettings <rectangleSignature >;
//sigSettings sig;
using settings = EngineSettings<compSettings , sigSettings>;
//constexpr auto ComponentSettings <Transform, RectangleShape>:: componentList;
int main() {
    namespace hana = boost::hana;
    using namespace hana::literals;

    // example usage of how this model works

    //settings set;

    // define which systems will the engine use
    using sysSettings = SystemSettings <GraphicSystem<settings >>;
    // define full settings of the engine




    GameEngine<settings, sysSettings > gameEngine;
    Id id = gameEngine.spawnGameObject();
    Vector_Float pos = {1,2};
    gameEngine.addComponent<Transform>(id, pos);
    gameEngine.addComponent<RectangleShape>(id);
    std::cout << "has component: " << gameEngine.hasComponent<RectangleShape>(id) << std::endl;
    std::cout << "has component: " << gameEngine.hasComponent<RigidBody>(id) << std::endl;
    auto& system =  gameEngine.getSystem<GraphicSystem<settings >>();
    system.getSurface("aa");
    system.initialize();
    system.draw();

}