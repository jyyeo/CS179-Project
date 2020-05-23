#include "vector.h"

const double G = 6.673e-11;

typedef unsigned int kg;

struct Body {
	kg mass;
	vector_t position;
	vector_t velocity;
};

vector_t get_position(Body b);

kg get_mass(Body b);

// (mass, p2) acts on p1
vector_t acc_on_point(vector_t p1, kg mass, vector_t p2);

// b acts on a
vector_t acc_on (Body a, Body b);

Body updateBody(Body b, vector_t acc, int t);