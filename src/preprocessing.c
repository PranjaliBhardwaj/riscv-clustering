#include "clustering.h"
#include "riscv_utils.h"
#include <math.h>

void normalize_data(DataPoint* data, uint32_t num_points, uint32_t dimensions) {
    double mean[MAX_DIMENSIONS] = {0};
    double stddev[MAX_DIMENSIONS] = {0};
    
    
    for (uint32_t i = 0; i < num_points; i++) {
        for (uint32_t d = 0; d < dimensions; d++) {
            mean[d] += data[i].values[d];
        }
    }
    
    for (uint32_t d = 0; d < dimensions; d++) {
        mean[d] /= num_points;
    }
    
    
    for (uint32_t i = 0; i < num_points; i++) {
        for (uint32_t d = 0; d < dimensions; d++) {
            double diff = data[i].values[d] - mean[d];
            stddev[d] += diff * diff;
        }
    }
    
    for (uint32_t d = 0; d < dimensions; d++) {
        stddev[d] = sqrt(stddev[d] / num_points);
        // Avoid division by zero for constant dimensions
        if (stddev[d] == 0.0) stddev[d] = 1.0;
    }
    
    // Normalizing data
    for (uint32_t i = 0; i < num_points; i++) {
        for (uint32_t d = 0; d < dimensions; d++) {
            data[i].values[d] = (data[i].values[d] - mean[d]) / stddev[d];
        }
    }
}
