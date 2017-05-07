
#include "ClientObjectsSpawner.h"
#include "Constants/NetworkConstants.h"
#include "Network/PlayerNetworkReceiverSystem.h"

int main() {
    namespace hana = boost::hana;
    using namespace hana::literals;


    Client client;
    client.connect(NetworkConstants::kServerAddress, NetworkConstants::kServerPort);

    EngineType_Client gameEngine;


    auto& clientSender = gameEngine.getSystem<PlayerNetworkSenderSystem<settings>>();
    clientSender.setPlayerClient(&client);
    auto& clientReceiver = gameEngine.getExternalSystem<PlayerNetworkReceiverSystem<settings>>();
    clientReceiver.setPlayerClient(&client);


    spawnPitch(gameEngine);

    Id activeButtonId = spawnButton(gameEngine, ClientGameConstants::kContinueButtonTag,
    ClientGameConstants::kQuitButtonTag, ClientGameConstants::kOptionsButtonTag,
    ClientGameConstants::kContinueButtonPos, ClientGameConstants::kContinueButtonText);

    Id optionsButtonId = spawnButton(gameEngine, ClientGameConstants::kOptionsButtonTag,
                                    ClientGameConstants::kContinueButtonTag, ClientGameConstants::kQuitButtonTag,
                                    ClientGameConstants::kOptionsButtonPos, ClientGameConstants::kOptionsButtonText);
    Id QuitButtonId = spawnButton(gameEngine, ClientGameConstants::kQuitButtonTag,
                                     ClientGameConstants::kOptionsButtonTag, ClientGameConstants::kContinueButtonTag,
                                     ClientGameConstants::kQuitButtonPos, ClientGameConstants::kQuitButtonText);
    spawnMenuPanel(gameEngine);
    spawnSelectionArrow(gameEngine);
    auto& inputSystem = gameEngine.template getSystem<PlayerLogicSystem<settings >>();
    inputSystem.setActiveButton(activeButtonId);

    for (int i = 0; i < ServerGameConstants::kMaxNumberOfPlayers; ++i){
        spawnPlayer_Client(gameEngine);
    }
    spawnBall_Client(gameEngine);
    spawnManager_Client(gameEngine);
    spawnLabel(gameEngine, ClientGameConstants::kGameoverLabelTag, ClientGameConstants::kGameoverLabelText);
    spawnLabel(gameEngine, ClientGameConstants::kScored1LabelTag, ClientGameConstants::kScored1LabelText);
    spawnLabel(gameEngine, ClientGameConstants::kScored2LabelTag, ClientGameConstants::kScored2LabelText);


    gameEngine.start();


}