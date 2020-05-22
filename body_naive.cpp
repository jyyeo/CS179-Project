#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "body_naive.h"

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
    cout << "initialized" << endl;
    for (int t = 0; t < duration; t++) {
        // this portion can be parallelized
        for (int i = 0; i < n; i++) {
            bodies[i].resetForce();
            for (int j = 0; j < n; j++) {
                bodies[i].forceDueTo(bodies[j]);
            }
            cout << bodies[i].fx  << "   " << bodies[i].fy << endl;
        }
        // this portion can be parallelized
        for (int i = 0; i < n; i++) {
            bodies[i].update(1E12);
            cout << bodies[i].rx << "   " << bodies[i].ry << endl;
        }
    }
}
