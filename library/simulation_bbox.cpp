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
#include "bbox.h"
#include "findMin.cuh"
#include "findMax.cuh"

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
		float mass = num[4];
		bodies[i].position = position;
		bodies[i].velocity = velocity;
		bodies[i].mass = mass;
	}

	input_file.close();
	ofstream output_file;
	output_file.open("output.txt");

	for (int t = 0; t < timestep; t++) {

		// calculate bounding boxes for each body (CPU)
		Bbox boxes[n];
		float min_x_cpu = get_min_x(bodies, n);
		float max_x_cpu = get_max_x(bodies, n);
		float min_y_cpu = get_min_y(bodies, n);
		float max_y_cpu = get_max_y(bodies, n);

		printf("%f %f %f %f\n", min_x_cpu, min_y_cpu, max_x_cpu, max_y_cpu);

		// calculate bounding boxes for each body (GPU)
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

		// cuda call for find min and find max
		float *min_x, *max_x, *min_y, *max_y;
		// min_x = (float*)malloc(sizeof(float));
		// max_x = (float*)malloc(sizeof(float));
		// min_y = (float*)malloc(sizeof(float));
		// max_y = (float*)malloc(sizeof(float));
		// cudaFindMin(position_x, n, min_x);
		// cudaFindMax(position_x, n, max_x);
		// cudaFindMin(position_y, n, min_y);
		// cudaFindMax(position_y, n, max_y);

		// printf("%f %f %f %f\n", *min_x, *min_y, *max_x, *max_y);

		for (int i = 0; i < n; i++) {
			// vector_t mins = {min_x, min_y};
			boxes[i].bl = {*min_x, *min_y};
			// vector_t maxs = {max_x, max_y};
			boxes[i].tr = {*max_x, *max_y};
		}

		// float centre_x = get_centre_x(*min_x, *max_x);
		// float centre_y = get_centre_y(*min_y, *max_y);

		// insert bodies into octants
		
		
		// calculate acceleration on each body, update position and velocity
		float acc_x[n];
		float acc_y[n];
		for (int i = 0; i < n; i++) {
			acc_x[i] = 0.0;
			acc_y[i] = 0.0;
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				vector_t total_acc = acc_on(bodies[i], bodies[j]);
				acc_x[i] += total_acc.x;
				acc_y[i] += total_acc.y;
			}
		}
		
		// organize data for GPU
		extract_position_x (bodies, n, position_x);
		extract_position_y (bodies, n, position_y);
		extract_velocity_x (bodies, n, velocity_x);
		extract_velocity_y (bodies, n, velocity_y);

		// cuda calls
		// v_new = v + at, x_new = x + vt
		cudaSaxpy(timestep, acc_x, velocity_x, n);
		cudaSaxpy(timestep, velocity_x, position_x, n);
		cudaSaxpy(timestep, acc_y, velocity_y, n);
		cudaSaxpy(timestep, velocity_y, position_y, n);

		// update values from GPU
		reverse_position_x (bodies, n, position_x);
		reverse_position_y (bodies, n, position_y);
		reverse_velocity_x (bodies, n, velocity_x);
		reverse_velocity_y (bodies, n, velocity_y);

		free(position_x);
		free(position_y);
		free(velocity_x);
		free(velocity_y);
		free(min_x);
		free(max_x);
		free(min_y);
		free(max_y);

		 // output to txt file
		 for (int i = 0; i < n; i++) {
		 	string float_arr[5];
		 	float_arr[0] = to_string(get_position(bodies[i]).x);
		 	float_arr[1] = to_string(get_position(bodies[i]).y);
		 	float_arr[2] = to_string(get_velocity(bodies[i]).x);
		 	float_arr[3] = to_string(get_velocity(bodies[i]).y);
		 	float_arr[4] = to_string(get_mass(bodies[i]));
		 	// string output_line = float_arr[0] + " " + float_arr[1] + " " + float_arr[2] + " " + float_arr[3] + " " + float_arr[4];
		 	// cout << output_line << "\n";
			// output_file << output_line << "\n";
		}
		output_file << "\n";
		printf("timestep %d\n", timestep);
	}	
	output_file.close();


	return 0;
}
