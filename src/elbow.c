#include "clustering.h"
#include <math.h>

uint32_t determine_optimal_k(DataPoint* data, uint32_t num_points, uint32_t dimensions) {
    const uint32_t k_min = 1;
    const uint32_t k_max = (num_points < 10) ? num_points : 10;
    double wcss[MAX_CLUSTERS] = {0};
    
    Cluster test_clusters[MAX_CLUSTERS];
    
    for (uint32_t k = k_min; k <= k_max; k++) {
        kmeans_clustering(data, num_points, dimensions, k, test_clusters);
        
        
        for (uint32_t i = 0; i < num_points; i++) {
            uint32_t c = 0;
            double min_dist = INFINITY;
            
            
            for (uint32_t j = 0; j < k; j++) {
                double dist = riscv_euclidean_distance(
                    data[i].values, test_clusters[j].centroid.values, dimensions);
                
                if (dist < min_dist) {
                    min_dist = dist;
                    c = j;
                }
            }
            
            wcss[k-1] += min_dist * min_dist;
        }
    }
    
    
    uint32_t best_k = 1;
    double max_reduction = 0;
    
    for (uint32_t k = 1; k < k_max; k++) {
        double reduction = (wcss[k-1] - wcss[k]) / wcss[k-1];
        if (reduction > max_reduction) {
            max_reduction = reduction;
            best_k = k+1;
        }
    }
    
    return best_k;
}
