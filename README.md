# Benchmarking-Parallelism-io-operations

This project focuses on benchmarking file I/O performance, concurrency, and memory utilization using C/C++ on Linux. The benchmark generates large volumes of BLAKE3 cryptographic hashes, stores them in binary files, and evaluates the performance of different system configurations.

Key features:

-Multi-threaded hash generation, sorting, and disk writing using PThreads.
-Binary file storage of sorted hash–nonce records (1 GB / 64 GB workloads).
-Controlled memory usage with tunable parameters (256 MB–64 GB).
-Automated benchmarking across 42+7 configurations using Bash scripts.
-Performance analysis including throughput, concurrency scaling, and search efficiency.

The project provides insights into how threading, I/O concurrency, and memory allocation affect end-to-end system throughput for large-scale data generation and storage.
