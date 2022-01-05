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
    char input;
    int size;
    int len =-1;
    int city;
    //add vars here pls
    Graph *graph = createGraph(0);
    scanf(" %c", &input);
    if (input != EOF) {
        while (isCommand(input)) {
            // A -> create graph
            switch (input) {
                case 'A':
                    scanf("%d", &size);
                    if (graph) {
                        if(graph->start != NULL)
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
                    scanf("%d", &id_node);
                    scanf("%d", &id_dest);
                    //len = distance(src:id_node,dest:id_dest) idk
                    printf("Dijsktra shortest path: %d \n",len);
                    break;
                case 'T'://TSP
                    scanf("%d",&len); //cities len
                    for(int i = 0;i<len;i++) {
                        scanf("%d", &city);
                        //add city to a path I guess?
                    }
                    printf("TSP shortest path: %d \n",len);
                    break;
                default: //so IDE wouldn't scream at me ;-;
                    break;
            }
        }
        printGraph(graph); // for dbg
        freeGraph(graph); // free at the end of program
        return 0;
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
}