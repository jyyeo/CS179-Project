// #include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <sstream>
#include <cuda_runtime.h>

#include "vector.h"
#include "mechanics.h"
#include "data.h"
#include "saxpy.cuh"

using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::to_string;

int	main(int argc, char const *argv[])
{
	// check arguments
	if (argc != 2) {
		cerr << "Incorrect number of arguments.\n";
		cerr << "Arguments: <.o file> <.txt file>\n";
		exit(EXIT_FAILURE);
	}

	// open file, while contains data
	ifstream input_file;
	input_file.open(argv[1]);

	// read data
	string line;
	int n, timestep;
	getline(input_file, line);
	n = stoi(line);
	getline(input_file, line);
	timestep = stoi(line);

	// save the data of each body
	Body bodies[n];
	for (int i = 0; i < n; i++) {
		getline(input_file, line);
		std::stringstream  lineStream(line);

		// should be 8
		float num[5];
		for (int j = 0; j < 5; j++) {
			lineStream >> num[j];
		}

		vector_t position = {num[0], num[1]};
		vector_t velocity = {num[2], num[3]};
		kg mass = num[4];
		bodies[i].position = position;
		bodies[i].velocity = velocity;
		bodies[i].mass = mass;
	}

	input_file.close();
	ofstream output_file;
	output_file.open("output.txt");

	for (int t = 0; t < 2; t++) {
		// calculate acceleration on each body, update position and velocity
		// vector_t acc[n];
		float acc_x[n];
		float acc_y[n];
		for (int i = 0; i < n; i++) {
			acc_x[i] = 0.0;
			acc_y[i] = 0.0;
			// acc[i].x = 0.0;
			// acc[i].y = 0.0;
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%f %f %f %f %s\n", get_position(bodies[i]).x, get_position(bodies[i]).y, 
					get_velocity(bodies[i]).x, get_velocity(bodies[i]).y, to_string(get_mass(bodies[i])));
				printf("%f %f %f %f %s\n", get_position(bodies[j]).x, get_position(bodies[j]).y, 
					get_velocity(bodies[j]).x, get_velocity(bodies[j]).y, to_string(get_mass(bodies[i])));
				vector_t total_acc = acc_on(bodies[i], bodies[j]);
				printf("%f %f\n", total_acc.x, total_acc.y);
				acc_x[i] += total_acc.x;
				acc_y[i] += total_acc.y;
				// printf("%f %f\n", acc_x[i], acc_y[i]);
			}
			// printf("Debug: %f %f\n", acc_x[i], acc_y[i]);
		}
		
		// organize data for GPU
		float *position_x;
		position_x = (float*)malloc(n * sizeof(float));
		float *position_y;
		position_y = (float*)malloc(n * sizeof(float));
		float *velocity_x;
		velocity_x = (float*)malloc(n * sizeof(float));
		float *velocity_y;
		velocity_y = (float*)malloc(n * sizeof(float));
		extract_position_x (bodies, n, position_x);
		extract_position_y (bodies, n, position_y);
		extract_velocity_x (bodies, n, velocity_x);
		extract_velocity_y (bodies, n, velocity_y);
		// for (int i = 0; i < n; i++) {
		// 	printf("%f ", position_x[i]);
		// }
		// printf("\n");

		// cuda calls
		// v_new = v + at, x_new = x + vt
		cudaSaxpy(timestep, acc_x, velocity_x, n);
		cudaSaxpy(timestep, velocity_x, position_x, n);
		cudaSaxpy(timestep, acc_y, velocity_y, n);
		cudaSaxpy(timestep, velocity_y, position_y, n);
		// for (int i = 0; i < n; i++) {
		// 	printf("%f ", position_x[i]);
		// }
		// printf("\n");

		reverse_position_x (bodies, n, position_x);
		reverse_position_y (bodies, n, position_y);
		reverse_velocity_x (bodies, n, velocity_x);
		reverse_velocity_y (bodies, n, velocity_y);

		free(position_x);
		free(position_y);
		free(velocity_x);
		free(velocity_y);

		 // output to txt file
		 for (int i = 0; i < n; i++) {
		 	string float_arr[5];
		 	float_arr[0] = to_string(get_position(bodies[i]).x);
		 	float_arr[1] = to_string(get_position(bodies[i]).y);
		 	float_arr[2] = to_string(get_velocity(bodies[i]).x);
		 	float_arr[3] = to_string(get_velocity(bodies[i]).y);
		 	float_arr[4] = to_string(get_mass(bodies[i]));
		 	string output_line = float_arr[0] + " " + float_arr[1] + " " + float_arr[2] + " " + float_arr[3] + " " + float_arr[4];
		 	// cout << output_line << "\n";
		// 	output_file << output_line << "\n";
		}
		printf("time step 1 \n\n");
		output_file << "\n";
	}	
	output_file.close();


	return 0;
}
