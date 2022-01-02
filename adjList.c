// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include "adjList.h"

//------------------------------------------------
// Adjacency List implementation
//------------------------------------------------
struct _Node {
    int id;
    struct _Node *nextNode;  //next node in the linked list of nodes
    struct _Edge *firstEdge;  //first Edge of the adjacency list of this node
};

typedef struct _Node Node;
struct _Edge {
    int weight;
    struct _Node *destNode;  //Destination of the Edge
    struct _Edge *nextEdge; //next Edge of the adjacency list
};
typedef struct _Edge Edge;
//Node *find(int u);
//void addNode(int u);
//void insertEdge(int u,int v);
//void deleteEdge(int u,int v);
//void deleteIncomingEdges(int u);
//void deleteVertex(int u);
//void display();
//------------------------------------------------
// Graph implementation
//------------------------------------------------

// A structure to represent a graph. 
// Size of array will be V (number of vertices in graph)
typedef struct _Graph {
    int V;
    Node *start;
} Graph;

// A utility function that creates a graph of V vertices
Graph *createGraph(int V) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->V = 0;
    // Create a list of V nodes
    graph->start = NULL;
    for (int i = 0; i < V; i++) {
        addNode(graph, i);
    }
    return graph;
}

//finds a node with id
Node *find(Graph *graph, int id) {
    Node *ptr, *loc;
    ptr = graph->start;
    while (ptr != NULL) {
        if (ptr->id == id) {
            loc = ptr;
            return loc;
        } else
            ptr = ptr->nextNode;
    }
    loc = NULL;
    return loc;
}

//method deletes edges where their destination's ids equal to id
void deleteInEdges(Graph *graph, int id) {
    Node *ptr;
    Edge *q, *tmp;

    ptr = graph->start;
    while (ptr != NULL) {
        if (ptr->firstEdge == NULL)   //Edge list for node ptr is empty
        {
            ptr = ptr->nextNode;
            continue; // continue searching in other Edge lists
        }

        if (ptr->firstEdge->destNode->id == id) {
            tmp = ptr->firstEdge;
            ptr->firstEdge = ptr->firstEdge->nextEdge;
            free(tmp);
            continue; // continue searching in other Edge lists
        }
        q = ptr->firstEdge;
        while (q->nextEdge != NULL) {
            if (q->nextEdge->destNode->id == id) {
                tmp = q->nextEdge;
                q->nextEdge = tmp->nextEdge;
                free(tmp);
                continue;
            }
            q = q->nextEdge;
        }
        ptr = ptr->nextNode;
    }
}

void removeEdges(Graph *graph, int src) {
    Node *pSrc = find(graph, src);
    Edge *p, *tmp;
    p = pSrc->firstEdge;
    while (p != NULL) {
        tmp = p;
        p = p->nextEdge;
        free(tmp);
    }
}
void addNode(Graph *graph, int id) {
    Node *ptr = find(graph, id);
    if(ptr !=NULL){
        removeEdges(graph, id);
        ptr ->firstEdge = NULL;
        return;
    }
    Node *tmp = malloc(sizeof(Node));
    tmp->id = id;
    tmp->nextNode = NULL;
    tmp->firstEdge = NULL;
    graph->V++; //update the graph's size
    if (graph->start == NULL) {
        graph->start = tmp;
        return;
    }
    ptr = graph->start;
    while (ptr->nextNode != NULL) {
        ptr = ptr->nextNode;
    }
    ptr->nextNode = tmp;
}
void removeNode(Graph *graph, int id) {
    graph->V--; //decrease size
    if(find(graph,id)==NULL) return;
    //assuming the node exists, free all edges going in and out from this node
    deleteInEdges(graph, id);
    removeEdges(graph, id);
    Node *tmp, *q;
    if (graph->start->id == id)/* Node to be deleted is first node of list*/
    {
        tmp = graph->start;
        graph->start = graph->start->nextNode;
    } else /* Node to be deleted is in between or at last */
    {
        q = graph->start;
        while (q->nextNode != NULL) {
            if (q->nextNode->id == id)
                break;
            q = q->nextNode;
        }
        if (q->nextNode == NULL) {
            printf("Node not found\n");
            return;
        } else {
            tmp = q->nextNode;
            q->nextNode = tmp->nextNode;
        }
    }
    free(tmp);
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    Node *srcNode, *destNode;
    Edge *ptr, *tmp;

    srcNode = find(graph, src);
    destNode = find(graph, dest);

    if (srcNode == NULL) {
        printf("\nStart node not present, first insert node %d\n", src);
        return;
    }
    if (destNode == NULL) {
        printf("\nEnd node not present, first insert node %d\n", dest);
        return;
    }
    tmp = malloc(sizeof(Edge));
    tmp->weight = weight;
    tmp->destNode = destNode;
    tmp->nextEdge = NULL;

    if (srcNode->firstEdge == NULL) {
        srcNode->firstEdge = tmp;
        return;
    }
    if (srcNode->firstEdge->destNode == destNode) {
        tmp->nextEdge = srcNode->firstEdge->nextEdge;
        srcNode->firstEdge = tmp;
        return;
    }
    ptr = srcNode->firstEdge;
    while (ptr->nextEdge != NULL) {
        if (ptr->nextEdge->destNode == destNode) {
            tmp->nextEdge = ptr->nextEdge->nextEdge;
            ptr->nextEdge = tmp;
            return;
        }
        ptr = ptr->nextEdge;
    }
    ptr->nextEdge = tmp;
}


// frees the graph's memory
void freeGraph(Graph *graph) {
    Node *q;
    q = graph->start;
    while (q != NULL) {
        removeNode(graph, q->id);
        q = q->nextNode;
    }
    free(graph);
}


void printGraph(Graph *graph) {
    Node *ptr;
    Edge *q;

    ptr = graph->start;
    while (ptr != NULL) {
        printf("%d ->", ptr->id);
        q = ptr->firstEdge;
        while (q != NULL) {
            printf(" %d:(%d)", q->destNode->id,q->weight);
            q = q->nextEdge;
        }
        printf("\n");
        ptr = ptr->nextNode;
    }
}