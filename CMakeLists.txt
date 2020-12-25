cmake_minimum_required(VERSION 3.0.0)
project(sk2_project_server VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(main main.cpp src/events/EpollController src/net/Server )
target_compile_options(main PRIVATE "-W" "-Wall" "-Wextra" "-pedantic" "-Werror")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(test)
