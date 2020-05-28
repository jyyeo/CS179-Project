#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#include "findMax.cuh"

int main(void) {
	int size = 10;
	float *arr;
	float max_val;

	arr = (float*)malloc(size * sizeof(float));

	for (int i = 0; i < size; i++) {
		arr[i] = (size - i) * 1.5;
		printf("%f ", arr[i]);
	}
	printf("\n");
 	
 	float *dev_arr;
	float *dev_max_val;

	cudaMalloc((void**)&dev_arr, size * sizeof(float));
	cudaMalloc((void**)&dev_max_val, sizeof(float));

	cudaMemcpy(dev_arr, arr, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemset(dev_max_val, 0, sizeof(float));

 	cudaFindMax(dev_arr, size, dev_max_val);

 	for (int i = 0; i < size; i++) {
		arr[i] = (size - i) * 1.5;
		printf("%f ", arr[i]);
	}
	printf("\n");

 	cudaMemcpy(&max_val, dev_max_val, 1 * sizeof(float), cudaMemcpyDeviceToHost);	

 	printf("completed\n");
 	printf("%f\n", max_val);

	cudaFree(dev_arr);
	cudaFree(dev_max_val);
	
	free(arr);
 }
