// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>
#include "adjList.h"

//------------------------------------------------
// Edge implementation
//------------------------------------------------
typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

Edge *makeEdge(int src, int dest, int weight) {
    Edge *newEdge = (Edge *) malloc(sizeof(Edge));
    newEdge->src = src;
    newEdge->dest = dest;
    newEdge->weight = weight;
    return newEdge;
}

void freeEdge(Edge *edge) {
    if(edge == NULL) return;
    Edge *temp = edge;
    edge = NULL;
    free(temp);
}

//------------------------------------------------
// Adjacency List implementation
//------------------------------------------------

// A structure to represent an adjacency list node
typedef struct AdjListNode {
    Edge *edge;
    struct AdjListNode *next;
} Node;

void freeNode(Node *node) {
    if(node == NULL) return;
    freeEdge(node->edge);
    Node *temp = node;
    node = NULL;
    free(temp);
}

// A structure to represent an adjacency liat
typedef struct AdjacencyList {
    Node *head; // pointer to head node of list
} AdjList;

// A utility function to create a new adjacency list node
Node *newAdjListNode(Edge *edge) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->edge = edge;
    newNode->next = NULL;
    return newNode;
}

void freeList(AdjList *list) {
    if (list == NULL) return;
    Node *p1 = list->head;
    Node *p2;
    while (p1) {
        p2 = p1;
        p1 = p1->next;
        freeNode(p2);
    }
    list->head = NULL;
    AdjList *temp = list;
    free(temp);
}

//------------------------------------------------
// Graph implementation
//------------------------------------------------
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
typedef struct _Graph {
    int V;
    AdjList *array;
} Graph;

// A utility function that creates a graph of V vertices
Graph *createGraph(int V) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->V = V;
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (AdjList *) malloc(V * sizeof(AdjList));
    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

//resizes the graph when there's a new node
void addNode(Graph *graph, int src) {
    int v = graph->V;
    if (src > v) {
        v = src + 1;
        graph->array = (AdjList *) realloc(graph->array, v * sizeof(AdjList));
        graph->V = v;
    }
}


// Add an edge from src to dest.
// If needed, a new node is added to the adjacency list of src.  The node is added by the given weight;
void addEdge(Graph *graph, int src, int dest, int weight) {
    //check if an edge of the same src and dest and update it
    Edge *newEdge = makeEdge(src, dest, weight);
    Node *newNode;

    //init a list head if there's none
    if (graph->array[src].head == NULL) {
        newNode = newAdjListNode(newEdge);
        graph->array[src].head = newNode;
        return;
    }

    Node *tempNode = graph->array[src].head;
    Edge *tempEdge;
    while (tempNode != NULL) {
        tempEdge = tempNode->edge;
        if (tempEdge != NULL) {
            if (dest == tempEdge->dest) {
                tempNode->edge = newEdge;
                return;
            }
        }
        tempNode = tempNode->next;
    }
    //add new node;
    newNode = newAdjListNode(newEdge);
    tempNode = graph->array[src].head;
    while (tempNode->next != NULL) {
        tempEdge = tempNode->edge;
        if (weight > tempEdge->weight)
            tempNode = tempNode->next;
        else
            break;
    }
    newNode->next = tempNode->next;
    tempNode->next = newNode;
}

void removeNode(Graph *graph, int src) {
    if (graph->array[src].head != NULL) {
        for (int v = 0; v < graph->V; ++v) {
            Node *node = graph->array[v].head;
            Node *temp;
            Edge *edge;
            while (node != NULL) {
                edge = node->edge;
                if (edge != NULL)
                    if (edge->dest == src || edge->src == src) {
                        temp = node;
                        //node = node -> next;
                        freeNode(temp);//its edge is freed along with the node
                        break;
                    }
                node = node->next;
            }
        }
        freeList(&graph->array[src]);
    }
}

// frees the graph's memory
void freeGraph(Graph *graph) {
    int v;
    for (v = 0; v < graph->V; ++v) {
        freeList(&graph->array[v]);
    }
}

void printGraph(Graph *graph) {
    int v;
    for (v = 0; v < graph->V; ++v) {
        Node *pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head [%d]", v, v);
        while (pCrawl) {
            printf(" -> %d(%d)", pCrawl->edge->dest, pCrawl->edge->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");

    }

}
