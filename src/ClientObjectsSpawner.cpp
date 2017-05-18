#include "ClientObjectsSpawner.h"
#include "Constants/GameConstants.h"

Id spawnButton(EngineType_Client& gameEngine, const std::string& tag, const std::string& upTag,
               const std::string& downTag, Vector_Float position,const std::string& text){

    Id id = gameEngine.spawnGameObject(tag);
    gameEngine.addComponent<Button>(id, upTag, downTag);
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kButtonSpriteOffset, ClientGameConstants::kButtonSpritePath,
                                    ClientGameConstants::kButtonLayer, ClientGameConstants::kMenuEnabledAtStart);
    gameEngine.addComponent<Label>(id, ClientGameConstants::kButtonLabelOffset, text,
                                   ClientGameConstants::kButtonFontPath, ClientGameConstants::kButtonFontColor,
                                   ClientGameConstants::kButtonFontSize, ClientGameConstants::kButtonLayer,
                                   ClientGameConstants::kMenuEnabledAtStart);
    return id;
}

Id spawnPlayer_Client(EngineType_Client& gameEngine){
    Id id = gameEngine.spawnGameObject("player");
    gameEngine.addComponent<Transform>(id);
    gameEngine.addComponent<NetworkId>(id);

    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kPlayerSpriteOffset, ClientGameConstants::kPlayerSpriteLayer,
    ClientGameConstants::kPlayerEnabledAtStart);

    gameEngine.addComponent<Label>(id, ClientGameConstants::kPlayerLabelOffset, ClientGameConstants::kPlayerLabelFontPath,
    ClientGameConstants::kPlayerLabelFontColor, ClientGameConstants::kPlayerLabelFontSize, ClientGameConstants::kPlayerLabelLayer,
    ClientGameConstants::kPlayerEnabledAtStart);

    return id;
}

Id spawnBall_Client(EngineType_Client& gameEngine){
    Id id = gameEngine.spawnGameObject("ball");
    gameEngine.addComponent<Transform>(id);
    gameEngine.addComponent<NetworkId>(id, 0);

    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kBallSpriteOffset, ClientGameConstants::kBallSpritePath, ClientGameConstants::kBallSpriteLayer,
                                    ClientGameConstants::kBallEnabledAtStart);
    return id;
}

Id spawnMenuPanel(EngineType_Client &gameEngine) {
    Id id = gameEngine.spawnGameObject("menuPanel");
    gameEngine.addComponent<Transform>(id, ClientGameConstants::kMenuPanelPosition);
    gameEngine.addComponent<RectangleShape>(id, ClientGameConstants::kMenuPanelXOffset, ClientGameConstants::kMenuPanelYOffset,
    ClientGameConstants::kMenuPanelWidth, ClientGameConstants::kMenuPanelHeight, ClientGameConstants::kMenuPanelColor,
    ClientGameConstants::kMenuPanelLayer, ClientGameConstants::kMenuEnabledAtStart);
    return id;
}

Id spawnSelectionArrow(EngineType_Client &gameEngine) {
    Id id = gameEngine.spawnGameObject("arrow");
    gameEngine.addComponent<Transform>(id);
    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kArrowSpriteOffset, ClientGameConstants::kArrowSpritePath, ClientGameConstants::kArrowSpriteLayer,
    ClientGameConstants::kArrowEnabledAtStart);
    return id;
}

Id spawnPitch(EngineType_Client &gameEngine) {
    Id id = gameEngine.spawnGameObject("pitch");
    gameEngine.addComponent<Transform>(id, ClientGameConstants::kPitchPos);
    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kPitchSpriteOffset, ClientGameConstants::kPitchSpritePath, ClientGameConstants::kPitchSpriteLayer,
                                    ClientGameConstants::kPitchEnabledAtStart);
    return id;
}

Id spawnManager_Client(EngineType_Client &gameEngine) {
    Id id = gameEngine.spawnGameObject();
    gameEngine.addComponent<MovementInputHolder>(id);
    gameEngine.addComponent<GameStateChange>(id);
    return id;
}



Id spawnLabel(EngineType_Client &gameEngine, const std::string& tag, const std::string& text) {
    Id id = gameEngine.spawnGameObject(tag);
    gameEngine.addComponent<Transform>(id, ClientGameConstants::kLabelPosition);
    gameEngine.addComponent<Label>(id, ClientGameConstants::kLabelOffset, text, ClientGameConstants::kLabelFontPath,
    ClientGameConstants::kLabelFontColor, ClientGameConstants::kLabelFontSize, ClientGameConstants::kLabelLayer, false);
    return id;
}

