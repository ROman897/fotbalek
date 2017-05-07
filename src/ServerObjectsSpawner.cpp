//
// Created by pnavratil on 5/4/17.
//

#include "ServerObjectsSpawner.h"

Id spawnPlayer_Server(EngineType_Server &gameEngine) {
    Id id = gameEngine.spawnGameObject("player");
    gameEngine.addComponent<Transform>(id);
    gameEngine.addComponent<NetworkId>(id);
    //gameEngine.addComponent<CircleCollider>(id, ServerGameConstants::kPlayerColliderCenter, ServerGameConstants::kPlayerColliderRadius,
    //ServerGameConstants::kPlayerCollisionLayer);

    Vector_Float offset{-32, -32};
    Vector_Float offset2{32, 32};
    gameEngine.addComponent<RectangleCollider>(id, offset, offset2, ServerGameConstants::kPlayerCollisionLayer);

    gameEngine.addComponent<RigidBody>(id, ServerGameConstants::kPlayerInverseMass, ServerGameConstants::kPlayerRestitution,
                                       ServerGameConstants::kPlayerSpeedDecrement);
    gameEngine.addComponent<PlayerComp>(id);
    return id;
}

Id spawnBall_Server(EngineType_Server &gameEngine) {
    Id id = gameEngine.spawnGameObject("ball");
    gameEngine.addComponent<Transform>(id);
    gameEngine.addComponent<NetworkId>(id, 0);
    gameEngine.addComponent<CircleCollider>(id, ServerGameConstants::kBallColliderCenter, ServerGameConstants::kBallColliderRadius,
    ServerGameConstants::kBallCollisionLayer);
    gameEngine.addComponent<RigidBody>(id, ServerGameConstants::kBallInverseMass, ServerGameConstants::kBallRestitution,
                                       ServerGameConstants::kBallSpeedDecrement);
    gameEngine.addComponent<BallComp>(id);
    return id;
}

Id spawnBarrier_Server(EngineType_Server &gameEngine, Vector_Float position,
                       const Vector_Float &m_bottomRight) {
    Id id = gameEngine.spawnGameObject();
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<RectangleCollider>(id, m_bottomRight, ServerGameConstants::kBarrierCollisionLayer);
    return id;
}

Id spawnGoalTrigger_Server(EngineType_Server &gameEngine, Vector_Float position, const std::string& tag) {
    Id id = gameEngine.spawnGameObject(tag);
    gameEngine.addComponent<Transform>(id, position);
    gameEngine.addComponent<RectangleCollider>(id, ServerGameConstants::kGoalBotRight, ServerGameConstants::kGoalCollisionLayer);
    gameEngine.addComponent<ColliderTrigger>(id);
    return id;
}

Id spawnManager_Server(EngineType_Server &gameEngine) {
    Id id = gameEngine.spawnGameObject();
    gameEngine.addComponent<GameState>(id);
    gameEngine.addComponent<GameStateChange>(id);
    return id;
}
