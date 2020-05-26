#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
    float x;
    float y;
} vector_t;

vector_t vec_add(vector_t v1, vector_t v2);

vector_t vec_subtract(vector_t v1, vector_t v2);

vector_t vec_negate(vector_t v);

vector_t vec_multiply(float scalar, vector_t v);

float vec_mag(vector_t v1);

float vec_distance(vector_t v1, vector_t v2);

bool vec_same(vector_t v1, vector_t v2);

vector_t vec_norm(vector_t v1);

#endif
