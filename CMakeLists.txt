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
    src/game/GameConfig
    src/game/Logger
    src/game/Unit
    $<TARGET_OBJECTS:messageHelper>
    src/game/message/GameMessage
    $<TARGET_OBJECTS:PlayMessage>
    $<TARGET_OBJECTS:KickMessage>
    src/game/message/GameJoinedMessage
    src/game/message/LobbyJoinedMessage
    src/game/message/PlayerJoinedMessage
    src/game/message/UnitMovedMessage
    $<TARGET_OBJECTS:MoveUnitsMessage>
    $<TARGET_OBJECTS:AttackUnitsMessage>
    src/game/message/UnitAttackedMessage
    src/game/message/UnitDestroyedMessage
    src/game/message/UnitSpawnedMessage
    src/game/message/PlayersScoreChangedMessage
    src/game/MessageFilter
    src/game/UnitFactory
    src/game/Map
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
