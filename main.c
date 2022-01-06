#include "adjList.h"
#include "Algo.h"
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
    char input;
    int size;
//    int len;
    int len = -1;
    int city;
    //add vars here pls
    pathMat *M = NULL;
    Graph *graph = createGraph(0);
    scanf(" %c", &input);

    if (input != EOF) {
        while (isCommand(input)) {
            // A -> create graph
            switch (input) {
                case 'A':
                    scanf("%d", &size);
                    if (graph) {
                        if (graph->start != NULL)
                            freeGraph(graph);
                    }
                    graph = createGraph(size);
                    scanf(" %c", &input);
                    while (input == 'n') {
                        scanf("%d", &id_node);
                        // Add the edges to the node
                        while (scanf("%d", &id_dest) == 1) {
                            scanf("%d", &weight);
                            addEdge(graph, id_node, id_dest, weight);
                        }
                        input = checkEOF();
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
                    if (M == NULL) { init_path_mat(M, graph); }
                    if (M->MC != graph->MC) { init_path_mat(M, graph); }
                    scanf("%d%d", &id_node, &id_dest);
                    len = distance(id_node, id_dest, M);
                    printf("Dijsktra shortest path: %d \n", len);
                    input = checkEOF();
                    break;
                case 'T'://TSP
                    scanf("%d", &len); //cities len
                    for (int i = 0; i < len; i++) {
                        scanf("%d", &city);
                        //add city to a path I guess?
                    }
                    printf("TSP shortest path: %d \n", len);
                    input = checkEOF();
                    break;
                default:
                    break;
            }
            printGraph(graph);
            freeGraph(graph);
            return 0;
        }
    }
}

char checkEOF() {
    char ch;
    if ((scanf("%c",&ch)) == EOF)
        return 'Z';//assign an input that isn't a command to get out
    else if (ch == ' ' || ch == '\n') {
        if ((scanf("%c",&ch)) == EOF)
            return 'Z';
    }
    return ch;
}
bool isCommand(char ch) {
    return (ch == 'A' || ch == 'B' || ch == 'D' || ch == 'S' || ch == 'T');