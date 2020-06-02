#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#include "saxpy.cuh"

int main(void) {
	float a = 1.5;
	float *x, *y;
	int size = 10;

	x = (float*)malloc(size * sizeof(float));
	y = (float*)malloc(size * sizeof(float));
	
	for (int i = 0; i < size; i++) {
		x[i] = i + 0.5;
		y[i] = i + 1.5;
	}
	printf("CPU: ");
	for (int i = 0; i < size; i++) {
		printf("%f  ", a * x[i] + y[i]);
	}
	printf("\n");

	cudaSaxpy(a, x, y, size);

	printf("GPU: ");
	for (int i = 0; i < size; i++) {
		printf("%f  ",y[i]);
	}
	printf("\n");
}
