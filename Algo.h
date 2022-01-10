//
// Created by S on 02/01/2022.
//

#ifndef SOFTSYS_A_04_ALGO_H
#define SOFTSYS_A_04_ALGO_H
#include "adjList.h"

/*
  A structure to hold the weights of the shortest paths
  between any 2 nodes  &  one to keep track of the latest visit
  of any path inorder to recreate the paths
*/

typedef struct pathMat{
    int* weightMat;
    int* preMat;
    int MC;
    int dimantions;
}pathMat;

void init_path_mat(pathMat* M, Graph* g);

void freeMats(pathMat* M);

//tsp
//shortest path len
//shortest path
//add edge

/*
    A structure that represant a path in the graph
    simlply a list of int's (ids)
*/
typedef struct Path{ 
  Node* head;
  int weight;
} path;

void addToPath(path* P, int id);

void mergePaths(path* p1, path* p2);

void removeDoubles(path* P);

void updateWeight(path* P, Graph* g);

void freePath(path* P);

void printPath(path* P);

void permute(path* P, int len);

int distance(int src, int dest, pathMat* M);

path* TSP(path* cities, pathMat* M);

#endif //SOFTSYS_A_04_ALGO_H
