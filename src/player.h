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

    void set_time_per_move(int seconds) {
        seconds_per_move_ = seconds;
    }

    bool is_input_available();

    /*
     * Gets the pair (x, y) to move
     * 1 <= x, y <= 4
     */
    std::pair<char, char> get_move_position();


private:
    void parse_config(const std::string& config_file);
    bool order;
    int seconds_per_move_;
    std::string login;
    std::string password;
};
