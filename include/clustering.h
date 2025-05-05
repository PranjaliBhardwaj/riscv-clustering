#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <stdint.h>

#define MAX_DIMENSIONS 8
#define MAX_DATA_POINTS 1024
#define MAX_CLUSTERS 10

typedef struct {
    double values[MAX_DIMENSIONS];
} DataPoint;

typedef struct {
    DataPoint centroid;
    uint32_t count;
} Cluster;

void normalize_data(DataPoint* data, uint32_t num_points, uint32_t dimensions);
uint32_t determine_optimal_k(DataPoint* data, uint32_t num_points, uint32_t dimensions);
void kmeans_clustering(DataPoint* data, uint32_t num_points, 
                      uint32_t dimensions, uint32_t k, Cluster* clusters);

// Performance counters
extern uint64_t cycle_count;
extern uint64_t inst_count;

#endif
