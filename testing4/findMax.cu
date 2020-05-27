#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include "cuda_runtime.h"
#include "findMax.cuh"

__global__ void findMax(float *dev_arr, int size, float *dev_output) {
	extern __shared__ float shmem[];
	int tid = threadIdx.x;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < size) {
		shmem[tid] = dev_arr[i];
	}

	__syncthreads();

	for (int s = blockDim.x / 2; s > 0; s >>= 1) {
		if (tid < s && i < size) {
			shmem[tid] = fmaxf (shmem[tid],shmem[tid + s]);
		}
	}

	__syncthreads();

	if (tid == 0) {
		dev_output[blockIdx.x] = shmem[tid];
	}
}

void cudaFindMax(float *arr, int size, float *output) {
	float *dev_arr;
	float *dev_output;

	cudaMalloc((void**)&dev_arr, size * sizeof(float));
	cudaMalloc((void**)&dev_output, size * sizeof(float));

	cudaMemcpy(dev_arr, arr, size * sizeof(float), cudaMemcpyHostToDevice);

	findMax<<<1, size>>>(dev_arr, size, dev_output);

	//std::cout << dev_output[0] << std::endl;
	cudaMemcpy(output, dev_output, size * sizeof(float), cudaMemcpyDeviceToHost);	

	cudaFree(dev_arr);
	cudaFree(dev_output);
}
