#include <cuda_runtime.h>

__global__
void cudaAddVecKernel(
	const float *input1,
	const float *input2,
	float *output,
	const unsigned int size) 
{
	uint thread_index = blockIdx.x * blockDim.x + threadIdx.x;
	while (thread_index < size) {
		output[thread_index] = input1[thread_index] + input2[thread_index];
		thread_index += blockDim.x * gridDim.x;
	}
}

void cudaCallAddVecKernel(const int blocks,
	const unsigned int threadsPerBlock,
	const float *input1,
	const float *input2,
	float *output,
	const unsigned int size) 
{
	cudaAddVecKernel<<<blocks, threadsPerBlock>>>(input1, input2, output, size);
}
