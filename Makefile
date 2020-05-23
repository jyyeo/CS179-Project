CC = g++
CPPFLAGS = -Iinclude -Wall

LIBS = vector mechanics
OBJS = $(addprefix out/,$(LIBS:=.o))

all: $(OBJS)

out/%.o: library/%.cpp
	$(CC) -c $(CPPFLAGS) $^ -o $@
