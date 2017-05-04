#include "ClientObjectsSpawner.h"
#include "Constants/GameConstants.h"

Id spawnButton(EngineType& gameEngine, bool selected, bool enabled, const std::string& tag, const std::string& upTag,
               const std::string& downTag, Vector_Float position,const std::string& text){

    Id id = gameEngine.spawnGameObject(tag);
    gameEngine.addComponent<Button>(id, upTag, downTag, selected);
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<Sprite>(id, ClientGameConstants::kButtonSpriteOffset, ClientGameConstants::kButtonSpritePath, enabled);
    gameEngine.addComponent<Label>(id, ClientGameConstants::kButtonLabelOffset, text,
                                   ClientGameConstants::kButtonFontPath, ClientGameConstants::kButtonFontColor,
                                   ClientGameConstants::kButtonFontSize, enabled);
    gameEngine.addComponent<RenderingLayer_UI>(id);
    return id;
}

Id spawnPlayer(EngineType& gameEngine){

}

Id spawnBall(EngineType& gameEngine){

}

Id spawnBarrier(EngineType& gameEngine, Vector_Float position, const Vector_Float &m_topLeft, const Vector_Float &m_bottomRight){
    Id id = gameEngine.spawnGameObject();
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<RectangleCollider>(id, m_topLeft, m_bottomRight);
    return id;
}

