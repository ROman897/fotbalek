//
// Created by pnavratil on 5/4/17.
//


#include "ServerObjectsSpawner.h"
#include "SettingsDefines.h"

int main() {
	namespace hana = boost::hana;
	using namespace hana::literals;


	Server server;
	server.init();
	EngineType_Server gameEngine;

	auto& senderSystem = gameEngine. getExternalSystem<ServerNetworkReceiverSystem<settings>>();
	auto& receiverSystem = gameEngine.getSystem<ServerNetworkSenderSystem<settings >>();
	senderSystem.setServer(&server);
	receiverSystem.setServer(&server);
	for (int i =0; i < ServerGameConstants::kMaxNumberOfPlayers; ++i){
		spawnPlayer_Server(gameEngine);
	}
	spawnBall_Server(gameEngine);

	spawnGoalTrigger_Server(gameEngine, ServerGameConstants::kLeftGoalPos, ServerGameConstants::kLeftGoalTag);
	spawnGoalTrigger_Server(gameEngine, ServerGameConstants::kRightGoalPos, ServerGameConstants::kRightGoalTag);

    spawnBarrier_Server(gameEngine, ServerGameConstants::kLeftTopBarrier_Pos, ServerGameConstants::kSideBarrier_TopLeft, ServerGameConstants::kSideBarrier_BotRight);
    spawnBarrier_Server(gameEngine, ServerGameConstants::kLeftBotBarrier_Pos, ServerGameConstants::kSideBarrier_TopLeft, ServerGameConstants::kSideBarrier_BotRight);
    spawnBarrier_Server(gameEngine, ServerGameConstants::kRightTopBarrier_Pos, ServerGameConstants::kSideBarrier_TopLeft, ServerGameConstants::kSideBarrier_BotRight);
    spawnBarrier_Server(gameEngine, ServerGameConstants::kRightBotBarrier_Pos, ServerGameConstants::kSideBarrier_TopLeft, ServerGameConstants::kSideBarrier_BotRight);
    spawnBarrier_Server(gameEngine, ServerGameConstants::kTopBarrier_Pos, ServerGameConstants::kUpDownBarrier_TopLeft, ServerGameConstants::kUpDownBarrier_BotRight);
    spawnBarrier_Server(gameEngine, ServerGameConstants::kBotBarrier_Pos, ServerGameConstants::kUpDownBarrier_TopLeft, ServerGameConstants::kUpDownBarrier_BotRight);

	spawnManager_Server(gameEngine);
	auto& physicSystem = gameEngine.getExternalSystem<PhysicSystem<settings >>();
	physicSystem.setBoundaries(ServerGameConstants::kLeftBoundary, ServerGameConstants::kRightBoundary,
	ServerGameConstants::kUpBoundary, ServerGameConstants::kDownBoundary);

	gameEngine.start();


}