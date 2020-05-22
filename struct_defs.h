#ifndef struct_defs
#define struct_defs

struct Body;
struct Quad;
struct BHTree;

struct Body {
    double rx, ry;
    double vx, vy;
    double fx, fy;
    double mass;

    int size();
    void update (double dt);
    double distanceTo (Body b);
    void resetForce ();
    void forceDueTo (Body b);
    bool inQuad (Quad q);
};

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

#endif
