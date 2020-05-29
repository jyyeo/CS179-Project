#include <stdlib.h>
#include <cstdio>

#include "vector.h"
#include "mechanics.h"
#include "bbox.h"

float get_min_x(Body bodies[], int n) {
	float min_x = 0.0;
	for (int i = 0; i < n; i++) {
			float x = get_position(bodies[i]).x;
			if (x < min_x) {
				min_x = x;
			}
	}
	return min_x;
}

float get_max_x(Body bodies[], int n) {
	float max_x = 0.0;
	for (int i = 0; i < n; i++) {
			float x = get_position(bodies[i]).x;
			if (x > max_x) {
				max_x = x;
			}
	}
	return max_x;
}

float get_min_y(Body bodies[], int n) {
	float min_y = 0.0;
	for (int i = 0; i < n; i++) {
			float y = get_position(bodies[i]).y;
			if (y < min_y) {
				min_y = y;
			}
	}
	return min_y;
}

float get_max_y(Body bodies[], int n) {
	float max_y = 0.0;
	for (int i = 0; i < n; i++) {
			float y = get_position(bodies[i]).y;
			if (y > max_y) {
				max_y = y;
			}
	}
	return max_y;
}

float get_centre_x (float min_x, float max_x) {
	return max_x - 0.5 * (max_x - min_x);
}

float get_centre_y (float min_y, float max_y) {
	return max_y - 0.5 * (max_y - min_y);
} 

vector_t get_min_x(Bbox bbox) {
	return (bbox.bl).x;
}

vector_t get_max_x(Bbox bbox) {
	return (bbox.tr).x;
}

vector_t get_min_y(Bbox bbox) {
	return (bbox.bl).y;
}

vector_t get_max_y(Bbox bbox) {
	return (bbox.tr).y;
}