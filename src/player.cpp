#include <iostream>

#include "player.h"

#include <toml.hpp>

void Player::parse_config(const std::string& config_file) {
    auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

    login = toml::find<std::string>(data, "login").c_str();
    password = toml::find<std::string>(data, "password").c_str();
}


std::pair<char, char> Player::get_move_position() {
    std::pair<char, char> coords;
    do {
        std::cout << "Enter the coords where you want to place your figure:" << std::endl;
        std::cin >> coords.first >> coords.second;
    } while (coords.first < '1' || coords.first > '4' || coords.second < '1' || coords.second > '4');

    coords.first -= 1;
    coords.second -= 1;

    return coords;
}
