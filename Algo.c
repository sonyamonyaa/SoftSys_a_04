#include <Algo.h>
#include <stdio.h>
#include <stdlib.h>

void init_path_mat(pathMat* M, Graph* g);
    
    unsigned int inf  = -1; //max value that can be held by an int

    M -> dimantions = g -> V;

    M -> weightMat = (int*) malloc(sizeof(int) * g -> V * g -> V);
    M -> preMat = (int*) malloc(sizeof(int) * g -> V g -> V);

    //initialising every value to inf
    for(int i = 0; i < g -> V; i++){
        for(int j = 0; j < g -> V; j++){

            M.weightMat[(g -> V * i) + j] = inf;
            M.preMat[(g -> V * i) + j] = -1;
        }
    }

    //executing first step of Fluid Warshall algorithm
    Node n = * g -> start;

    while(n != NULL){

        Edge e = *n.firstEdge;

        while(e != NULL){

            M -> weightMat[(g -> V * n.id) + e.destNode -> id] = e.weight;
            M -> preMat[(g -> V * n.id) + e.destNode -> id] = n.id;

            e = *e.nextEdge;
        }

        n = *n.nextNode;
    }


    //executing Fluid Warshall
    for(int i = 0; i < g -> V; i++){
        for(int j = 0; j < g -> V; j++){
            for(int k = 0; k < g -> V; k++){

                if(i != j){

                    int visitK = M -> weightMat[(i * g.V) + k]  +  M -> weightMat[(k * g.V) + j];

                    if( M -> weightMat[(i * g -> V) + j] > visitK){

                        M -> weightMat[(i * g -> V) + j] = visitK;
                        M -> preMat[(i * g -> V) + j] = k;
                    }
                }
            }
        }
    }

}

void freeMats(pathMat* M){

    free(M ->preMat);
    free(M -> weightMat);

    M -> preMat = NULL;
    M -> weightMat = NULL;
}

int pathLen(int src, int dest, pathMat* M){ return M -> weightMat[(M -> dimantions * src) + dest];}

void addToPath(path* P, int id){
    Node n = * P -> head;

    while( n != NULL){
        n = *n.nextNode;
    }

    n = (Node) malloc(sizeof(Node));
}

void mergePaths(path* p1, path* p2){

    Node n = * p1 -> head;

    if(n == NULL){ p1 -> head = p2 -> head; return;}

    while(*n.nextNode != NULL){
        n = *n.nextNode;
    }

    nextNode = p2 -> head;
}