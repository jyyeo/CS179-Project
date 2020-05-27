#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#include "findMax.cuh"

int main(void) {
	int size = 10;
	float *arr;
	float *output;

	arr = (float*)malloc(size * sizeof(float));
	output = (float*)malloc(size * sizeof(float));

	for (int i = 0; i < size; i++) {
		arr[i] = (size - i) * 1.5;
		printf("%f ", arr[i]);
	}
	printf("\n");
 	
 	cudaFindMax(arr, size, output);
 	printf("completed\n");

	for (int i = 0; i < size; i++) {
		printf("%f\n", output[0]);
	}
	printf("\n");

	free(arr);
	free(output);
 }
