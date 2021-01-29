cmake_minimum_required(VERSION 3.0.0)
project(sk2_project_server VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(main main.cpp
src/events/EpollController
src/net/Server
src/net/Client
src/net/Buffer
src/game/GameConfig
src/game/Logger
src/game/Unit
src/game/message/messageHelper
src/game/message/SimpleMessageOut
src/game/message/GameMessage
src/game/message/KickMessage
src/game/message/PlayMessage
src/game/message/GameJoinedMessage
src/game/message/LobbyJoinedMessage
src/game/message/PlayerJoinedMessage
src/game/message/UnitMovedMessage
src/game/message/MoveUnitsMessage
src/game/message/AttackUnitsMessage
src/game/message/UnitAttackedMessage
src/game/message/UnitDestroyedMessage
src/game/message/UnitSpawnedMessage
src/game/message/PlayersScoreChangedMessage
src/game/MessageFilter
src/game/Map
src/game/UnitFactory
src/game/PlayerSpawner
src/game/Player
src/game/Game
src/net/MessageIdentifier
src/net/MessageWriter
src/game/GameController
src/game/GameMessageIdentifier


)
target_compile_options(main PRIVATE "--std=c++2a" "-W" "-Wall" "-Wextra" "-pedantic" "-Werror")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
