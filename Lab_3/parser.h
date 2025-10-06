#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "datagram.h"

void parse_file(FILE *fp);
void write_output(FILE *fp);

#endif
