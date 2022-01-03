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
    int* preMat;
    int* weightMat;
    int dimantions;
}pathMat;

void init_path_mat(pathMat M, Graph g);

//tsp
//shortest path len
//shortest path
//add edge
int pathLen(int src, int dest);
int shortestPath(int src, int dest);

#endif //SOFTSYS_A_04_ALGO_H
