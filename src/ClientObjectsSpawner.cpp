#include "ClientObjectsSpawner.h"
#include "Utils/GameConstants.h"

Id spawnButton(EngineType& gameEngine, bool selected, bool enabled, const std::string& tag, const std::string& upTag,
               const std::string& downTag, Vector_Float position,const std::string& text){

    Id id = gameEngine.spawnGameObject(tag);
    gameEngine.addComponent<Button>(id, upTag, downTag, selected);
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<Sprite>(id, GameConstants::kButtonSpriteOffset, GameConstants::kButtonSpritePath, enabled);
    gameEngine.addComponent<Label>(id, GameConstants::kButtonLabelOffset, text,
    GameConstants::kButtonFontPath, GameConstants::kButtonFontColor, GameConstants::kButtonFontSize, enabled);
    gameEngine.addComponent<RenderingLayer_UI>(id);
    return id;
}

Id spawnPlayer(EngineType& gameEngine){

}

Id spawnBall(EngineType& gameEngine){

}

Id spawnBarrier(EngineType& gameEngine){

}

