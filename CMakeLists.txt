cmake_minimum_required(VERSION 3.0.0)
project(sk2_project_server VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options("--std=c++2a" "-W" "-Wall" "-Wextra" "-pedantic" "-Werror")
add_subdirectory(src)

add_executable(main
    src/events/EpollController
    src/net/Server
    src/net/NettyClient
    $<TARGET_OBJECTS:Buffer>
    src/game/core/GameConfig
    src/game/core/Logger
    src/game/core/Unit
    $<TARGET_OBJECTS:messageHelper>
    $<TARGET_OBJECTS:PlayMessage>
    $<TARGET_OBJECTS:KickMessage>
    $<TARGET_OBJECTS:GameJoinedMessage>
    $<TARGET_OBJECTS:LobbyJoinedMessage>
    $<TARGET_OBJECTS:PlayerJoinedMessage>
    $<TARGET_OBJECTS:UnitMovedMessage>
    $<TARGET_OBJECTS:MoveUnitsMessage>
    $<TARGET_OBJECTS:AttackUnitsMessage>
    $<TARGET_OBJECTS:UnitAttackedMessage>
    $<TARGET_OBJECTS:UnitDestroyedMessage>
    $<TARGET_OBJECTS:UnitSpawnedMessage>
    $<TARGET_OBJECTS:PlayersScoreChangedMessage>
    src/game/core/MessageFilter
    src/game/core/UnitFactory
    src/game/core/Map
    src/game/PlayerSpawner
    $<TARGET_OBJECTS:Player>
    src/game/Game
    $<TARGET_OBJECTS:MessageIdentifier>
    $<TARGET_OBJECTS:MessageWriter>
    src/game/GameController
    $<TARGET_OBJECTS:GameMessageIdentifier>
main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
