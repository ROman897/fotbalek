//
// Created by pnavratil on 5/4/17.
//


#include "ServerObjectsSpawner.h"
#include "SettingsDefines.h"

int main() {
	namespace hana = boost::hana;
	using namespace hana::literals;


	UdpServer server;
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

	spawnBarrier_Server(gameEngine, ServerGameConstants::kLeftBarrier_Pos, ServerGameConstants::kSideBarrier_BotRight);
	spawnBarrier_Server(gameEngine, ServerGameConstants::kTopBarrier_Pos, ServerGameConstants::kUpDownBarrier_BotRight);
	spawnBarrier_Server(gameEngine, ServerGameConstants::kBotBarrier_Pos, ServerGameConstants::kUpDownBarrier_BotRight);
	spawnBarrier_Server(gameEngine, ServerGameConstants::kRightBarrier_Pos, ServerGameConstants::kSideBarrier_BotRight);

	spawnGoalTrigger_Server(gameEngine, ServerGameConstants::kLeftGoalPos, ServerGameConstants::kLeftGoalTag);
	spawnGoalTrigger_Server(gameEngine, ServerGameConstants::kRightGoalPos, ServerGameConstants::kRightGoalTag);

	gameEngine.start();


}