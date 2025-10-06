#ifndef PARSER_H
#define PARSER_H

#include "heap_sort.h"

void parse_file(FILE *fp, int arr[], int length);
void count_length(FILE *fp, int *length);
void print_array(int arr[], int size);
void write_to_file(FILE *fp, int arr[], int size);

#endif
