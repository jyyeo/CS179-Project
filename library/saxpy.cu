#include "cuda_runtime.h"
#include "saxpy.cuh"

__global__ 
void saxpy (float a, float *x, float *y, int size) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < size) {
		y[i] = a * x[i] + y[i];
	}
}

void cudaSaxpy (float a, float *x, float *y, int size) {
	float *dev_x;
	float *dev_y;

	cudaMalloc((void**)&dev_x, size * sizeof(float));
	cudaMalloc((void**)&dev_y, size * sizeof(float));
	
	cudaMemcpy(dev_x, x, size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_y, y, size * sizeof(float), cudaMemcpyHostToDevice);

	saxpy<<<1, size>>>(a, dev_x, dev_y, size);

	cudaMemcpy(y, dev_y, size * sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(dev_x);
	cudaFree(dev_y);
}