CC = /usr/bin/g++
CPPFLAGS = -Iinclude -Wall

CUDA_PATH       ?= /usr/local/cuda
CUDA_INC_PATH   ?= $(CUDA_PATH)/include
CUDA_LIB_PATH   ?= $(CUDA_PATH)/lib

CFLAGS = -I$(CUDA_INC_PATH) -L$(CUDA_LIB_PATH) -lcudart

LIBS = vector mechanics data
OBJS = $(addprefix out/,$(LIBS:=.o))

C_LIBS = saxpy
C_OBJS = $(addprefix out/,$(C_LIBS:=.o))

all: main

main: $(OBJS) $(C_OBJS) library/simulation_saxpy.cpp 
	$(CC) -o bins/main $^ $(CFLAGS) $(CPPFLAGS)

libs: $(OBJS)

out/%.o: library/%.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

out/%.o: library/%.cu
	nvcc -c $^ -o $@

clean:
	rm -f out/* bin/*

.PHONY: all clean
