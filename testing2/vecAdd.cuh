#pragma once

__global__ void vecAdd (float *input1, float *input2, float *output, int size);

void cudaVecAdd (float *input1, float *input2, float *output, int size);