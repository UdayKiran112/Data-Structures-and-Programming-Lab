#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "prim.h"

void write_mst_to_file(FILE *out, int root, Graph *mst_graph);
void process_file(FILE *in, FILE *out);

#endif
