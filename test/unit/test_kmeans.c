#include "test_utils.h"
#include "clustering.h"
#include "test_data.h"
#include <stdio.h>

bool test_kmeans_simple_clusters() {
    DataPoint data[simple_test_data_count];
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        data[i] = simple_test_data[i];
    }
    
    Cluster clusters[3];
    kmeans_clustering(data, simple_test_data_count, 2, 3, clusters);
    
    
    uint32_t total_points = 0;
    for (uint32_t i = 0; i < 3; i++) {
        total_points += clusters[i].count;
    }
    TEST_ASSERT(total_points == simple_test_data_count, "All points should be assigned");
    
    
    bool has_small_cluster = false;
    bool has_medium_cluster = false;
    bool has_large_cluster = false;
    
    for (uint32_t i = 0; i < 3; i++) {
        if (clusters[i].count == 4) has_large_cluster = true;
        if (clusters[i].count == 3) has_medium_cluster = true;
        if (clusters[i].count == 2) has_small_cluster = true;
    }
    
    TEST_ASSERT(has_large_cluster && has_medium_cluster && has_small_cluster,
               "Should find clusters of expected sizes");
    
    return true;
}

bool test_kmeans_convergence() {
    DataPoint data[simple_test_data_count];
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        data[i] = simple_test_data[i];
    }
    
    Cluster clusters[3];
    kmeans_clustering(data, simple_test_data_count, 2, 3, clusters);
    
    
    Cluster clusters2[3];
    for (uint32_t i = 0; i < 3; i++) {
        clusters2[i].centroid = clusters[i].centroid;
    }
    
    kmeans_clustering(data, simple_test_data_count, 2, 3, clusters2);
    
    
    for (uint32_t i = 0; i < 3; i++) {
        double dist = riscv_euclidean_distance(
            clusters[i].centroid.values, 
            clusters2[i].centroid.values, 2);
        TEST_ASSERT(dist < 1e-6, "Centroids should be stable after convergence");
    }
    
    return true;
}

int main() {
    printf("Running k-means tests...\n");
    
    if (test_kmeans_simple_clusters()) {
        printf("Simple clustering test PASSED\n");
    }
    
    if (test_kmeans_convergence()) {
        printf("Convergence test PASSED\n");
    }
    
    return 0;
}
