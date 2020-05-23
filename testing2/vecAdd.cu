#include <stdio.h>
#include "cuda_runtime.h"

__global__ void vecAdd (float *input1, float *input2, float *output, int size) {
	int tid = blockDim.x * gridDim.x + threadIdx.x;
	while (tid < size) {
		output[tid] = input1[tid] +input2[tid];
		tid += blockDim.x * gridDim.x;
	}
}

void cudaVecAdd (float *input1, float *input2, float *output, int size) {
	float* dev_input1;
	float* dev_input2;
	float* dec_input3;

	cudaMalloc((void**)&dev_input1, size * sizeof(float));
	cudaMalloc((void**)&dev_input2, size * sizeof(float));
	cudaMalloc((void**)&dev_output, size * sizeof(float));

	cudaMemcpy(dev_input1, input1, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_input2, input2, size * sizeof(float), cudaMemcpyHostToDevice);

	vecAdd<<<1, size>>>(dev_input1, dev_input2, dev_output, size);

	cudaMemcpy(output, dev_output, size * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(dev_input1);
	cudaFree(dev_input2);
	cudaFree(dev_output);
}

int main(void) {
	float *input1, *input2, *output;
	int size = 10;

	input1 = (float*)malloc(size * sizeof(float));
	input2 = (float*)malloc(size * sizeof(float));

	for (int i = 0; i < size; i++) {
		input1[i] = i + 0.5;
		input2[i] = i + 1.5;
	}

	cudaVecAdd(input1, input2, output, size);

	for (int i = 0; i < size; i++) {
		printf("%f  %f\n", input1[i]+input2[i], output[i]);
	}
}