
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>
#include <stdbool.h>

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("TEST FAILED: %s (%s:%d)\n", msg, __FILE__, __LINE__); \
            return false; \
        } \
    } while (0)

bool compare_double(double a, double b, double epsilon);
bool compare_arrays(const double* a, const double* b, uint32_t size, double epsilon);
void print_data_point(const double* point, uint32_t dimensions);

#endif
