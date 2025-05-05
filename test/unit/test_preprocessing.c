#include "test_utils.h"
#include "clustering.h"
#include "test_data.h"
#include <stdio.h>

bool test_normalization_2d() {
    DataPoint data[simple_test_data_count];
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        data[i] = simple_test_data[i];
    }
    
    normalize_data(data, simple_test_data_count, 2);
    
    
    double sum_x = 0.0, sum_y = 0.0;
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        sum_x += data[i].values[0];
        sum_y += data[i].values[1];
    }
    
    TEST_ASSERT(fabs(sum_x) < 1e-10, "X mean should be ~0 after normalization");
    TEST_ASSERT(fabs(sum_y) < 1e-10, "Y mean should be ~0 after normalization");
    
    
    double var_x = 0.0, var_y = 0.0;
    for (uint32_t i = 0; i < simple_test_data_count; i++) {
        var_x += data[i].values[0] * data[i].values[0];
        var_y += data[i].values[1] * data[i].values[1];
    }
    var_x /= simple_test_data_count;
    var_y /= simple_test_data_count;
    
    TEST_ASSERT(fabs(var_x - 1.0) < 0.1, "X variance should be ~1 after normalization");
    TEST_ASSERT(fabs(var_y - 1.0) < 0.1, "Y variance should be ~1 after normalization");
    
    return true;
}

bool test_normalization_high_dim() {
    DataPoint data[high_dim_test_data_count];
    for (uint32_t i = 0; i < high_dim_test_data_count; i++) {
        data[i] = high_dim_test_data[i];
    }
    
    normalize_data(data, high_dim_test_data_count, 4);
    
    
    double sums[4] = {0};
    for (uint32_t i = 0; i < high_dim_test_data_count; i++) {
        for (uint32_t d = 0; d < 4; d++) {
            sums[d] += data[i].values[d];
        }
    }
    
    for (uint32_t d = 0; d < 4; d++) {
        TEST_ASSERT(fabs(sums[d]) < 1e-10, "All means should be ~0 after normalization");
    }
    
    return true;
}

int main() {
    printf("Running preprocessing tests...\n");
    
    if (test_normalization_2d()) {
        printf("2D normalization test PASSED\n");
    }
    
    if (test_normalization_high_dim()) {
        printf("High-dim normalization test PASSED\n");
    }
    
    return 0;
}
