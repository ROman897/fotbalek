#include "ClientObjectsSpawner.h"
#include "Constants/GameConstants.h"

Id spawnButton(EngineType& gameEngine, const std::string& tag, const std::string& upTag,
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

Id spawnPlayer(EngineType& gameEngine){
    /*Id id = gameEngine.spawnGameObject("player");
    gameEngine.addComponent<Transform>(id, ClientGameConstants::kMenuPanelPosition);
    gameEngine.addComponent<NetworkId>(id);


    gameEngine.addComponent<RectangleShape>(id, ClientGameConstants::kMenuPanelXOffset, ClientGameConstants::kMenuPanelYOffset,
                                            ClientGameConstants::kMenuPanelWidth, ClientGameConstants::kMenuPanelHeight, ClientGameConstants::kMenuPanelColor,
                                            ClientGameConstants::kMenuPanelLayer, ClientGameConstants::kMenuEnabledAtStart);
    return id;*/
}

Id spawnBall(EngineType& gameEngine){

}

Id spawnBarrier(EngineType& gameEngine, Vector_Float position, const Vector_Float &m_topLeft, const Vector_Float &m_bottomRight){
    Id id = gameEngine.spawnGameObject();
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<RectangleCollider>(id, m_topLeft, m_bottomRight);
    return id;
}

Id spawnMenuPanel(EngineType &gameEngine) {
    Id id = gameEngine.spawnGameObject("menuPanel");
    gameEngine.addComponent<Transform>(id, ClientGameConstants::kMenuPanelPosition);
    gameEngine.addComponent<RectangleShape>(id, ClientGameConstants::kMenuPanelXOffset, ClientGameConstants::kMenuPanelYOffset,
    ClientGameConstants::kMenuPanelWidth, ClientGameConstants::kMenuPanelHeight, ClientGameConstants::kMenuPanelColor,
    ClientGameConstants::kMenuPanelLayer, ClientGameConstants::kMenuEnabledAtStart);
    return id;
}

