#include <iostream>
#include "asio.hpp"
#include "Core/GameEngine.h"
#include "Core/EngineSettings.h"
#include "Components/Transform.h"
#include "Utils/declarations.h"
#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Graphic/GraphicSystem.h"


int main() {
    namespace hana = boost::hana;
    using namespace hana::literals;

    // example usage of how this model works

    // first we need to specify which components will the engine keep track of
    using compSettings = ComponentSettings <Transform, RectangleShape>;
    // define a sample signature
    using rectangleSignature = Signature <Transform, RectangleShape>;
    // define which signatures will the engine use
    using sigSettings = SignatureSettings <rectangleSignature >;
    using settings = EngineSettings<compSettings , sigSettings>;

    // define which systems will the engine use
    using sysSettings = SystemSettings <GraphicSystem<settings >>;
    // define full settings of the engine


    GameEngine<settings, sysSettings > gameEngine;

}