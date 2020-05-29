#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include "cuda_runtime.h"
#include "findMax.cuh"

__device__ static float atomicMin(float* address, float val) {
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do {
        assumed = old;
        old = ::atomicCAS(address_as_i, assumed,
            __float_as_int(::fminf(val, __int_as_float(assumed))));
    } while (assumed != old);
    return __int_as_float(old);
}

__global__ void findMax(float *dev_arr, int size, float *dev_min_val) {
	extern __shared__ float shmem[];
	const unsigned int tid = threadIdx.x;
	unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
	while (i < size) {
		shmem[tid] = dev_arr[i];

		__syncthreads();

		for (unsigned int s = blockDim.x/2; s > 0; s >>= 1) {
			if (tid < s) {
				if (shmem[tid] > shmem[tid + s]) {
					shmem[tid] = shmem[tid + s];
				}
			}
			__syncthreads();
		}

		if (tid == 0) {
			atomicMax(dev_min_val,shmem[0]);
		}
		i += blockDim.x * gridDim.x;
	}
}

void cudaFindMin(float *dev_arr, int size, float *dev_min_val) {
	
	findMax<<<1, size, size * sizeof(float)>>>(dev_arr, size, dev_min_val);

}
