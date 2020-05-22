#include "vector.h"

struct Body {
	uint mass;
	vector_t location;
	vector_t velocity;
};

vector_t get_location(Body b);
