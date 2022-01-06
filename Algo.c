#include "Algo.h"
#include <stdio.h>
#include <stdlib.h>

void init_path_mat(pathMat* M, Graph* g){
    
    unsigned int inf  = -1; //max value that can be held by an int

    M -> dimantions = g -> V;
    M -> MC = g -> MC;

    M -> weightMat = (int*) malloc(sizeof(int) * g -> V * g -> V);
    M -> preMat = (int*) malloc(sizeof(int) * g -> V * g -> V);

    //initialising every value to inf
    for(int i = 0; i < g -> V; i++){
        for(int j = 0; j < g -> V; j++){

            M -> weightMat[(g -> V * i) + j] = inf;
            M -> preMat[(g -> V * i) + j] = -1;
        }
    }

    //executing first step of Fluid Warshall algorithm
    Node *n =  g -> start;

    while(n != NULL){

        Edge *e = n->firstEdge;

        while(e != NULL){

            M -> weightMat[(g -> V * n -> id) + e -> destNode -> id] = e -> weight;
            M -> preMat[(g -> V * n -> id) + e -> destNode -> id] = n -> id;

            e = e -> nextEdge;
        }

        n = n -> nextNode;
    }


    //executing Fluid Warshall
    for(int i = 0; i < g -> V; i++){
        for(int j = 0; j < g -> V; j++){
            for(int k = 0; k < g -> V; k++){

                if(i != j){

                    int visitK = M -> weightMat[(i * g -> V) + k]  +  M -> weightMat[(k * g -> V) + j];

                    if( M -> weightMat[(i * g -> V) + j] > visitK){

                        M -> weightMat[(i * g -> V) + j] = visitK;

                        M -> preMat[(i * g -> V) + j] = M -> preMat[(k * g -> V) + j];
                    }
                }
            }
        }
    }

}

void freeMats(pathMat* M){

    free(M -> preMat);
    free(M -> weightMat);

    M -> preMat = NULL;
    M -> weightMat = NULL;
}

path* shortestPath(int src, int dest, pathMat* M) {
    path *P = (path *) malloc(sizeof(path));
    addToPath(P, dest);
    int curr = dest;
    while (curr != src) {
        int last = M->preMat[(M->dimantions * src) + curr];
        if (last == -1) { return NULL; }
        addToPath(P, last);
        curr = last;
    }
    return P;
}

int distance(int src, int dest, pathMat* M){
        return M -> weightMat[(M -> dimantions * src) + dest];
}

void freePath(path* P){

    Node* n = P -> head;

    while( n -> nextNode != NULL){

        Node* tmp = n->nextNode;

        free(n);

        n = tmp;
    }

    P -> head = NULL;
    P -> weight = 0;
}

void addToPath(path* P, int id){

    Node *n = (Node*) malloc(sizeof(Node));

    n -> id = id; n -> nextNode = NULL; n -> firstEdge = NULL;

    Node* c = P -> head;

    if( c == NULL){

        P -> head = n;
        
    }else{

        n -> nextNode = c;
        P -> head = n;
    }
}

void mergePaths(path* p1, path* p2){

    Node *n = p1 -> head;
    if(n == NULL){ p1 -> head = p2 -> head; return;}
    while(n -> nextNode != NULL){
        n = n -> nextNode;
    }
    n -> nextNode = p2 -> head;
}

void updateWeight(path* P, Graph* g){

    Node* n = P -> head;
    Edge* q;
    //length < 2
    if(n == NULL){ P -> weight = 0;}
    if( n -> nextNode == NULL){ P -> weight = 0;}

    while(n -> nextNode != NULL){
        q = getEdge(g, n -> id, n -> nextNode -> id);
        P -> weight += q->weight;
        n = n -> nextNode;
    }
}
void removeDoubles(path* P){
    Node* n = P -> head;
    while( n -> nextNode != NULL){
        if( n -> id == n -> nextNode -> id){
            n -> nextNode = n -> nextNode -> nextNode;
        }else{
            n = n -> nextNode;
        }
    }
}
path* TSP(path* cities, pathMat* M){
    Node* n = cities -> head;
    path* P = (path*) malloc(sizeof(path));
    while(n -> nextNode != NULL){
        path* P2 = shortestPath( n -> id, n -> nextNode -> id, M);
        if(P2 == NULL){
            return NULL;
        }
        mergePaths(P, P2);
    }
    removeDoubles(P);
    return P;
}