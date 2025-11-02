#include "vaultx.hpp"
#include "record.hpp"
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

void searchRecords(const std::string& filename, int difficulty, int count) {
    std::ifstream in(filename, std::ios::binary);
    std::vector<Record> records;

    Record r;
    while (in.read(reinterpret_cast<char*>(&r), sizeof(Record))) {
        records.push_back(r);
    }

    for (int i = 0; i < count; ++i) {
        const Record& query = records[i * 1000]; // sample every 1000th record
        int matches = 0;
        for (const auto& rec : records) {
            if (std::memcmp(query.hash, rec.hash, difficulty) == 0) {
                ++matches;
                printRecord(rec);
            }
        }
        std::cout << "[" << i << "] difficulty=" << difficulty << " matches=" << matches << "\n";
    }
}
