#ifndef CUDA_FINDMAX_CUH
#define CUDA_FINDMAX_CUH

__device__ static float atomicMax(float* address, float val);

__global__ void findMax(float *dev_arr, int size, float *dev_output);

void cudaFindMax(float *arr, int size, float *output);

#endif
