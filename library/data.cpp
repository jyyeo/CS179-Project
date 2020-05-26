#include <stdlib.h>
#include <cstdio>

#include "vector.h"
#include "mechanics.h"
#include "data.h"

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

void reverse_position_x (Body bodies[], int n, float *position_x) {
	for (int i = 0; i < n; i++) {
		(bodies[i].position).x = position_x[i];
	}
}

void reverse_position_y (Body bodies[], int n, float *position_y) {
	for (int i = 0; i < n; i++) {
		(bodies[i].position).y = position_y[i];
	}
}	

void reverse_velocity_x (Body bodies[], int n, float *velocity_x) {
	for (int i = 0; i < n; i++) {
		(bodies[i].velocity).x = velocity_x[i];
	}
}

void reverse_position_y (Body bodies[], int n, float *velocity_y) {
	for (int i = 0; i < n; i++) {
		(bodies[i].velocity).y = velocity_y[i];
	}
}