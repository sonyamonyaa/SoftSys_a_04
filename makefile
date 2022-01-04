CC=gcc
AR=ar
FLAGS= -Wall -g
OBJ= main.o adjList.o Algo.o

all: graph

graph: main.o graphLib.a
		$(CC) $(FLAGS) -o graph main.o graphLib.a

graphLib.a: $(OBJ)
		$(AR) -rcs graphLib.a $(OBJ)

Algo.o: Algo.c Algo.h adjList.h
		$(CC) $(FLAGS) -c Algo.c

main.o: main.c adjList.h
		$(CC) $(FLAGS) -c main.c

adjList.o: adjList.c adjList.h
		$(CC) $(FLAGS) -c adjList.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so graph