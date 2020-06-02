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

