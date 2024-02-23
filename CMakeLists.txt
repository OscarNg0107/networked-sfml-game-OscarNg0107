cmake_minimum_required(VERSION 3.14)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# set(CMAKE_PREFIX_PATH C:/)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Network/Server.cpp src/Network/Server.h src/Network/Client.cpp src/Network/Client.h src/UI/Text.cpp src/UI/Text.h src/GameState/Menu.cpp src/GameState/Menu.h
        src/Network/UserData.cpp src/Network/UserData.h src/GameState/PlayerInit.cpp src/GameState/PlayerInit.h src/Tilemap/FreeFuncs.cpp src/Tilemap/ImageLayer.cpp src/Tilemap/LayerGroup.cpp src/Tilemap/Map.cpp src/Tilemap/miniz.c src/Tilemap/miniz.h
        src/Tilemap/Object.cpp src/Tilemap/ObjectGroup.cpp src/Tilemap/ObjectTypes.cpp src/Tilemap/Property.cpp src/Tilemap/TileLayer.cpp src/Tilemap/Tileset.cpp src/detail/pugixml.cpp src/Tilemap/Tile.cpp src/Tilemap/Tile.h src/GameState/Lobby.cpp
        src/GameState/Lobby.h src/GameObjects/GameObject.cpp src/GameObjects/GameObject.h src/GameObjects/Character.cpp src/GameObjects/Character.h src/GameObjects/Player.cpp src/GameObjects/Player.h src/Tilemap/Tilemap.cpp src/Tilemap/Tilemap.h src/Camera/Camera.cpp src/Camera/Camera.h
        src/UI/Chatroom.cpp src/UI/Chatroom.h src/GameState/Level.cpp src/GameState/Level.h src/GameObjects/NPC.cpp src/GameObjects/NPC.h src/GameObjects/Police.cpp src/GameObjects/Police.h src/GameObjects/Bullet.cpp src/GameObjects/Bullet.h src/Network/Server.cpp src/Network/Server.h
        src/Network/Client.cpp src/Network/Client.h src/UI/PauseMenu.cpp src/UI/PauseMenu.h src/UI/matchMenu.cpp src/UI/matchMenu.h src/GameState/GameState.cpp src/GameState/GameState.h src/UI/HealthBar.cpp src/UI/HealthBar.h
        src/Tilemap/SpawnPoint.cpp src/Tilemap/SpawnPoint.h src/UI/Scoreboard.cpp src/UI/Scoreboard.h src/UI/ScoreboardBlock.cpp src/UI/ScoreboardBlock.h)
add_executable(SFMLGame ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
