#ifndef _ADJLIST_H
#define _ADJLIST_H

/*
 * A graph data structure
 */
typedef struct Node Node;
typedef struct Edge Edge;
struct Node {
    int id;
    Node *nextNode;  //next node in the linked list of nodes
    Edge *firstEdge;  //first Edge of the adjacency list of this node
};

struct Edge {
    int weight;
    Node *destNode;  //Destination of the Edge
    Edge *nextEdge; //next Edge of the adjacency list
};

// A structure to represent a graph.
// Size of array will be V (number of vertices in graph)
typedef struct _Graph Graph;
struct _Graph {
    int V;
    int MC;// mod count
    Node *start;
};

/*
 * Creates a graph with V vertices
 */
Graph *createGraph(int V);

/*
 * resizes the graph when there's a new node
*/
void addNode(Graph *graph, int id);

/*
 *Add an edge from src to dest.
 *If needed, a new node is added to the adjacency list of src.  The node is added by the given weight;
*/
void addEdge(Graph *graph, int src, int dest, int weight);

/*
 * Delete a node in given src
 */
void removeNode(Graph *graph, int id);

/*
 * Frees the graph's memory
*/
void freeGraph(Graph *graph);

/*
 * prints Graph - mainly for dbg
 */
void printGraph(Graph *graph);


#endif
