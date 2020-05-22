#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

double G = 6.673e-11;
int minr = -100 * 1E18;
int maxr = 100 * 1E18;

struct Quad {
    double xmid;
    double ymid;
    double length;

    bool containsBody (double rx, double ry);
    Quad initializeNW ();
    Quad initializeNE ();
    Quad initializeSW ();
    Quad initializeSE ();
};

struct Body {
    double rx, ry;
    double vx, vy;
    double fx, fy;
    double mass;

    void update (double dt);
    double distanceTo (Body b);
    void resetForce ();
    void forceDueTo (Body b);
    bool inQuad (Quad q);
    void nullBody ();
};

struct BHTree {
    Body body;
    Quad quad;
    struct BHTree* NW;
    struct BHTree* NE;
    struct BHTree* SW;
    struct BHTree* SE;

    bool nodeIsLeaf ();
    void insertBody (Body b);
    void updateForce (Body b);
};

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

Body nullBody () {
    Body b;
    b.rx = 0;
    b.ry = 0;
    b.vx = 0;
    b.vy = 0;
    b.fx = 0;
    b.fy = 0;
    b.mass = 0;
    return b;
}

Body combine (Body a, Body b) {
    Body newbody;
    newbody.rx = (a.mass * a.rx + b.mass * b.rx) / (a.mass + b.mass);
    newbody.ry = (a.mass * a.ry + b.mass * b.ry) / (a.mass + b.mass);
    newbody.vx = 0;
    newbody.vy = 0;
    newbody.fx = 0;
    newbody.fy = 0;
    newbody.mass = a.mass + b.mass;
    return newbody;
}

bool Quad :: containsBody (double rx, double ry) {
    return (rx <= ((xmid + length/2.0) && (rx >= (xmid - length/2.0))) &&
            ry <= (ymid + length/2.0) && (ry >= (ymid - length/2.0)));
};

Quad Quad :: initializeNW () {
    Quad NW;
    NW.xmid = xmid - length/4.0;
    NW.ymid = ymid + length/4.0;
    NW.length = length / 2.0;
    return NW;
}
//
// Quad Quad :: initializeNE () {
//     Quad NE;
//     NE.xmid = xmid + length/4.0;
//     NE.ymid = ymid + length/4.0;
//     NE.length = length / 2.0;
//     return NE;
// }
//
// Quad Quad :: initializeSW () {
//     Quad SW;
//     SW.xmid = xmid - length/4.0;
//     SW.ymid = ymid - length/4.0;
//     SW.length = length / 2.0;
//     return SW;
// }
//
// Quad Quad :: initializeSE () {
//     Quad SE;
//     SE.xmid = xmid + length/4.0;
//     SE.ymid = ymid - length/4.0;
//     SE.length = length / 2.0;
//     return SE;
// }

BHTree initializeTree (Quad q) {
    BHTree tree;
    tree.body = nullBody();
    tree.quad = q;
    tree.NW = NULL;
    tree.NE = NULL;
    tree.SW = NULL;
    tree.SE = NULL;
    return tree;
};

bool BHTree :: nodeIsLeaf () {
  return (NW == NULL && NE == NULL &&
          SW == NULL && SE == NULL);
};

void BHTree :: insertBody (Body b) {

    if (body.mass == 0) { //terminal node. Is a leaf.
        body = b;
    }
    else if (nodeIsLeaf () == false) { //internal node
        body = combine (b, body); //only position and mass matters
        if (b.inQuad(NW.quad)) {
            if (NW == NULL) {
                NW = initializeTree(quad);
            }
            NW.insertBody(b);
        }
        else if (b.inQuad(NE.quad)) {
            if (NE == NULL) {
                initializeTree(NE);
            }
            NE.insertBody(b);
        }
        else if (b.inQuad(SW.quad)) {
            if (SW == NULL) {
                initializeTree(SW);
            }
            SW.insertBody(b);
        }
        else {
            if (SE == NULL) {
                initializeTree(SE);
            }
            SE.insertBody(b);
        }
    }
    else {
    //This is an external node with a body.
    //All quads are NULL.
    //Make this an internal node by creating new tree.
    //Insert original body into a quad.
        quad.initializeNW();
        if (body.inQuad(NW.quad)) {
            initializeTree(NW);
            NW.insertBody(body);
        }
        else if (body.inQuad(NE)) {
            initializeTree(NE);
            NE.insertBody(body);
        }
        else if (body.inQuad(SW)) {
            initializeTree(SW);
            SW.insertBody(body);
        }
        else {
            initializeTree(SE);
            SE.insertBody(body);
        }
    //Insert new body into a quad.
        if (b.inQuad(NW)) {
            initializeTree(NW);
            NW.insertBody(b);
        }
        else if (b.inQuad(NE)) {
            initializeTree(NE);
            NE.insertBody(b);
        }
        else if (b.inQuad(SW)) {
            initializeTree(SW);
            SW.insertBody(b);
        }
        else {
            initializeTree(SE);
            SE.insertBody(b);
        }
    //Combine original and new bodies.
    body = combine(b,body)
    }
};

double theta = 2.0;
void BHTree :: updateForce (body b) {
    if (nodeIsLeaf (this)) {
        b.forceDueTo(body);
    }
    else if (quad.length() / body.distanceTo(b) < theta) {
        b.forceDueTo(body);
    }
    else {
        if (NW != NULL) {
            NW.updateForce(b);
        }
        if (NE != NULL) {
            NE.updateForce(b);
        }
        if (SW != NULL) {
            SW.updateForce(b);
        }
        if (SE != NULL) {
            SE.updateForce(b);
        }
    }

}
