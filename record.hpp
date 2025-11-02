#pragma once
#include "vaultx.hpp"
#include <cstring>
#include <iostream>

inline bool compareHash(const Record& a, const Record& b) {
    return std::memcmp(a.hash, b.hash, HASH_SIZE) < 0;
}

inline void printRecord(const Record& r) {
    for (int i = 0; i < HASH_SIZE; ++i) std::printf("%02x", r.hash[i]);
    std::cout << " ";
    for (int i = 0; i < NONCE_SIZE; ++i) std::printf("%02x", r.nonce[i]);
    std::cout << std::endl;
}