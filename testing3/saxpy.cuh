#pragma once

__global__ void saxpy (float a, float *x, float *y, int size);

void cudaSaxpy (float a, float *x, float *y, int size);
