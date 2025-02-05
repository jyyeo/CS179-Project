#ifndef __BBOX_H__
#define __BBOX_H__

#include "vector.h"
#include "mechanics.h"

typedef struct {
    vector_t bl;
    vector_t tr;
} Bbox;

float get_min_x(Body bodies[], int n);

float get_max_x(Body bodies[], int n);

float get_min_y(Body bodies[], int n);

float get_max_y(Body bodies[], int n);

float get_centre_x (Bbox bbox);

float get_centre_y (Bbox bbox);

#endif