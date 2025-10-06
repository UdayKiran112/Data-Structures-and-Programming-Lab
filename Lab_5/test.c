#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

// Structure for adjacency list node
typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
} AdjNode;

// Structure for adjacency list
typedef struct AdjList {
    AdjNode* head;
} AdjList;

// Structure for graph
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Create a new adjacency node
AdjNode* newAdjNode(int dest, int weight) {
    AdjNode* node = (AdjNode*)malloc(sizeof(AdjNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Add an undirected edge
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* node = newAdjNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    // Undirected
    node = newAdjNode(src, weight);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

// Tree node structure
typedef struct TreeNode {
    int vertex;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Create a tree node
TreeNode* createTreeNode(int v) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->vertex = v;
    node->left = node->right = NULL;
    return node;
}

// Inorder traversal
void inorder(TreeNode* root, FILE* out) {
    if (!root) return;
    inorder(root->left, out);
    fprintf(out, "%d ", root->vertex);
    inorder(root->right, out);
}

// Find vertex with minimum key
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Prim's algorithm using adjacency list
void primMST(Graph* graph, int root, int parent[]) {
    int V = graph->V;
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[root] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        AdjNode* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            int w = temp->weight;
            if (!mstSet[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
}

// Build tree from parent array
TreeNode* buildTree(int parent[], int V, int root) {
    TreeNode* nodes[V];
    for (int i = 0; i < V; i++)
        nodes[i] = createTreeNode(i);

    TreeNode* treeRoot = nodes[root];
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            if (!nodes[parent[i]]->left)
                nodes[parent[i]]->left = nodes[i];
            else
                nodes[parent[i]]->right = nodes[i];
        }
    }
    return treeRoot;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");
    if (!in || !out) {
        printf("Error opening file.\n");
        return 1;
    }

    int V, E;
    fscanf(in, "%d %d", &V, &E);

    Graph* graph = createGraph(V);

    int u, v, w;
    int firstNode = -1;
    for (int i = 0; i < E; i++) {
        fscanf(in, "%d %d %d", &u, &v, &w);
        if (firstNode == -1) firstNode = u;
        addEdge(graph, u, v, w);
    }
    fclose(in);

    int parent[V];

    // MST from first node
    primMST(graph, firstNode, parent);
    TreeNode* tree1 = buildTree(parent, V, firstNode);
    fprintf(out, "MST starting from first node (%d):\n", firstNode);
    inorder(tree1, out);
    fprintf(out, "\n\n");

    // MST from random node
    srand(time(0));
    int randomNode = rand() % V;
    primMST(graph, randomNode, parent);
    TreeNode* tree2 = buildTree(parent, V, randomNode);
    fprintf(out, "MST starting from random node (%d):\n", randomNode);
    inorder(tree2, out);
    fprintf(out, "\n");

    fclose(out);
    printf("MSTs written to %s\n", argv[2]);
    return 0;
}
