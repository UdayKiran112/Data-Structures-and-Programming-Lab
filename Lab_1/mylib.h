#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

long int add(int num, long int S);
bool ismember(int num, long int S);
int count_elements(long int S);
long int make_set(FILE *file, long int S);
void write_set(FILE *file, long int S);

#endif
