#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
    int from;
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct adjList
{
    Edge *head;
} adjList;

typedef struct Graph
{
    int V;
    adjList *array;
} Graph;

Edge *create_edge(int from, int to, int weight);
Graph *create_graph(int V);
void add_edge(Graph *graph, int from, int to, int weight);
void print_graph(Graph *graph);

#endif