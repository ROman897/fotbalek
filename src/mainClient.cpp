
#include "ClientObjectsSpawner.h"

int main() {
    namespace hana = boost::hana;
    using namespace hana::literals;

    // example usage of how this model works

    //settings set;

    // define which systems will the engine use

    // define full settings of the engine


    PlayerClient client;
    client.connect(ClientGameConstants::kServerAddress, ClientGameConstants::kServerPort);

    EngineType_Client gameEngine;
    Id id = gameEngine.spawnGameObject();
    Id id2 = gameEngine.spawnGameObject();
    Vector_Float pos = {23.47f ,200};
    Vector_Float pos2 = {700, 200};
    gameEngine.addComponent<Transform>(id, pos);
    SDL_Color color = {.r = 255, .g = 0, .b = 0, .a = 255};
    SDL_Color color2 = {.r = 0, .g = 255, .b = 0, .a = 255};
    gameEngine.addComponent<RectangleShape>(id, -100, -100, 200, 200, color, FOREGROUND, true );
    gameEngine.addComponent<Transform>(id2, pos2);
    gameEngine.addComponent<RectangleShape>(id2, -50, -50, 100, 100, color2, FOREGROUND, true);
    Vector_Float vel = {50.0f, 0.0f};
    Vector_Float force = {0.0f, 0.0f};

    gameEngine.addComponent<RigidBody>(id, 1.0f, 10.0f, vel, force, 1.001f);
    gameEngine.addComponent<NetworkId>(id, 1);
    gameEngine.addComponent<MovementInputHolder>(id);

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
    gameEngine.addComponent<Sprite>(pitchId, spriteOffset, ClientGameConstants::kPitchSpritePath, BACKGROUND, true);


    Id arrowId = gameEngine.spawnGameObject("arrow");
    Vector_Float arrowPos = {200, 200};
    gameEngine.addComponent<Transform>(arrowId, arrowPos);
    gameEngine.addComponent<Sprite>(arrowId);

    Vector_Float continuePos = {400, 100 };
    Vector_Float optionsPos = {400, 200 };
    Vector_Float quitPos = {400, 300 };
    Id activeButtonId = spawnButton(gameEngine, "continue", "", "", continuePos, "CONTINUE");
    spawnButton(gameEngine, "options", "", "", optionsPos, "OPTIONS");
    spawnButton(gameEngine, "quit", "", "", quitPos, "QUIT");
    auto& inputSystem = gameEngine.template getSystem<InputSystem<settings >>();
    inputSystem.setActiveButton(activeButtonId);
    auto& clientSender = gameEngine.getSystem<PlaynerNetworkSenderSystem<settings>>();
    clientSender.setPlayerClient(&client);
    spawnMenuPanel(gameEngine);
    //spawnBarrier(gameEngine)

    //auto& graphicSystem =  gameEngine.getSystem<GraphicSystem<settings >>();
    //auto& physicSystem = gameEngine.getSystem<PhysicSystem<settings >>();
    //graphicSystem.initialize();


    /*while (true) {
        graphicSystem.draw();
        physicSystem.runPhysicUpdate(0.1f);

    }*/
    gameEngine.start();


}