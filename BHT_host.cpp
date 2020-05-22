#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdlib.h>

#include "struct_defs.h"
#include "body.h"
#include "quads.h"

#define gpuErrChk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
// inline void gpuAssert(cudaError_t code, const char *file, int line,
//     bool abort = true)
// {
//     if (code != cudaSuccess) {
//         fprintf(stderr,"GPUassert: %s %s %d\n",
//             cudaGetErrorString(code), file, line);
//         exit(code);
//     }
// }

int main(int argc, char const *argv[]) {
    int n, duration;

    // handle arguments
    if (argc != 3) {
        printf("Usage: ./a.out [number of bodies (int)] [duration (int)]\n");
        return 1;
    }
    n = atoi(argv[1]);
    duration = atoi(argv[2]);

    Body bodies[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        bodies[i] = initializeBody();
        std::cout << bodies[i].mass << std::endl;
        std::cout << bodies[i].rx << "   " << bodies[i].ry << std::endl;
    }

    // Allocate host memory
    float * host_bodies = array_from_body(bodies);

    // Allocate device memory
    float * dev_bodies;
    CUDA_CALL(cudaMalloc ((void **) &dev_bodies, n * 7 * sizeof(float)));
    
    // gpuErrChk(cudaMemcpy(bodies))
    return 0;
};
