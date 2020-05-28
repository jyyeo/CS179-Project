#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include "cuda_runtime.h"
#include "findMax.cuh"

__device__ static float atomicMax(float* address, float val) {
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do {
        assumed = old;
        old = ::atomicCAS(address_as_i, assumed,
            __float_as_int(::fmaxf(val, __int_as_float(assumed))));
    } while (assumed != old);
    return __int_as_float(old);
}

__global__ void findMax(float *dev_arr, int size, float *dev_max_val) {
	extern __shared__ float shmem[];
	int tid = threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	while (i < size) {
		shmem[tid] = dev_arr[tid];

		__syncthreads();

		for (int s = blockDim.x; s > 1; s >>= 1) {
			if (tid < s) {
				if (shmem[tid] < shmem[tid + s]) {
					shmem[tid] = shmem[tid + s];
				}
			}
			__syncthreads();
		}

		if (tid == 0) {
			atomicMax(dev_max_val,shmem[0]);
		}
		i += blockDim.x * gridDim.x;
	}
}

void cudaFindMax(float *arr, int size, float *max_val) {
	float *dev_arr;
	float *dev_max_val;

	cudaMalloc((void**)&dev_arr, size * sizeof(float));
	cudaMalloc((void**)&dev_max_val, 1 * sizeof(float));

	cudaMemcpy(dev_arr, arr, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemset(dev_max_val, 0, sizeof(float));

	findMax<<<1, size>>>(dev_arr, size, dev_max_val);

	//std::cout << dev_output[0] << std::endl;
	cudaMemcpy(&max_val, &dev_max_val, 1 * sizeof(float), cudaMemcpyDeviceToHost);	

	cudaFree(dev_arr);
	cudaFree(dev_max_val);
}
