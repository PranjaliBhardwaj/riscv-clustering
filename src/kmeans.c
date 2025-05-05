#include "clustering.h"
#include "riscv_utils.h"
#include <stdlib.h>
#include <float.h>

static void init_centroids(DataPoint* data, uint32_t num_points, 
                          uint32_t dimensions, uint32_t k, DataPoint* centroids) {
    
    for (uint32_t i = 0; i < k; i++) {
        uint32_t idx = rand() % num_points;
        for (uint32_t d = 0; d < dimensions; d++) {
            centroids[i].values[d] = data[idx].values[d];
        }
    }
}

void kmeans_clustering(DataPoint* data, uint32_t num_points, 
                      uint32_t dimensions, uint32_t k, Cluster* clusters) {
    DataPoint centroids[MAX_CLUSTERS];
    uint32_t assignments[MAX_DATA_POINTS];
    
    
    init_centroids(data, num_points, dimensions, k, centroids);
    
    uint32_t changed;
    uint32_t iterations = 0;
    const uint32_t max_iterations = 100;
    
    do {
        changed = 0;
        
        
        for (uint32_t i = 0; i < num_points; i++) {
            double min_dist = DBL_MAX;
            uint32_t best_cluster = 0;
            
            for (uint32_t c = 0; c < k; c++) {
                double dist = riscv_euclidean_distance(
                    data[i].values, centroids[c].values, dimensions);
                
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = c;
                }
            }
            
            if (assignments[i] != best_cluster) {
                assignments[i] = best_cluster;
                changed++;
            }
        }
        
        
        uint32_t counts[MAX_CLUSTERS] = {0};
        DataPoint sums[MAX_CLUSTERS] = {0};
        
        for (uint32_t i = 0; i < num_points; i++) {
            uint32_t c = assignments[i];
            counts[c]++;
            
            for (uint32_t d = 0; d < dimensions; d++) {
                sums[c].values[d] += data[i].values[d];
            }
        }
        
        for (uint32_t c = 0; c < k; c++) {
            if (counts[c] > 0) {
                for (uint32_t d = 0; d < dimensions; d++) {
                    centroids[c].values[d] = sums[c].values[d] / counts[c];
                }
            }
        }
        
        iterations++;
    } while (changed > 0 && iterations < max_iterations);
    
    
    for (uint32_t c = 0; c < k; c++) {
        clusters[c].count = 0;
        for (uint32_t d = 0; d < dimensions; d++) {
            clusters[c].centroid.values[d] = centroids[c].values[d];
        }
    }
    
    for (uint32_t i = 0; i < num_points; i++) {
        clusters[assignments[i]].count++;
    }
}
