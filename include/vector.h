#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
    double x;
    double y;
} vector_t;

vector_t vec_add(vector_t v1, vector_t v2);

vector_t vec_subtract(vector_t v1, vector_t v2);

vector_t vec_negate(vector_t v);

vector_t vec_multiply(double scalar, vector_t v);

#endif
