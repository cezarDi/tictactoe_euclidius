#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <toml.hpp>

#include "logger.h"
#include "game.h"

class Server {
public:
    Server(const std::string& config_file) {
        parse_config(config_file);

        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        server_addr = new_sockaddr(port);

        if (server_fd < 0) {
            logger.log(ERROR, "Failed to create server socket.");
            return;
        } else {
            logger.log(INFO, "Server socket was successfully created.");
        }


        if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
            logger.log(ERROR, "Failed to bind to port.");
            return;
        } else {
            logger.log(INFO, "Port was binded successfully.");
        }


        if (listen(server_fd, max_clients) != 0) {
            logger.log(ERROR, "Listen failed.\n");
            return;
        }


        logger.log(INFO, "Waiting for a client to connect...");
    }


    ~Server() {
        logger.log(INFO, "Shutting server down.");
        close(server_fd);
    }


    void handle_connection() {

    }

private:
    Logger logger;
    unsigned int port;
    unsigned int max_clients = 2;
    int server_fd;
    struct sockaddr_in server_addr;

    struct sockaddr_in new_sockaddr(int port) {
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        return server_addr;
    }

    void parse_config(const std::string& config_file) {
        auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

        port = toml::find<unsigned int>(data, "port");

        std::string log_file = toml::find<std::string>(data, "log_file");
        logger.setLogFile(log_file);
    }
};
