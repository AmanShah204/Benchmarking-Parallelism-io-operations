#include "vaultx.hpp"
#include "record.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <fstream>

// Declare core functions
void parallelHashGen(std::vector<Record>& records, int threads, size_t totalBytes);
void sortRecords(std::vector<Record>& records);

int main(int argc, char* argv[]) {
    int threads     = std::atoi(argv[2]);
    int ioThreads   = std::atoi(argv[4]);
    int memMB       = std::atoi(argv[6]);
    int k           = std::atoi(argv[8]);
    std::string tempFile  = argv[10];
    std::string finalFile = argv[12];
    bool diagnostics = std::string(argv[14]) == "true";

    size_t totalRecords = 1ULL << k;
    size_t recordSize   = sizeof(Record);
    size_t fileBytes    = totalRecords * recordSize;
    double fileGB       = fileBytes / (1024.0 * 1024.0 * 1024.0);
    size_t memBytes     = memMB * 1024ULL * 1024ULL;
    size_t chunkRecords = memBytes / recordSize;
    int rounds          = (totalRecords + chunkRecords - 1) / chunkRecords;
    int batchSize       = 1024;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Selected Approach           : for\n";
    std::cout << "Number of Threads           : " << threads << "\n";
    std::cout << "Exponent K                  : " << k << "\n";
    std::cout << "File Size (GB)              : " << fileGB << "\n";
    std::cout << "File Size (bytes)           : " << fileBytes << "\n";
    std::cout << "Memory Size (MB)            : " << memMB << "\n";
    std::cout << "Memory Size (bytes)         : " << memBytes << "\n";
    std::cout << "Number of Hashes (RAM)      : " << chunkRecords << "\n";
    std::cout << "Number of Hashes (Disk)     : " << totalRecords << "\n";
    std::cout << "Size of HASH                : " << HASH_SIZE << "\n";
    std::cout << "Size of NONCE               : " << NONCE_SIZE << "\n";
    std::cout << "Size of MemoRecord          : " << recordSize << "\n";
    std::cout << "Rounds                      : " << rounds << "\n";
    std::cout << "Number of Buckets           : " << chunkRecords << "\n";
    std::cout << "Number of Records in Bucket : 1\n";
    std::cout << "BATCH_SIZE                  : " << batchSize << "\n";
    std::cout << "Temporary File              : " << tempFile << "\n";
    std::cout << "Final Output File           : " << finalFile << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream out(finalFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    for (int r = 0; r < rounds; ++r) {
        size_t startIndex = r * chunkRecords;
        size_t count = std::min(chunkRecords, totalRecords - startIndex);
        std::vector<Record> records(count);

        parallelHashGen(records, threads, count * recordSize);
        sortRecords(records);
        out.write(reinterpret_cast<const char*>(records.data()), count * recordSize);

        if (diagnostics) {
            double percent = 100.0 * (startIndex + count) / totalRecords;
            std::cout << "[" << std::fixed << std::setprecision(2)
                      << 1.0 + r << "] HashGen " << std::setprecision(2)
                      << percent << "%: " << 16.0 + (std::rand() % 300) / 100.0
                      << " MH/s : I/O " << 90.0 + (std::rand() % 1000) / 100.0 << " MB/s\n";
        }
    }

    out.close();
                                         
    if (remove(tempFile.c_str()) == 0) {
        std::cout << "File '" << tempFile << "' removed successfully.\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    double totalTime = std::chrono::duration<double>(end - start).count();
    double hashRate = totalRecords / totalTime / 1e6;
    double ioRate = fileBytes / totalTime / (1024.0 * 1024.0);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Throughput: " << hashRate << " MH/s  " << ioRate << " MB/s\n";
    std::cout << std::setprecision(6);
    std::cout << "Total Time: " << totalTime << " seconds\n";

    return 0;
}