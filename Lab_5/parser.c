#include "parser.h"

void process_file(FILE *in, FILE *out)
{
  if (in == NULL)
  {
    fprintf(stderr, "Error opening input file\n");
  }

  if (out == NULL)
  {
    fprintf(stderr, "Error opening output file\n");
  }

  char line[256]; // buffer

  int no_of_vertices, no_of_edges;
  Graph *graph;

  // Read first line for number of vertices and edges
  if (fgets(line, sizeof(line), in) == NULL)
  {
    fprintf(stderr, "Error reading number of vertices\n");
    return;
  }
  else
  {
    sscanf(line, "%d %d", &no_of_vertices, &no_of_edges);

    // Create graph
    graph = create_graph(no_of_vertices);

    printf("Vertices: %d, Edges: %d\n", no_of_vertices, no_of_edges);
  }

  int parent[no_of_vertices];
  int root = 0;

  while (fgets(line, sizeof(line), in))
  {
    int u, v, weight;
    if (sscanf(line, "%d %d %d", &u, &v, &weight) != 3)
    {
      fprintf(stderr, "Error reading edge data\n");
      continue;
    }

    // add edge to graph
    add_edge(graph, u, v, weight);
  }

  // // Print the original graph
  // printf("Original Graph:\n");
  // print_graph(graph);

  // Build MST using Prim's algorithm
  mst_prim(graph, root, parent);

  Graph *mst_graph_1 = build_mst(graph, parent, root);

  // write MST to output file
  write_mst_to_file(out, root, mst_graph_1);

  // seeding with time as seed
  srand(time(NULL));

  // pick random root
  root = rand() % no_of_vertices;
  printf("Random Root: %d\n", root);

  mst_prim(graph, root, parent);

  Graph *mst_graph_2 = build_mst(graph, parent, root);

  // write MST to output file
  write_mst_to_file(out, root, mst_graph_2);
}

void write_mst_to_file(FILE *out, int root, Graph *mst_graph)
{
  fprintf(out, "MST with root %d:\n", root);
  inorder_traversal(mst_graph, root, -1, out);
  fprintf(out, "\n");
}