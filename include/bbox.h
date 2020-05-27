#ifndef __BBOX_H__
#define __BBOX_H__

#include "vector.h"

typedef struct {
    vector_t bl;
    vector_t tr;
} Bbox;

vector_t get_min_x(Bbox bbox);

vector_t get_max_x(Bbox bbox);

vector_t get_min_y(Bbox bbox);

vector_t get_max_y(Bbox bbox);

#endif