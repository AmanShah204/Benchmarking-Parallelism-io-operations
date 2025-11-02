#include "vaultx.hpp"
#include "record.hpp"
#include <vector>
#include <random>

void parallelHashGen(std::vector<Record>& records, int threads, size_t totalBytes) {
    std::mt19937 rng(42);
    for (auto& r : records) {
        for (int i = 0; i < HASH_SIZE; ++i) r.hash[i] = rng() % 256;
        for (int i = 0; i < NONCE_SIZE; ++i) r.nonce[i] = rng() % 256;
    }
}
