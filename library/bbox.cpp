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

float get_centre_x (Bbox bbox) {
	float max_x = (bbox.tr).x;
	float min_x = (bbox.bl).x;
	return max_x - 0.5 * (max_x - min_x);
}

float get_centre_y (Bbox bbox) {
	float max_y = (bbox.tr).y;
	float min_y = (bbox.bl).y;
	return max_y - 0.5 * (max_y - min_y);
} 
