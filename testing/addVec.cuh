#ifndef CUDA_ADDVEC_CUH
#define CUDA_ADDVEC_CUH

void cudaAddVecKernel(
	const float *input1,
	const float *input2,
	const float *output,
	const unsigned int size);

void cudaCallAddVecKernel(const int blocks,
	const unsigned int threadsPerBlock,
	const float *input1,
	const float *input2,
	const float *output,
	const unsigned int size);

#endif
