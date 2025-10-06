#include "prim.h"

// create a new edge
Edge *create_edge(int from, int to, int weight)
{
    Edge *new = (Edge *)malloc(sizeof(Edge));
    new->from = from;
    new->to = to;
    new->weight = weight;
    new->next = NULL;
    return new;
}

// create a graph with V vertices
Graph *create_graph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;

    graph->array = (adjList *)malloc(V * sizeof(adjList));

    for (int i = 0; i < V; i++)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

// add an edge to the graph
void add_edge(Graph *graph, int from, int to, int weight)
{
    Edge *new_edge = create_edge(from, to, weight);

    // add edge at the beginning
    new_edge->next = graph->array[from].head;
    graph->array[from].head = new_edge;

    // Undirect graph : same edge in reverse order
    new_edge = create_edge(to, from, weight);
    new_edge->next = graph->array[to].head;
    graph->array[to].head = new_edge;
}

// print the graph
void print_graph(Graph *graph)
{
    for (int v = 0; v < graph->V; v++)
    {
        Edge *node = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (node != NULL)
        {
            printf("-> %d(w:%d) ", node->to, node->weight);
            node = node->next;
        }
        printf("\n");
    }
}