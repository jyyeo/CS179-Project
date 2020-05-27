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

	for (int j = 1; j < blockDim.x; j *= 2) {
		if (tid % (2*j) == 0) {
			shmem[tid] = fminf (shmem[tid],shmem[tid + j]);
		}
	}

	__syncthreads();

	if (tid == 0) {
		dev_output[blockIdx.x] = shmem[0];
	}
}

void cudaFindMax(float *arr, int size, float *output) {
	float *dev_arr;
	float *dev_output;

	cudaMalloc((void**)&dev_arr, size * sizeof(float));
	cudaMalloc((void**)&dev_output, size * sizeof(float));

	cudaMemcpy(dev_arr, arr, size * sizeof(float), cudaMemcpyHostToDevice);

	findMax<<<1, size>>>(dev_arr, size, dev_output);

	cudaMemcpy(output, dev_output, size * sizeof(float), cudaMemcpyDeviceToHost);	

	cudaFree(dev_arr);
	cudaFree(dev_output);
}