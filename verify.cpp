#include "vaultx.hpp"
#include "record.hpp"
#include <fstream>
#include <cstring>

bool verifySorted(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    Record prev, curr;

    if (!in.read(reinterpret_cast<char*>(&prev), sizeof(Record))) return true;

    while (in.read(reinterpret_cast<char*>(&curr), sizeof(Record))) {
        if (std::memcmp(prev.hash, curr.hash, HASH_SIZE) > 0) {
            printRecord(prev);
            printRecord(curr);
            return false;
        }
        std::memcpy(&prev, &curr, sizeof(Record));
    }
    return true;
}
