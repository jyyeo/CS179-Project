#include "struct_defs.h"

// struct Quad {
//     double xmid;
//     double ymid;
//     double length;
//
//     bool containsBody (double rx, double ry);
//     Quad initializeNW ();
//     Quad initializeNE ();
//     Quad initializeSW ();
//     Quad initializeSE ();
// };

Quad initializeQuad (double xmid, double ymid, double length) {
    Quad q;
    q.xmid = xmid;
    q.ymid = ymid;
    q.length = length;
    return q;
};

bool Quad :: containsBody (double rx, double ry) {
    return (rx <= ((xmid + length/2.0) && (rx >= (xmid - length/2.0))) &&
            ry <= (ymid + length/2.0) && (ry >= (ymid - length/2.0)));
};

Quad Quad :: initializeNW () {
    Quad q = initializeQuad (xmid - length/4.0, ymid + length/4.0, length/2.0);
    return q;
};

Quad Quad :: initializeNE () {
    Quad q = initializeQuad (xmid + length/4.0, ymid + length/4.0, length/2.0);
    return q;
};

Quad Quad :: initializeSW () {
    Quad q = initializeQuad (xmid - length/4.0, ymid - length/4.0, length/2.0);
    return q;
};

Quad Quad :: initializeSE () {
    Quad q = initializeQuad (xmid + length/4.0, ymid - length/4.0, length/2.0);
    return q;
};
