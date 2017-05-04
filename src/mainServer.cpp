//
// Created by pnavratil on 5/4/17.
//


#include "ServerObjectsSpawner.h"
#include "SettingsDefines.h"

int main() {
	namespace hana = boost::hana;
	using namespace hana::literals;

	// example usage of how this model works

	//settings set;

	// define which systems will the engine use

	// define full settings of the engine

	UdpServer server;
	server.init();
	EngineType_Server gameEngine;

	auto& senderSystem = gameEngine. getExternalSystem<ServerNetworkReceiverSystem<settings>>();
	auto& receiverSystem = gameEngine.getSystem<ServerNetworkSenderSystem<settings >>();
	senderSystem.setServer(&server);
	receiverSystem.setServer(&server);
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