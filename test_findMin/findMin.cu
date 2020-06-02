#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include "cuda_runtime.h"
#include "findMin.cuh"

// __device__ static float atomicMin(float* address, float val) {
//     int* address_as_i = (int*) address;
//     int old = *address_as_i, assumed;
//     do {
//         assumed = old;
//         old = ::atomicCAS(address_as_i, assumed,
//             __float_as_int(::fminf(val, __int_as_float(assumed))));
//     } while (assumed != old);
//     return __int_as_float(old);
// }

__device__ __forceinline__ float atomicMin (float * addr, float value) {
        float old;
        old = (value >= 0) ? __int_as_float(atomicMin((int *)addr, __float_as_int(value))) :
             __uint_as_float(atomicMax((unsigned int *)addr, __float_as_uint(value)));

        return old;
}

__global__ void findMin(float *dev_arr, int size, float *dev_min_val) {
	extern __shared__ float shmem[];
	const unsigned int tid = threadIdx.x;
	unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
	while (i < size + 1) {
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
			atomicMin(dev_min_val,shmem[0]);
		}
		i += blockDim.x * gridDim.x;
	}
	if (tid == 0) {
		atomicMin(dev_min_val,shmem[0]);
	}

}

void cudaFindMin(float *arr, int size, float *min_val) {
	float *dev_arr;
	float *dev_min_val;

	cudaMalloc((void**)&dev_arr, size * sizeof(float));
	cudaMalloc((void**)&dev_min_val, sizeof(float));

	cudaMemcpy(dev_arr, arr, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemset(dev_min_val, 0.0, sizeof(float));

	float block_dim = powf(2, ceil(log2(size)));
	
	findMin<<<1, block_dim, block_dim * sizeof(float)>>>(dev_arr, size, dev_min_val);
	
	cudaMemcpy(min_val, dev_min_val, sizeof(float), cudaMemcpyDeviceToHost);	
	cudaMemcpy(arr, dev_arr, size * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(dev_arr);
	cudaFree(dev_min_val);

}
