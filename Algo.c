#include "Algo.h"
#include <stdio.h>
#include <stdlib.h>

void init_path_mat(pathMat* M, Graph* g){
    
    int inf  = 9999;

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

    int visitK;
    //executing Fluid Warshall
    for(int i = 0; i < g -> V; i++){
        for(int j = 0; j < g -> V; j++){
            if(i != j){
                for(int k = 0; k < g -> V; k++){
                    if((k != i) && (k!=j)) {
                        visitK = M->weightMat[(i * g->V) + k] + M->weightMat[(k * g->V) + j];

                        if (M->weightMat[(i * g->V) + j] > visitK) {

                            M->weightMat[(i * g->V) + j] = visitK;
                            int last = M->preMat[(k * g->V) + j];
                            M->preMat[(i * g->V) + j] = last;
                        }
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
    P ->head =NULL;
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

    while( n != NULL){

        Node* tmp = n->nextNode;

        free(n);

        n = tmp;
    }

    P -> head = NULL;
    P -> weight = 0;
}

void addToPath(path* P, int id){

    Node *n = (Node*) malloc(sizeof(Node));

    n -> id = id;
    n -> firstEdge = NULL;
    n -> nextNode = NULL;

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
    P->weight = 0;
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
    if(n == NULL) return;
    while( n -> nextNode != NULL){
        if( n -> id == n -> nextNode -> id){
            n -> nextNode = n -> nextNode -> nextNode;
        }else{
            n = n -> nextNode;
        }
    }
}

void permute(path* P,int len){

    if( P->head == NULL){ return;}
    if( P ->head -> nextNode == NULL){ return;}

    Node* n = P -> head;

    for(int i = 0; i<len-1;i++){
        n = n -> nextNode;
    }

    n -> nextNode = P -> head;

    Node* m = P -> head -> nextNode;
    P -> head -> nextNode = NULL;
    P -> head = m;
}

void remmoveCities(path* cities, path* visited){

    Node* n = visited -> head;
    if(n == NULL){ return;}

    while(n != NULL){

        Node* m = cities -> head;

        while(m != NULL){

            if(m -> id == n -> id){
                cities -> head = m -> nextNode;
                m = cities -> head;
            }else{
                break;
            }
        }
        if(m!=NULL){
            while(m -> nextNode != NULL){

                if(m -> nextNode -> id == n -> id){
                    m -> nextNode = m -> nextNode -> nextNode;
                }else{
                    m = m -> nextNode;
                }
            }
        }
        n = n -> nextNode;
    }    
}

path* copyPath(path* P){

    path * ans = (path*) malloc(sizeof (path));

    Node * n = P -> head;
    if(n == NULL){
        return  ans;
    } else{
        ans -> head = (Node*) malloc(sizeof (path));
        ans -> head -> id = P -> head -> id;

        Node * m = ans -> head;
        while (n -> nextNode != NULL){
            m -> nextNode = (Node*) malloc(sizeof (Node));
            m -> nextNode -> id = n -> nextNode -> id;

            n = n -> nextNode;
            m = m -> nextNode;
        }
        m -> nextNode = NULL;

        return  ans;
    }
}

path* TSP(path* cities, pathMat* M){

    path* P = (path*) malloc(sizeof(path));
    P->head = NULL;
    path* P2;
    cities = copyPath(cities);

    int stop = cities -> head != NULL;
    if(! stop){ return  P;}

    while(stop){

        Node *n = P->head;
        if(n == NULL || cities -> head -> nextNode != NULL){
            P2 = shortestPath( cities -> head -> id, cities -> head -> nextNode -> id, M);
        } else{

            Node *last = P -> head;
            while ( last -> nextNode != NULL){ last = last -> nextNode;}

            P2 = shortestPath( last -> id, cities -> head -> id, M);
        }

        if(P2 == NULL){ return NULL;}

        mergePaths(P, P2);

        remmoveCities(cities,P);

        stop = cities -> head != NULL;
    }

    removeDoubles(P);
    return P;
}