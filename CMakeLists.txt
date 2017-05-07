cmake_minimum_required(VERSION 3.6)
project(pv264_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
set(SOURCE_FILES src/Physic/PhysicSystem.h src/Components/Physic/RigidBody.h src/Utils/Vector2.h
        src/Utils/Timer.cpp src/Utils/Timer.h src/Physic/Collision.h
        src/Components/Physic/Shapes/CircleCollider.h src/Components/Physic/Shapes/RectangleCollider.h
        src/Core/GameObject.h src/Core/GameEngine.h src/Core/ComponentManager.h src/Components/Graphic/Shapes/RectangleShape.h
        src/Components/Graphic/Shapes/CircleShape.h src/Core/EngineSettings.h src/Core/ComponentStorage.h src/Utils/declarations.h
        src/Components/Transform.h src/Graphic/GraphicSystem.h src/Components/Graphic/Sprite.h src/Core/SignatureManager.h
        src/Core/EngineStructures.h src/Components/Graphic/Label.h src/Components/Network/NetworkId.h src/Game_Logic/PlayerLogicSystem.h
        src/Components/Logic/MovementInputHolder.h src/Network/API/Client/UdpBase.h src/SettingsDefines.h
        src/Components/UI/Button.h src/Constants/NetworkConstants.h src/Constants/NetworkConstants.cpp
        src/Components/Physic/ColliderTrigger.h src/Network/API/Client/Message.h src/Network/API/Client/Player.h
        src/Components/Logic/PlayerComp.h src/Components/Logic/BallComp.h src/Components/Network/GameStateChange.h)

SET(CONSTANTS src/Constants/ClientGameConstants.h src/Constants/ClientGameConstants.cpp
        src/Constants/ServerGameConstants.h src/Constants/ServerGameConstants.cpp
        src/Constants/GameConstants.cpp src/Constants/GameConstants.h )

set(SERVER_FILES src/Network/ServerNetworkSenderSystem.h src/Network/ServerNetworkReceiverSystem.h
        src/Game_Logic/ServerLogicSystem.h src/ServerObjectsSpawner.cpp src/Network/API/Server/Server.cpp
        src/Network/API/Server/Server.h src/ServerObjectsSpawner.h src/Components/Logic/GameState.h)

set(CLIENT_FILES src/Network/PlayerNetworkReceiverSystem.h src/Network/PlayerNetworkSenderSystem.h
        src/Network/API/Client/Client.cpp src/Network/API/Client/Client.h src/ClientObjectsSpawner.h
        src/ClientObjectsSpawner.cpp)

set(SERVER_MAIN src/mainServer.cpp)
set(CLIENT_MAIN src/mainClient.cpp src/Network/API/Client/Score.h)

set(BOOST_ROOT /opt/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)

include_directories(${Boost_INCLUDE_DIR})
add_executable(pv264_project_server ${SOURCE_FILES} ${SERVER_MAIN} ${SERVER_FILES} ${CONSTANTS})
target_link_libraries(pv264_project_server ${Boost_LIBRARIES})

add_executable(pv264_project_client ${SOURCE_FILES} ${CLIENT_MAIN} ${CLIENT_FILES} ${CONSTANTS})
target_link_libraries(pv264_project_client ${Boost_LIBRARIES})


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(pv264_project_client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
TARGET_LINK_LIBRARIES(pv264_project_server ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

TARGET_LINK_LIBRARIES(pv264_project_client ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})
TARGET_LINK_LIBRARIES(pv264_project_server ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})
