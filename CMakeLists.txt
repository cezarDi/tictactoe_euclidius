cmake_minimum_required(VERSION 3.12)

project(tictactoe)
include(FetchContent)

find_package(OpenSSL REQUIRED)
add_subdirectory(toml11)

add_executable(
    server 
    src/server_main.cpp 
    src/server.cpp
    src/game.cpp
    src/logger.cpp
    src/cryptography.cpp
)

add_executable(
    client 
    src/client_main.cpp 
    src/client.cpp 
    src/logger.cpp 
    src/cryptography.cpp
    src/player.cpp
)

target_link_libraries(server toml11::toml11)
target_link_libraries(client toml11::toml11)

target_link_libraries(server OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(client OpenSSL::SSL OpenSSL::Crypto)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
