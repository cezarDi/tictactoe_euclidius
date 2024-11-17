#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <toml.hpp>

#include "logger.h"

#include "player.h"
#include "client.h"
#include "cryptography.h"

Client::Client(const char* config_file): player(config_file) {
    parse_config(config_file);
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr = new_sockaddr(port, server_ip);

    if (client_fd < 0) {
        logger.log(ERROR, "Failed to create client socket.");
        return;
    } else {
        logger.log(INFO, "Client socket was successfully created.");
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        logger.log(ERROR, "Failed to connect to server.");
        return;
    } else {
        logger.log(INFO, "Connected to server successfully.");
    }

    if (authenticate() == FAIL) {
        logger.log(ERROR, "Invalid login or password.");
    }
}


Client::~Client() {
    logger.log(INFO, "Shutting client down.");
    close(client_fd);
}

void Client::parse_config(const std::string& config_file) {
    auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

    server_ip = toml::find<std::string>(data, "server_ip").c_str();
    port = toml::find<unsigned int>(data, "port");
    std::string log_file = toml::find<std::string>(data, "log_file");
    logger.setLogFile(log_file);
}

auth_e Client::authenticate() {
    std::string password_hash = sha256(player.get_password());
    std::string login = player.get_login();
    char recv_buf[5];

    std::string to_send = login + " "+ password_hash;

    send(client_fd, to_send.c_str(), to_send.length(), 0);
    read(client_fd, recv_buf, 5);
    
    if (strcmp(recv_buf, "-1") == 0) {
        logger.log(ERROR, "Wrong login or password.");
        return FAIL;
    } else {
        logger.log(INFO, "Authenticated successfully.");
        return SUCCESS;
    }
}

