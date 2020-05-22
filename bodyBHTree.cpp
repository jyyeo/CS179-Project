#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "body.h"
#include "quads.h"

using namespace std;

int main () {
    int n, duration;
    cout << "Number of bodies (integer): ";
    cin >> n;
    cout << "Duration (integer): ";
    cin >> duration;

    Body bodies[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        bodies[i] = initializeBody();
        cout << bodies[i].mass << endl;
        cout << bodies[i].rx << "   " << bodies[i].ry << endl;
    }

    // BHTree tree;
    // cout << "initialized" << endl;
    // for (int t = 0; t < duration; t++) {
    //     for (int i = 0; i < n; i++) {
    //         tree.insertBody(bodies[i]);
    //     }
    //     for (int i = 0; i < n; i++) {
    //         bodies[i].resetForce();
    //         tree.updateForce(bodies[i]);
    //     }
    //     for (int i = 0; i < n; i++) {
    //         cout << bodies[i].fx  << "   " << bodies[i].fy << endl;
    //         bodies[i].update(1E12);
    //         cout << bodies[i].rx << "   " << bodies[i].ry << endl;
    //     }
    // }
}
