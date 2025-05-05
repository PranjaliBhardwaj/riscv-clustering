#include "clustering.h"
#include "riscv_utils.h"
#include <stdio.h>

int main() {
    // Example dataset 
    DataPoint data[MAX_DATA_POINTS] = {
        {{1.0, 2.0}}, {{1.1, 2.1}}, {{1.2, 2.0}},
        {{10.0, 11.0}}, {{10.1, 11.2}}, {{9.9, 10.9}},
        {{5.0, 5.0}}, {{5.1, 5.2}}, {{4.9, 4.8}}
    };
    uint32_t num_points = 9;
    uint32_t dimensions = 2;
    
    riscv_start_counters();
    
    
    normalize_data(data, num_points, dimensions);
    
    
    uint32_t k = determine_optimal_k(data, num_points, dimensions);
    printf("Optimal number of clusters: %u\n", k);
    
    
    Cluster clusters[MAX_CLUSTERS];
    kmeans_clustering(data, num_points, dimensions, k, clusters);
    
    riscv_stop_counters();
    
    
    printf("Clustering completed in %lu cycles, %lu instructions\n", 
           cycle_count, inst_count);
    
    for (uint32_t i = 0; i < k; i++) {
        printf("Cluster %u: Centroid (", i);
        for (uint32_t d = 0; d < dimensions; d++) {
            printf("%.2f%s", clusters[i].centroid.values[d], 
                   (d == dimensions-1) ? ")" : ", ");
        }
        printf(", Points: %u\n", clusters[i].count);
    }
    
    return 0;
}
