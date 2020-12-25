add_executable(Server ServerTest.h)
target_link_libraries(Server gtest_main)
add_test(NAME ServerTest COMMAND Server)