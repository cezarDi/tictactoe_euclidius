#pragma once

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <map>


#include "logger.h"

class Server {
public:
    Server(const std::string& config_file);
    ~Server();

private:
    Logger logger;
    unsigned int port;
    unsigned int max_clients = 2;
    int server_sock;
    struct sockaddr_in server_addr;

    std::array<int, 2> client_sockets;
    std::map<std::string, std::string> users;


    struct sockaddr_in new_sockaddr(int port) {
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        return server_addr;
    }

    void parse_config(const std::string& config_file);
    void auth_user(int new_socket);
};
