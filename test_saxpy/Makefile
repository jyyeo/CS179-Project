CC = g++
CPPFLAGS = -Wall

CUDA_PATH       ?= /usr/local/cuda
CUDA_INC_PATH   ?= $(CUDA_PATH)/include
CUDA_LIB_PATH   ?= $(CUDA_PATH)/lib

CFLAGS = -I$(CUDA_INC_PATH) -L$(CUDA_LIB_PATH) -lcudart

# LIBS = vector mechanics data bbox
# OBJS = $(addprefix out/,$(LIBS:=.o))

C_LIBS = saxpy
C_OBJS = $(addprefix out/,$(C_LIBS:=.o))

all: saxpy

saxpy: $(C_OBJS) test_saxpy/main.cpp
	$(CC) -o test_saxpy $^ $(CFLAGS) $(CPPFLAGS)

# cpu: out/mechanics.o out/vector.o library/simulation_cpu.cpp
# 	$(CC) -o bins/cpu_run $^ $(CPPFLAGS)

# libs: $(OBJS)

# out/%.o: test_saxpy/%.cpp
# 	$(CC) -c $(CPPFLAGS) -I$(CUDA_INC_PATH) $^ -o $@

out/%.o: test_saxpy/%.cu
	nvcc -c $^ -o $@ -Iinclude

clean:
	rm -f out/* bin/*

# test: bins/gpu_run bins/cpu_run
# 	./bins/gpu_run test_cases/test2.txt
# 	echo "\n"
# 	./bins/cpu_run test_cases/test2.txt

.PHONY: all clean saxpy
