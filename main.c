#include "adjList.h"
int main() {
    int V = 2;
    Graph *graph = createGraph(V);
    addEdge(graph, 0, 1, 2);
    //addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
//    addEdge(graph, 1, 3, 2);
//    addEdge(graph, 1, 4, 6);
//    addEdge(graph, 2, 3, 1);
//    addEdge(graph, 3, 4, 2);

    printGraph(graph);

    //removeNode(graph, 1);

    // print the adjacency list representation of the above graph
    freeGraph(graph);
    return 0;
}
