cmake_minimum_required(VERSION 3.6)
project(pv264_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(SOURCE_FILES src/main.cpp src/Physic/PhysicSystem.h src/Components/Physic/RigidBody.h src/Utils/Vector2.h src/Utils/GameConstants.cpp src/Utils/GameConstants.h src/Utils/Timer.cpp src/Utils/Timer.h src/Physic/Collision.cpp src/Physic/Collision.h src/Components/Physic/Shapes/CircleCollider.h src/Components/Physic/Shapes/RectangleCollider.h src/Core/GameObject.h src/Core/GameEngine.h src/Core/ComponentManager.h src/Components/Graphic/Shapes/RectangleShape.h src/Components/Graphic/Shapes/CircleShape.h src/Core/EngineSettings.h src/Core/ComponentStorage.h src/Utils/declarations.h src/Components/Transform.h src/Graphic/GraphicSystem.h src/Components/Graphic/Sprite.h src/Core/SignatureManager.h src/Core/EngineStructures.h src/Components/Graphic/Label.h src/Components/Network/NetworkId.h src/Game_Logic/InputSystem.h src/Components/MovementInputHolder.h src/Network/PlayerNetworkReceiverSystem.h src/Network/PlayerNetworkSenderSystem.h src/Network/ServerNetworkSenderSystem.h src/Network/ServerNetworkReceiverSystem.h src/Components/Graphic/Camera.h src/Components/ClientMenuInputHolder.h src/Game_Logic/MenuSystem.h src/Components/UI/Button.h src/Components/Graphic/Layers/RenderingLayer_Background.h src/Components/Graphic/Layers/RenderingLayer_Foreground.h src/Components/Graphic/Layers/RenderingLayer_UI.h src/SettingsDefines.h src/ClientObjectsSpawner.h src/ClientObjectsSpawner.cpp src/Components/Physic/ColliderTrigger.h src/Network/PlayerNetworkSystem.h)

set(BOOST_ROOT /opt/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)

include_directories(${Boost_INCLUDE_DIR})
add_executable(pv264_project ${SOURCE_FILES})
target_link_libraries(pv264_project ${Boost_LIBRARIES})


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

#ADD_LIBRARY(Tetris SHARED ${SRC_FILES})
TARGET_LINK_LIBRARIES(pv264_project ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})
