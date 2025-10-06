#ifndef PRIM_H
#define PRIM_H

#include "graph.h"
#include <limits.h>
#include <stdbool.h>

int min_key(int V, int key[], bool in_mst[]);
void mst_prim(Graph *graph, int root, int parent[]);
Graph *build_mst(Graph *graph, int parent[], int root);
void inorder_traversal(Graph *mst_graph, int node, int parent, FILE *fp);

#endif