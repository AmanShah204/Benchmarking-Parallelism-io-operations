#include "record.hpp"
#include <vector>
#include <algorithm>
#include <cstring>

void sortRecords(std::vector<Record>& records) {
    std::sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
        return std::memcmp(a.hash, b.hash, HASH_SIZE) < 0;
    });
}
