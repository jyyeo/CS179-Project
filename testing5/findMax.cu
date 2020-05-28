#include <cstdio>

#include <cuda_runtime.h>
#include <cufft.h>

#include "findMax.cuh"

__device__ static float atomicMax(float* address, float val)
{
    int* address_as_i = (int*) address;
    int old = *address_as_i, assumed;
    do {
        assumed = old;
        old = ::atomicCAS(address_as_i, assumed,
            __float_as_int(::fmaxf(val, __int_as_float(assumed))));
    } while (assumed != old);
    return __int_as_float(old);
}

__global__
void
cudaMaximumKernel(cufftComplex *out_data, float *max_abs_val,
    int padded_length) {

    extern __shared__ float shared_memory[];
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.x;
    while (i < padded_length) {
	shared_memory[j] = fabs(out_data[j].x);
	__syncthreads();
	for (int k = blockDim.x; k > 1; k >>= 1) {
	    if (j < k) { //place values in contiguous memory locations
		if (shared_memory[j] < shared_memory[j + k]) { //store the larger value
		    shared_memory[j] = shared_memory[j + k];
		}
	    }		
	    __syncthreads();
	}
	if (threadIdx.x == 0) {
		atomicMax(max_abs_val, shared_memory[0]);
	} //run this once, after the largest value is in first memory location
    	i += blockDim.x * gridDim.x;
    }
}

void cudaCallMaximumKernel(const unsigned int blocks,
        const unsigned int threadsPerBlock,
        cufftComplex *out_data,
        float *max_abs_val,
        const unsigned int padded_length) {
        

    /* TODO 2: Call the max-finding kernel. */
    cudaMaximumKernel<<<blocks,threadsPerBlock>>>(out_data, max_abs_val, padded_length);
}