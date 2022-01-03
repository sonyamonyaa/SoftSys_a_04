#include "adjList.h"
#include <stdio.h>
int main() {
    // A -> create graph
    char ch;
    scanf(" %c",&ch);
    int size;
    Graph* graph;// = createGraph(0);
    while (ch != EOF) {
        // A -> create graph
        switch (ch) {
            case 'A':
                if(graph->start != NULL)
                    freeGraph(graph);
                scanf("%d",&size);
                graph = createGraph(size);
                scanf(" %c",ch);
                while (ch == 'n'){
                    int node_id,dest_id,weight;
                    scanf(" %d",&node_id);
                    //add condition to keep get these till next n
                    scanf("%d",&dest_id);
                    scanf("%d",&weight);
                    addEdge(graph,node_id,dest_id,weight);
                    scanf(" %c",ch);
                }
                break;
            case 'B': //new node
                break;
            case 'S': //shortest path len
                break;
            case 'P': //shortest path
                break;
            case 'T'://TSP
                break;
            default:
                printGraph(graph);
        }
        int V = 2;
        graph = createGraph(V);
        addEdge(graph, 0, 1, 2);
        //addEdge(graph, 0, 4, 5);
        addEdge(graph, 1, 0, 1);
//    addEdge(graph, 1, 3, 2);
//    addEdge(graph, 1, 4, 6);
//    addEdge(graph, 2, 3, 1);
//    addEdge(graph, 3, 4, 2);

        printGraph(graph);

        removeNode(graph, 1);
    }
    freeGraph(graph);

    // print the adjacency list representation of the above graph
    //freeGraph(graph);
    return 0;
}
