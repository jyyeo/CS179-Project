#include <math.h>
#include "vector.h"

vector_t vec_add(vector_t v1, vector_t v2) {
    vector_t output = {v1.x + v2.x, v1.y + v2.y};
    return output;
}

vector_t vec_subtract(vector_t v1, vector_t v2) {
    vector_t output = {v1.x - v2.x, v1.y - v2.y};
    return output;
}

vector_t vec_negate(vector_t v) {
    vector_t output = {-v.x, -v.y};
    return output;
}

vector_t vec_multiply(double scalar, vector_t v) {
    vector_t output = {scalar * v.x, scalar * v.y};
    return output;
}
