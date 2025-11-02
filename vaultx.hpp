#pragma once
#include <cstdint>

#define NONCE_SIZE 6
#define HASH_SIZE 10

struct Record {
    uint8_t hash[HASH_SIZE];
    uint8_t nonce[NONCE_SIZE];
};
