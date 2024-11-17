#pragma once
#include <string>



class Player {
public:
    Player(const std::string& config_file) {
        parse_config(config_file);
    }
    ~Player() {}

    std::string get_login() {
        return login;
    }

    std::string get_password() {
        return password;
    }
private:
    void parse_config(const std::string& config_file);
    bool order;
    std::string login;
    std::string password;
};
