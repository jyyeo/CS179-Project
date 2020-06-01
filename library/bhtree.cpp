#include <stdlib.h>
#include <cstdio>

#include "vector.h"
#include "mechanics.h"
#include "bbox.h"
#include "bhtree.h"

Body get_body (BHTree *tree) {
	return tree->body;
}

Bbox get_bbox (BHTree *tree) {
	return tree->bbox;
}

bool contain_body (BHTree *tree) {
	if (get_mass(tree->body) == 0) {
		return false;
	}
	else {
		return true;
	}
}

BHTree* insert_body (BHTree *tree, Body b) {
	tree->body = b;
	return tree;
}

bool is_internal_node (BHTree *tree) {
	return (get_mass(get_body(tree->NW)) != 0.0 ||
		    get_mass(get_body(tree->NE)) != 0.0 ||
		    get_mass(get_body(tree->SW)) != 0.0 ||
		    get_mass(get_body(tree->SE)) != 0.0);
}

float update_mass (BHTree *tree, Body b) {
	return get_mass(get_body(tree)) + get_mass(b);
}

vector_t update_position (BHTree *tree, Body b) {
	float total_mass = update_mass(tree, b);
	float pos_x = get_mass(get_body(tree)) * get_position(get_body(tree)).x +
	              get_mass(b) * get_position(b).x;
	float pos_y = get_mass(get_body(tree)) * get_position(get_body(tree)).y +
	              get_mass(b) * get_position(b).y;
	vector_t new_pos = {pos_x / total_mass, pos_y / total_mass};
	return new_pos;	              
}

int check_quad (BHTree *tree, Body b) {
	if (get_position(b).x < get_centre_x(get_bbox(tree))) { // West
		if (get_position(b).y > get_centre_y(get_bbox(tree))) { //North
			return 1;
		}
	}
	else if (get_position(b).x > get_centre_x(get_bbox(tree))) { // East
		if (get_position(b).y > get_centre_y(get_bbox(tree))) { //North
			return 2;
		}
	}
	else if (get_position(b).x < get_centre_x(get_bbox(tree))) { // West
		if (get_position(b).y < get_centre_y(get_bbox(tree))) { //South
			return 3;
		}
	}
	else {
	// if (get_position(b).x > get_centre_x(get_bbox(tree))) { // East
		if (get_position(b).y < get_centre_y(get_bbox(tree))) { //South
			return 4;
		}
	}
	return 0;
}

BHTree* initialize_quads (BHTree *tree) {
	BHTree *updated_tree = tree;
	
	((*updated_tree->NW).bbox).bl = 
		{((tree->bbox).bl).x, get_centre_y(get_bbox(tree))};
	((*updated_tree->NW).bbox).tr = 
		{get_centre_x(get_bbox(tree)), ((get_bbox(tree)).tr).y};
	
	((*updated_tree->NE).bbox).bl =
		{get_centre_x(get_bbox(tree)), get_centre_y(get_bbox(tree))};
	((*updated_tree->NE).bbox).tr =
		get_bbox(tree).tr;
	
	((*updated_tree->SW).bbox).bl =
		get_bbox(tree).bl;
	((*updated_tree->SW).bbox).tr =
		{get_centre_x(get_bbox(tree)), get_centre_y(get_bbox(tree))};

	((*updated_tree->SE).bbox).bl =
		{get_centre_x(get_bbox(tree)), ((tree->bbox).bl).y};
	((*updated_tree->SE).bbox).tr =
		{(get_bbox(tree).tr).x, get_centre_y(get_bbox(tree))};

	return updated_tree;
}

BHTree* update_quad (BHTree *tree, Body b) {
	BHTree *updated_tree = tree;

	if (check_quad(tree, b) == 1) { // NW
		tree->NW = initialize_quads(tree->NW);
		updated_tree->NW = construct_tree(tree->NW, b);
	}
	else if (check_quad(tree, b) == 2) { //NE
		tree->NE = initialize_quads(tree->NE);
		updated_tree->NE = construct_tree(tree->NE, b);
	}
	else if (check_quad(tree, b) == 3) { // SW
		tree->SW = initialize_quads(tree->SW);
		updated_tree->SW = construct_tree(tree->SW, b);
	}
	else { //SE
		tree->SE = initialize_quads(tree->SE);
		updated_tree->SE = construct_tree(tree->SE, b);
	}
	return updated_tree;
}

BHTree* construct_tree (BHTree *tree, Body b) {
	BHTree *updated_tree;
	// does not contain a body
	if (contain_body(tree) == false) {
		return insert_body(tree, b);
	}
	// internal node
	else if (is_internal_node(tree)) {
		updated_tree = update_quad(tree, b);
	}
	// external node that contains a body already
	else {
		Body tree_body = get_body(tree);
		updated_tree = update_quad(tree, tree_body);
		updated_tree = update_quad(tree, b);
	}

	(updated_tree->body).mass = update_mass(tree, b);
	(updated_tree->body).position = update_position(tree, b);
	
	return updated_tree;
}


