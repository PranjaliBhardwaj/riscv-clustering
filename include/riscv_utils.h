#ifndef RISCV_UTILS_H
#define RISCV_UTILS_H

#include <stdint.h>


double riscv_euclidean_distance(const double* a, const double* b, uint32_t dim);

void riscv_matrix_mean(double* output, const double* input, 
                      uint32_t rows, uint32_t cols, uint32_t stride);


void riscv_start_counters();
void riscv_stop_counters();

#endif
