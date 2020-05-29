#ifndef __BBOX_H__
#define __BBOX_H__

#include "vector.h"

typedef struct {
    vector_t bl;
    vector_t tr;
} Bbox;

float get_min_x(Bbox bbox);

float get_max_x(Bbox bbox);

float get_min_y(Bbox bbox);

float get_max_y(Bbox bbox);

#endif