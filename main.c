#include "adjList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isCommand(char ch); //check whether a char is a command
char checkEOF(); //check if an input is an eof and returning an unrelated char

int main() {
    int id_node;
    int id_dest;
    int weight;
//    int res;
//    int cities;
//    int i,city;
    char input;
    int size;
//    int len;
    Graph *graph = NULL;
    scanf(" %c", &input);
    if (input != EOF) {
        while (isCommand(input)) {
            // A -> create graph
            switch (input) {
                case 'A':
                    scanf("%d", &size);
                    if (graph != NULL) {
                        if(graph->start != NULL)
                            freeGraph(graph);
                    }
                    int scanned;
                    graph = createGraph(size);
                    scanf("%s", &input);
                    while (input == 'n') {
                        scanf("%d", &id_node);
                        // Add the edges to the node
                        scanned=scanf("%d", &id_dest);
                        while (scanned == 1) {
                            scanf("%d", &weight);
                            addEdge(graph, id_node, id_dest, weight);
                            scanned=scanf("%d", &id_dest);
                        }
                        if(scanned==0){
                            input = checkEOF();
                        }
                    }
                    break;
                case 'B': //new node
                    scanf("%d", &id_node);
                    addNode(graph, id_node);
                    //add edges to the node
                    while (scanf("%d", &id_dest) == 1) {
                        scanf("%d", &weight);
                        addEdge(graph, id_node, id_dest, weight);
                    }
                    input = checkEOF();
                    break;
                case 'D': //delete node
                    scanf("%d", &id_node);
                    removeNode(graph, id_node);
                    input = checkEOF();
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
//        int V = 2;
//        Graph *graph = createGraph(V);
//        addEdge(graph, 0, 1, 2);
//        addEdge(graph, 0, 4, 5);
//        addEdge(graph, 1, 0, 1);
//    addEdge(graph, 1, 3, 2);
//    addEdge(graph, 1, 4, 6);
//    addEdge(graph, 2, 3, 1);
//    addEdge(graph, 3, 4, 2);
        }
        printGraph(graph);

//        removeNode(graph, 1);
        freeGraph(graph);

        // print the adjacency list representation of the above graph
        //freeGraph(graph);
        return 0;
    }
}

char checkEOF() {
    char ch;
    if (scanf("%c", &ch) == EOF)
        return 'Z';//assign an input that isn't a command to get out
    else if (ch == ' ') {
        if (scanf("%c", &ch) == EOF)
            return 'Z';
    }
    return ch;
}
bool isCommand(char ch) {
    return (ch == 'A' || ch == 'B' || ch == 'D' || ch == 'S' || ch == 'T' || ch == 'P');
}