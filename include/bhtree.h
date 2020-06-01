#ifndef __BHTREE_H__
#define __BHTREE_H__

#include "vector.h"
#include "mechanics.h"
#include "bbox.h"

struct BHTree;

struct BHTree {
	Body body;
	Bbox bbox;
	struct BHTree* NW;
	struct BHTree* NE;
	struct BHTree* SW;
	struct BHTree* SE;
};

Body get_body (BHTree *tree);

Bbox get_bbox (BHTree *tree);

bool contain_body (BHTree *tree);

BHTree* insert_body (BHTree *tree, Body b);

bool is_internal_node (BHTree *tree);

float update_mass (BHTree *tree, Body b);

vector_t update_position (BHTree *tree, Body b);

int check_quad (BHTree *tree, Body b);

BHTree* initialize_quads (BHTree *tree);

BHTree* update_quad (BHTree *tree, Body b);

BHTree* construct_tree (BHTree *tree, Body b);

#endif