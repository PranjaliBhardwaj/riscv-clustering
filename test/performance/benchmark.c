#include "clustering.h"
#include "riscv_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BENCHMARK_DATA_SIZE 1000
#define BENCHMARK_DIMENSIONS 4
#define BENCHMARK_RUNS 10

void generate_random_data(DataPoint* data, uint32_t count, uint32_t dim) {
    srand(time(NULL));
    for (uint32_t i = 0; i < count; i++) {
        for (uint32_t d = 0; d < dim; d++) {
            data[i].values[d] = (double)rand() / RAND_MAX * 10.0;
        }
    }
}

void run_benchmark() {
    DataPoint data[BENCHMARK_DATA_SIZE];
    generate_random_data(data, BENCHMARK_DATA_SIZE, BENCHMARK_DIMENSIONS);
    
    uint64_t total_cycles = 0;
    uint64_t total_instructions = 0;
    
    for (uint32_t run = 0; run < BENCHMARK_RUNS; run++) {
        riscv_start_counters();
        
        normalize_data(data, BENCHMARK_DATA_SIZE, BENCHMARK_DIMENSIONS);
        uint32_t k = determine_optimal_k(data, BENCHMARK_DATA_SIZE, BENCHMARK_DIMENSIONS);
        
        Cluster clusters[MAX_CLUSTERS];
        kmeans_clustering(data, BENCHMARK_DATA_SIZE, BENCHMARK_DIMENSIONS, k, clusters);
        
        riscv_stop_counters();
        
        total_cycles += cycle_count;
        total_instructions += inst_count;
    }
    
    printf("Performance Benchmark Results (avg over %d runs):\n", BENCHMARK_RUNS);
    printf("  Cycles: %lu\n", total_cycles / BENCHMARK_RUNS);
    printf("  Instructions: %lu\n", total_instructions / BENCHMARK_RUNS);
    printf("  CPI: %.2f\n", (double)(total_cycles) / total_instructions);
}

int main() {
    printf("Running performance benchmarks...\n");
    run_benchmark();
    return 0;
}
