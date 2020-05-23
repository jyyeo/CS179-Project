#include <stdio.h>
#include "vecAdd.cuh"
#include <cuda_runtime.h>

int main(void) {
	float *input1, *input2, *output;
	int size = 10;

	input1 = (float*)malloc(size * sizeof(float));
	input2 = (float*)malloc(size * sizeof(float));
	output = (float*)malloc(size * sizeof(float));
	
	for (int i = 0; i < size; i++) {
		input1[i] = i + 0.5;
		input2[i] = i + 1.5;
	}

	cudaVecAdd(input1, input2, output, size);

	for (int i = 0; i < size; i++) {
		printf("%f  %f\n", input1[i]+input2[i], output[i]);
	}
}