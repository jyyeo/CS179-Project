#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#include "findMin.cuh"

int main(void) {
	int size = 10;
	float *arr;
	float *max_val;

	arr = (float*)malloc(size * sizeof(float));
	max_val = (float*)malloc(sizeof(float));

	for (int i = 0; i < size; i++) {
		arr[i] = (size - i) * 1.5;
		printf("%f ", arr[i]);
	}
	printf("\n");

 	cudaFindMin(arr, size, max_val);

 	for (int i = 0; i < size; i++) {
		arr[i] = (size - i) * 1.5;
		printf("%f ", arr[i]);
	}
	printf("\n");

 	printf("completed\n");
 	printf("%f\n", *max_val);

	free(arr);
	free(max_val);
 }
