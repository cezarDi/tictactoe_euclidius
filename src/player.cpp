#include "player.h"

#include <toml.hpp>

void Player::parse_config(const std::string& config_file) {
    auto data = toml::parse(config_file, toml::spec::v(1, 1, 0));

    login = toml::find<std::string>(data, "login").c_str();
    password = toml::find<std::string>(data, "password").c_str();
}
