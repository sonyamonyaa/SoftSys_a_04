#ifndef _ADJLIST_H
#define _ADJLIST_H

/*
 * A graph data structure
 */
typedef struct Node Node;
typedef struct _Graph Graph;
struct _Graph {
    int V;
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
