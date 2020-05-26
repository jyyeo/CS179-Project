#include "vector.h"
#include "mechanics.h"

#include "stdio.h"

float get_mass(Body b) {
	return b.mass;
}

vector_t get_position(Body b) {
	return b.position;
}

vector_t get_velocity(Body b) {
	return b.velocity;
}

vector_t acc_on_point(vector_t p1, float mass, vector_t p2) {
	if (vec_same(p1,p2)) {
		vector_t output = {0.0, 0.0};
		return output;
	}
	else {
		float r = vec_distance(p1, p2);
		vector_t dir = vec_norm(vec_subtract(p2,p1));
		return vec_multiply(G * mass / (r * r + 1), dir);
	}
}
// acceleration of b1 due to b2
vector_t acc_on (Body b1, Body b2) {
	return acc_on_point(get_position(b1), get_mass(b2), get_position(b2));
}

void updateBody(Body &b, vector_t acc, int t) {
	vector_t new_velocity = vec_add(get_velocity(b), vec_multiply(t, acc));
	vector_t new_position = vec_add(get_position(b), vec_multiply(t, new_velocity));
	b.velocity = new_velocity;
	b.position = new_position;
}