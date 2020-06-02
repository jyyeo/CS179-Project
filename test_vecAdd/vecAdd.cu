#include "cuda_runtime.h"
#include "vecAdd.cuh"

__global__ void vecAdd (float *input1, float *input2, float *output, int size) {
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	while (tid < size) {
		output[tid] = input1[tid] +input2[tid];
		tid += blockDim.x * gridDim.x;
	}
}

void cudaVecAdd (float *input1, float *input2, float *output, int size) {
	float* dev_input1;
	float* dev_input2;
	float* dev_output;

	cudaMalloc((void**)&dev_input1, size * sizeof(float));
	cudaMalloc((void**)&dev_input2, size * sizeof(float));
	cudaMalloc((void**)&dev_output, size * sizeof(float));

	cudaMemcpy(dev_input1, input1, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_input2, input2, size * sizeof(float), cudaMemcpyHostToDevice);

	vecAdd<<<1, size>>>(dev_input1, dev_input2, dev_output, size);

	cudaDeviceSynchronize();

	cudaMemcpy(output, dev_output, size * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(dev_input1);
	cudaFree(dev_input2);
	cudaFree(dev_output);
}
