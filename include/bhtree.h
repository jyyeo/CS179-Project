#ifndef __BHTREE_H__
#define __BHTREE_H__

#include "vector.h"
#include "mechanics.h"
#include "bbox.h"

typedef struct {
	Body body;
	Bbox bbox;
	BHTree NW;
	BHTree NE;
	BHTree SW;
	BHTree SE;
} BHTree;

#endif