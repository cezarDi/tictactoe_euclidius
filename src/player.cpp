#include <iostream>
#include <unistd.h>
#include "player.h"

#include <toml.hpp>

void Player::parse_config(const std::string& config_file) {
    auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

    login = toml::find<std::string>(data, "login").c_str();
    password = toml::find<std::string>(data, "password").c_str();
}

bool Player::is_input_available() {
    fd_set readfds;
    struct timeval tv;

    // Ожидаем ввода с stdin (стандартный ввод)
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    // Устанавливаем тайм-аут
    tv.tv_sec = seconds_per_move_;
    tv.tv_usec = 0;

    // Проверяем доступность ввода
    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    return ret > 0;  // Если вернулся положительный результат, значит, ввод доступен
}


std::pair<char, char> Player::get_move_position() {
    std::pair<char, char> coords;
    if (is_input_available()) {
        do {
            std::cout << "Enter the coords where you want to place your figure:" << std::endl;
            std::cin >> coords.first >> coords.second;
        } while (coords.first < '1' || coords.first > '4' || coords.second < '1' || coords.second > '4');
    }
    else {
        std::cout << "Move time expired" << std::endl;
        coords = {0, 0};
    }
    coords.first -= 1;
    coords.second -= 1;

    return coords;
}
