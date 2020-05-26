#include "vector.h"

// const double G = 6.673e-11;
const double G = 1;

typedef unsigned int kg;

typedef struct {
	vector_t position;
	vector_t velocity;
	kg mass;
} Body;

vector_t get_position(Body b);

vector_t get_velocity(Body b);

kg get_mass(Body b);

// (mass, p2) acts on p1
vector_t acc_on_point(vector_t p1, kg mass, vector_t p2);

// b acts on a
vector_t acc_on (Body a, Body b);

void updateBody(Body &b, vector_t acc, int t);