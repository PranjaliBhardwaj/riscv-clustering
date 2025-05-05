
#include "test_utils.h"
#include <stdio.h>
#include <math.h>

bool compare_double(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

bool compare_arrays(const double* a, const double* b, uint32_t size, double epsilon) {
    for (uint32_t i = 0; i < size; i++) {
        if (!compare_double(a[i], b[i], epsilon)) {
            return false;
        }
    }
    return true;
}

void print_data_point(const double* point, uint32_t dimensions) {
    printf("[");
    for (uint32_t i = 0; i < dimensions; i++) {
        printf("%.4f%s", point[i], (i < dimensions-1) ? ", " : "");
    }
    printf("]");
}
