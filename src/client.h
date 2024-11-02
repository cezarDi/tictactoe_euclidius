#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <toml.hpp>

#include "logger.h"
#include "player.h"

class Client {
public:
    Client(const char* config_file) {
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
    }

    ~Client() {
        logger.log(INFO, "Shutting client down.");
        close(client_fd);
    }

    void parse_config(const std::string& config_file) {
        auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

        server_ip = toml::find<std::string>(data, "server_ip").c_str();
        unsigned int port = toml::find<unsigned int>(data, "port");
        std::string log_file = toml::find<std::string>(data, "log_file");
        logger.setLogFile(log_file);
    }

private:
    int client_fd;
    unsigned int port;
    Logger logger;
    const char* server_ip;
    struct sockaddr_in server_addr;


    Player player;

    struct sockaddr_in new_sockaddr(int port, const char* server_ip) {
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

        return server_addr;
    }
};
