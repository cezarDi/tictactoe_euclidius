#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <map>

#include <toml.hpp>

#include "logger.h"
#include "game.h"
#include "server.h"

Server::Server(const std::string& config_file) {
    int new_socket;
    int addr_len = sizeof(server_addr);

    parse_config(config_file);

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr = new_sockaddr(port);

    if (server_sock < 0) {
        logger.log(ERROR, "Failed to create server socket.");
        return;
    } 
    logger.log(INFO, "Server socket was successfully created.");


    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
        logger.log(ERROR, "Failed to bind to port.");
        return;
    }
    logger.log(INFO, "Port was binded successfully.");

    if (listen(server_sock, max_clients) != 0) {
        logger.log(ERROR, "Listen failed.\n");
        return;
    }
    logger.log(INFO, "Waiting for a client to connect...");

    new_socket = accept(server_sock, (struct sockaddr *)&server_addr, (socklen_t*)&addr_len);

    if (new_socket < 0) {
        logger.log(ERROR, "Accept failed.");
        perror("Accept failed.");
        close(server_sock);
        return;
    } 

    logger.log(INFO, "Client connected.");

    
    auth_user(new_socket);

    /* read(new_socket, buffer, buffer_size); */
    /* std::cout << "Received message: " << buffer << std::endl; */
}

void Server::auth_user(int new_socket) {
    int buffer_size = 2048;
    char buffer[2048];

    std::string input_login;
    std::string input_password;
    const char* space_pos;

    read(new_socket, buffer, buffer_size);

    space_pos = strchr(buffer, ' ');
    input_login.assign(buffer, space_pos - buffer);
    input_password.assign(space_pos + 1);

    logger.log(INFO, "User " + input_login + " trying to connect.");
    auto lt = users.find(input_login);
    if (lt == users.end()) {
        send(new_socket, "-1", 3, 0); //send -1 as error
        logger.log(INFO, "Incorrect login.");
    } else if (lt->second == input_password) {
        send(new_socket, "0", 2, 0);
        logger.log(INFO, "User " + input_login + " authenticated.");
    } else {
        send(new_socket, "-1", 3, 0); //send -1 as error
        logger.log(INFO, "Incorrect password.");
    }
}

Server::~Server() {
    logger.log(INFO, "Shutting server down.");
    close(server_sock);
}


void Server::parse_config(const std::string& config_file) {
    auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

    users = toml::find<std::map<std::string, std::string>>(data, "allowed_users");
    port = toml::find<unsigned int>(data, "port");
    std::string log_file = toml::find<std::string>(data, "log_file");
    logger.setLogFile(log_file);
}
