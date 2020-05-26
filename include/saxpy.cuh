//#pragma once
#ifndef CUDA_SAXPY_CUH
#define CUDA_SAXPY_CUH

void saxpy (float a, float *x, float *y, int size);

void cudaSaxpy (float a, float *x, float *y, int size);

#endif
