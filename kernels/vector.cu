#include "vector.h"
#include <iostream>
#include <math.h>

// Add vector
__global__
void _cuda_add(int n, float *x, float *y) {
  int index = threadIdx.x;
  int stride = blockDim.x;
  for (int i = index; i < n; i += stride)
      y[i] = x[i] + y[i];
}

namespace Vectors {
  // Accepts
  void add(float *&x, float *&y, void(*callable)(float *&, float *&, int), int N) {
    // Allocate Unified Memory – accessible from CPU or GPU
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    callable(x, y, N);

    // Run kernel on 1M elements on the GPU
    _cuda_add<<<1, 256>>>(N, x, y);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

  }

  void free(float *&x, float *&y) {
    cudaFree(x);
    cudaFree(y);
  }
}
