#include "vector.h"

// const float G = 6.673e-11;
const float G = 1.0;

// typedef unsigned int float;

typedef struct {
	vector_t position;
	vector_t velocity;
	float mass;
} Body;

vector_t get_position(Body b);

vector_t get_velocity(Body b);

float get_mass(Body b);

// (mass, p2) acts on p1
vector_t acc_on_point(vector_t p1, float mass, vector_t p2);

// b acts on a
vector_t acc_on (Body a, Body b);

void updateBody(Body &b, vector_t acc, int t);