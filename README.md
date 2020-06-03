#Motivation:
The Barnes-Hut(BH) algorithm is a method to approximate the forces exerted on each body in an N-body simulation.

In N-body simulations, the force exerted on each body is the sum of the gravitational force due to every other body in the system. The force exerted on each body is independent of each other, and thus the process of updating the positions and velocities of each body allows for parallelization.

The BH algorithm approximates this force exerted by bodies that are far away. It is more complicated compared to the naive method, as several variables have to be calculated before updating the positions and velocities of each body. The computation of these variables also has room for parallelization.

#High-level overview of algorithms and GPU specifics:
##Naive method
At each timestep, the positions and velocities of each body is given as:
	velocity_new = velocity + acceleration * delta_time
	position_new = position + velocity * delta_time
where acceleration is due to the sum of gravitational forces exerted by every other body.

In CPU, this is done by:
	for (int i = 0; i < total number of bodies; i++) {
		velocity_new = velocity + acceleration * delta_time
		position_new = position + velocity * delta_time
	}

In GPU, the updating can be done for all bodies simultaneously in parallel, using Cuda SAXPY, which computes Y = X + A * Y, where X and Y are vectors and A is a scalar. In the updating of velocities, 
	X is the vector [v1; v2; v3; ...] where vn is the velocity of body n
	Y is the vector [a1; a2; a3; ...] where an is the acceleration due to G 	force acting in body n
	A is delta_time

##BH method
The BH method works as such:
	1. Construct a BH tree by inserting each body into the tree as nodes. Each node is a square (or bounding box) within the entire space occupied by all the bodies.
	2. For each body A, iterate through all the nodes in the BH tree, starting from the root of the tree.
	If a node is a leaf node, calculate the acceleration due to G force of the body in the node on body A.
	Otherwise, if the node is too far away (by an arbitrary threshold, typically the width of the box / distance from the centre of the box to body A), treat the node as a single body and calculate the acceleration due to G force of the node on body A.
	Otherwise, repeat step 2, but iterate through the descendants of the node instead of restarting at the root of the tree.

This can be done in CPU, as well as in GPU.

There are several computations that can be done in parallel. For example, in the calculation of the bounding boxes of each body, the minimum and maximum x and y values are computed first, before determining the coordinates of the boxes of each body. This can be done in parallel, by using reduction. Given N values, this would take O(N) time in CPU, because the algorithm will iterate through every body to find the minimum x and y values. In GPU, the algorithm reduces the number of values to compare by half in each iteration, taking O(logN) time in total.

#Code structure
##vector.h & vector.cpp
These modules defines a structure, vector_t, and handles vector computations. Vectors are one of the basic structures created. It is used to represent coordinates and velocities. It is used as a constituent of more complex structures, like bodies.

##mechanics.h && mechanics.cpp
These modules defines a structure, Body, and has functions to calculate the acceleration of one body on another body and to update a body's position and velocity, given the acceleration due to gravity on that body.

##data.h && data.cpp
These modules organize data for the Cuda functions. For example, it stores the acceleration, velocities and positions of each body in vectors for the updating of positions and velocities. These modules also have functions to use the results of the computations in GPU to update the position and velocity components of each Body.

##bbox.h && bbox.cpp
These modules defines a structure, Bbox, (which refers to the entire 2D space in which all the bodies are in, i.e. the bounding box) and has functions calculate the minimum and maximum x and y coordinates given the positions of all bodies, and also the coordinates of the centre of the box given the coordinates of the box.

##saxpy.cu
This module performs the calculation X + A * Y in GPU, where X and Y are vectors and A is scalar.

##findMax.cu
This module is a Cuda function that finds the maximum element within a vector. It is used to find the maximum x and y coordinates given the positions of all bodies to find the coordinates of the bounding box.

##findMin.cu
This module is a Cuda function that finds the minimum element within a vector. It is used to find the minimum x and y coordinates given the positions of all bodies to find the coordinates of the bounding box.

#Tests
##saxpy.cu
This module calculates X + A * Y in GPU. To test this module on its own, from the main directory, run:
	cd test_saxpy
	make test

Expected output:
CPU: 2.250000  4.750000  7.250000  9.750000  12.250000  14.750000  17.250000  19.750000  22.250000  24.750000
GPU: 2.250000  4.750000  7.250000  9.750000  12.250000  14.750000  17.250000  19.750000  22.250000  24.750000

##findMax.cu
This module finds the maximum element within a vector, using GPU. To test this module on its own, from the main directory, run:
Expected output:
CPU: 1.500000 3.000000 4.500000 6.000000 7.500000 9.000000 10.500000 12.000000 13.500000 15.000000
GPU: 1.500000 3.000000 4.500000 6.000000 7.500000 9.000000 10.500000 12.000000 13.500000 15.000000
completed
15.000000

##findMin.cu
This module finds the minimum element within a vector, using GPU. To test this module on its own, from the main directory, run:
 	cd test_findMin
 	make test

Expected output:
CPU: 7.500000 6.000000 4.500000 3.000000 1.500000 0.000000 -1.500000 -3.000000 -4.500000 -6.000000
GPU: 7.500000 6.000000 4.500000 3.000000 1.500000 0.000000 -1.500000 -3.000000 -4.500000 -6.000000
completed
-6.000000

## Compare CPU and GPU implementation
To run all test cases:
	make clean all
	./demo_project.sh

To run any single test cases (out of 5) using CPU implementation:
	./bins/cpu_run test_cases/test1.txt 

To run any single test cases (out of 5) using GPU implementation:
	./bins/gpu_run test_cases/test1.txt 
	