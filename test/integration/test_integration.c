#include "test_utils.h"
#include "clustering.h"
#include "test_data.h"
#include <stdio.h>

bool test_full_workflow() {
    DataPoint data[simple_test_data_count];
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        data[i] = simple_test_data[i];
    }
    
    
    normalize_data(data, simple_test_data_count, 2);
    
    
    uint32_t k = determine_optimal_k(data, simple_test_data_count, 2);
    TEST_ASSERT(k == 3, "Should find 3 clusters in simple test data");
    
    
    Cluster clusters[3];
    kmeans_clustering(data, simple_test_data_count, 2, k, clusters);
    

    uint32_t total_points = 0;
    for (uint32_t i = 0; i < k; i++) {
        total_points += clusters[i].count;
    }
    TEST_ASSERT(total_points == simple_test_data_count, "All points should be assigned");
    
    return true;
}

int main() {
    printf("Running integration tests...\n");
    
    if (test_full_workflow()) {
        printf("Full workflow test PASSED\n");
    }
    
    return 0;
}
