add_subdirectory(message)

add_library(GameMessageIdentifier OBJECT GameMessageIdentifier)
add_library(Player OBJECT Player)

add_executable(PlayerTest PlayerTest.cpp
    $<TARGET_OBJECTS:Buffer>
    $<TARGET_OBJECTS:MessageIdentifier>
    $<TARGET_OBJECTS:MessageWriter>
    $<TARGET_OBJECTS:messageHelper>
    $<TARGET_OBJECTS:PlayMessage>
    $<TARGET_OBJECTS:KickMessage>
    $<TARGET_OBJECTS:MoveUnitsMessage>
    $<TARGET_OBJECTS:AttackUnitsMessage>
    $<TARGET_OBJECTS:GameMessageIdentifier>
    $<TARGET_OBJECTS:Player>
)
add_test(NAME PlayerTest-returns_offline_status_of_client_true COMMAND PlayerTest returns_offline_status_of_client_true)
add_test(NAME PlayerTest-returns_offline_status_of_client_false COMMAND PlayerTest returns_offline_status_of_client_false)
add_test(NAME PlayerTest-emits_messages_when_online COMMAND PlayerTest emits_messages_when_online)
add_test(NAME PlayerTest-does_not_emit_messages_when_offline COMMAND PlayerTest does_not_emit_messages_when_offline)
add_test(NAME PlayerTest-flushes_messages_when_online COMMAND PlayerTest flushes_messages_when_online)
add_test(NAME PlayerTest-does_not_flush_messages_when_offline COMMAND PlayerTest does_not_flush_messages_when_offline)
