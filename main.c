#include "adjList.h"
#include "Algo.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
    Graph *graph = createGraph(0);
    pathMat Mat;
    pathMat *M = &Mat;
    M->MC = -1;
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
                    continue;
                case 'B': //new node
                    scanf("%d", &id_node);
                    addNode(graph, id_node);
                    //add edges to the node
                    while (scanf("%d", &id_dest) == 1) {
                        scanf("%d", &weight);
                        addEdge(graph, id_node, id_dest, weight);
                    }
                    input = checkEOF();
                    continue;
                case 'D': //delete node
                    scanf("%d", &id_node);
                    removeNode(graph, id_node);
                    input = checkEOF();
                    continue;
                case 'S': //shortest path len

                    if (M == NULL) { init_path_mat(M, graph); }
                    else if (M->MC != graph->MC) { init_path_mat(M, graph); }

                    scanf("%d%d", &id_node, &id_dest);
                    len = distance(id_node, id_dest, M);
                    printf("Dijsktra shortest path: %d \n", len);
                    input = checkEOF();
                    continue;
                case 'T'://TSP

                    if (M->MC != graph->MC) {
                        init_path_mat(M, graph);
                    }

                    path *cities = (path *) malloc(sizeof(path));
                    cities -> head = NULL;
                    scanf("%d", &len);
                    for (int i = 0; i < len; i++) {
                        scanf("%d", &city);
                        addToPath(cities, city);
                    }

                    path *best = (path *)malloc( sizeof (path));
                    best ->head = NULL;
                    path *ans;
                    for(int i = 0; i < len; i++){

                        ans = TSP(cities, M);

                        if( ans != NULL){
                            if(best -> head == NULL){
                                best -> head = ans -> head;
                            } else{
                                updateWeight(ans, graph);
                                updateWeight(best, graph);

                                if( ans -> weight < best -> weight){ best -> head = ans -> head;}
                            }
                        }

                        permute( cities,len);
                    }

                    if( best -> head == NULL){
                        printf("TSP shortest path: -1 \n");
                    }else{
                        printf("TSP shortest path: %d \n", best->weight);
                    }

                    freePath(cities);
                    freePath(ans);
                    freePath(best);
                    free(ans);
                    free(cities);
                    free(best);

                    input = checkEOF();
                    continue;

                default:
                    break;
            }
            printGraph(graph);
            freeMats(M);
            freeGraph(graph);
            return 0;
        }
    }
}

char checkEOF() {
    char ch;
    if ((scanf("%c", &ch)) == EOF)
        return 'Z';//assign an input that isn't a command to get out
    else if (ch == ' ' || ch == '\n') {
        if ((scanf("%c", &ch)) == EOF)
            return 'Z';
    }
    return ch;
}

bool isCommand(char ch) {
    return (ch == 'A' || ch == 'B' || ch == 'D' || ch == 'S' || ch == 'T');
}