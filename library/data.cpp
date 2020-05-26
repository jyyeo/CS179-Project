#include <stdlib.h>
#include <cstdio>

#include "../include/vector.h"
#include "../include/mechanics.h"
#include "../include/data.h"

void extract_position_x (Body bodies[], int n, float *position_x) {
	for (int i = 0; i < n; i++) {
		position_x[i] = get_position(bodies[i]).x;
	}
}

void extract_position_y (Body bodies[], int n, float *position_y) {
	for (int i = 0; i < n; i++) {
		position_y[i] = get_position(bodies[i]).y;
	}
}

void extract_velocity_x (Body bodies[], int n, float *velocity_x) {
	for (int i = 0; i < n; i++) {
		velocity_x[i] = get_velocity(bodies[i]).x;
	}
}

void extract_velocity_y (Body bodies[], int n, float *velocity_y) {
	for (int i = 0; i < n; i++) {
		velocity_y[i] = get_velocity(bodies[i]).y;
	}
}