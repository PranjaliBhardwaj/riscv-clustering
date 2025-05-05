# Apprioiach used 
## Kmeans
K-means clustering is an unsupervised machine learning algorithm used to group similar data points into clusters. It works by iteratively assigning data points to the nearest centroid, then recalculating the centroids based on the assigned points, until the centroids no longer change significantly. The goal is to minimize the distance between data points and their assigned cluster centers. 
<br>
## Elbow Method
The elbow method is a heuristic used to determine the optimal number of clusters (k) for clustering algorithms like K-Means. It involves plotting the within-cluster sum of squares (WCSS) against the number of clusters and identifying the point where adding more clusters leads to diminishing returns, visually resembling an elbow. This "elbow" point suggests the optimal number of clusters, as further increasing the number of clusters won't significantly reduce the WCSS.
![image](https://github.com/user-attachments/assets/e3ec3d8d-09b9-4d6b-b686-687ccd632593)
<br>
## Risc v
RISC-V cores can handle complex computational tasks with customized ISAs, while RISC-V extensions enable development of simple, secure, and flexible cores for greater energy efficiency.
<br>
## Test Coverage
Unit Tests: <br>
Data normalization (2D and high-dimensional) <br>
K-means clustering (basic functionality and convergence) <br>
Optimal k determination (elbow method) <br>

Integration Tests: <br>
Full workflow from normalization to clustering <br>
Verification of end-to-end functionality <br>
Performance Tests: <br>
Cycle and instruction counts <br>
Cycles per Instruction (CPI) metric <br>
Scaling with data size <br>
## Overview
This project implements a clustering workload analysis system optimized for RISC-V architectures, specifically targeting the Olympia performance model. The system performs k-means clustering on N-dimensional data with automatic determination of the optimal number of clusters using the elbow method.
## Project Structure 
riscv-clustering/
├── include/              # Header files
│   ├── clustering.h      # Main clustering interface
│   ├── riscv_utils.h     # RISC-V optimized routines
│   └── data.h           # Data structures
├── src/                 # Source files
│   ├── main.c           # Main application
│   ├── preprocessing.c  # Data normalization
│   ├── kmeans.c         # K-means implementation
│   ├── elbow.c          # Elbow method for k determination
│   └── riscv_utils.s    # RISC-V assembly optimizations
├── tests/               # Test framework
│   ├── unit/            # Unit tests
│   ├── integration/     # Integration tests
│   ├── performance/     # Performance benchmarks
│   ├── test_utils.c     # Test utilities
│   └── test_data.h      # Test datasets
├── Makefile             # Build system
└── link.ld             # Linker script

## Prerequisite

RISC-V toolchain (riscv64-unknown-elf-gcc) <br>
Spike RISC-V simulator <br>
Proxy kernel (pk) <br>

