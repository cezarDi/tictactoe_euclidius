cmake_minimum_required(VERSION 3.12)

project(tictactoe)

add_subdirectory(toml11)

add_executable(server src/server.cpp src/game.cpp src/logger.cpp)
add_executable(client src/client.cpp src/logger.cpp)

target_link_libraries(server toml11::toml11)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
