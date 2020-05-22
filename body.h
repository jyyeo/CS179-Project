#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include "struct_defs.h"

double G = 6.673e-11;
int minr = -100 * 1E18;
int maxr = 100 * 1E18;

// struct Body {
//     double rx, ry;
//     double vx, vy;
//     double fx, fy;
//     double mass;
//
//     void update (double dt);
//     double distanceTo (Body b);
//     void resetForce ();
//     void forceDueTo (Body b);
//     bool inQuad (Quad q);
// };

Body initializeBody () {
    Body b;
    b.rx = (rand() % 201 - 100) * 1E18;
    b.ry = (rand() % 201 - 100) * 1E18;
    b.vx = (rand() % 21 - 10) * pow(10,rand() % 5 + 1);
    b.vy = (rand() % 21 - 10) * pow(10,rand() % 5 + 1);
    b.fx = 0;
    b.fy = 0;
    b.mass = (rand() % 10 + 1) * 1E18;
    return b;
};

int Body :: size() {
  return 7;
}

void Body :: update (double dt) {
    vx += dt * fx / mass;
    vy += dt * fy / mass;
    rx += dt * vx;
    ry += dt * vy;
};

double Body :: distanceTo (Body b) {
    double dx = abs(rx - b.rx);
    double dy = abs(ry - b.ry);
    return sqrt(dx * dx + dy * dy);
};

void Body :: resetForce () {
    fx = 0;
    fy = 0;
};

void Body :: forceDueTo (Body b) {
    double epsilon = 3E4;
    double dx = b.rx - rx;
    double dy = b.ry - ry;
    double dist = sqrt(dx * dx + dy * dy);
    double force = (G * mass * b.mass) / (dist * dist + epsilon * epsilon);
    if (dx != 0 && dist != 0) {
        fx += force * dx / dist;
        fy += force * dy / dist;
    }
};

bool Body :: inQuad (Quad q) {
    return q.containsBody(rx, ry);
}

float * array_from_body(Body bodies[]) {
    int n = bodies->size();
    float * arr = (float *) malloc(sizeof(float) * n * 7);
    for (int i = 0; i < n; i++) {
        arr[i] = bodies[i].rx;
        arr[1 * n + i] = bodies[i].ry;
        arr[2 * n + i] = bodies[i].vx;
        arr[3 * n + i] = bodies[i].vy;
        arr[4 * n + i] = bodies[i].fx;
        arr[5 * n + i] = bodies[i].fy;
        arr[6 * n + i] = bodies[i].mass;
    }
    return arr;
};
