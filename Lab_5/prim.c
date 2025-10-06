#include "prim.h"

// find vertex with minimum key value
int min_key(int V, int key[], bool in_mst[])
{
    int min = INT_MAX, min_index = -1;

    for (int i = 0; i < V; i++)
    {
        if (in_mst[i] == false && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

// Prim's algorithm
void mst_prim(Graph *graph, int root, int parent[])
{
    int V = graph->V;
    int key[V];
    bool in_mst[V];

    // initialization of keys, mst set and parent
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        in_mst[i] = false;
        parent[i] = -1;
    }

    key[root] = 0; // root vertex key is 0

    for (int cnt = 0; cnt < V - 1; cnt++)
    {
        // find min key vertex
        int min = min_key(V, key, in_mst);

        if (min == -1)
        {
            fprintf(stderr, "Graph is disconnected\n");
            return;
        }

        // include this vertex in mst
        in_mst[min] = true;

        // update keys of adjacent vertices
        Edge *cur_node = graph->array[min].head;
        while (cur_node != NULL)
        {
            int to = cur_node->to;
            int weight = cur_node->weight;

            if (in_mst[to] == false && weight < key[to])
            {
                key[to] = weight;
                parent[to] = min;
            }

            cur_node = cur_node->next;
        }
    }
}

// Build MST Graph from parent array
Graph *build_mst(Graph *graph, int parent[], int root)
{
    int V = graph->V;
    Graph *mst_graph = create_graph(V);

    for (int i = 0; i < V; i++)
    {
        if (parent[i] != -1)
        {
            // find weight from original graph
            Edge *cur = graph->array[i].head;
            int w = 0;
            while (cur != NULL)
            {
                if (cur->to == parent[i])
                {
                    w = cur->weight;
                    break;
                }
                cur = cur->next;
            }

            if (i == root)
            {
                // add edge from root to parent
                add_edge(mst_graph, i, parent[i], w);
            }
            else
            {
                // add edge from parent to i
                add_edge(mst_graph, parent[i], i, w);
            }
        }
    }
    return mst_graph;
}

// recursive inorder traversal
void inorder_traversal(Graph *mst_graph, int node, int parent, FILE *fp)
{
    // Count number of children (excluding parent)
    int count = 0;
    Edge *curr = mst_graph->array[node].head;
    while (curr != NULL)
    {
        if (curr->to != parent)
        {
            count++;
        }
        curr = curr->next;
    }

    int half = count / 2;
    int i = 0;

    curr = mst_graph->array[node].head;

    // Traverse first half of children
    while (i < half && curr != NULL)
    {
        if (curr->to != parent)
        {
            inorder_traversal(mst_graph, curr->to, node, fp);
            i++;
        }
        curr = curr->next;
    }

    // Print current node
    fprintf(fp, "%d ", node);

    // Traverse second half of children
    while (curr != NULL)
    {
        if (curr->to != parent)
        {
            inorder_traversal(mst_graph, curr->to, node, fp);
        }
        curr = curr->next;
    }
}
