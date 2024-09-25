cmake_minimum_required(VERSION 3.12)

project(tictactoe)

add_executable(server src/server.cpp src/game.cpp src/logger.cpp)
add_executable(client src/client.cpp)

