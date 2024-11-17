#pragma once
#include <iostream>
#include <openssl/sha.h>
#include <string>

struct rsa_pair {


};

std::string sha256(const std::string& str);
void generate_rsa_keys();
