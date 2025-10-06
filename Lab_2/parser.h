#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"

// Utility functions
void parse_file(FILE *fp, Student **studentHead);
void print_students(Student *head);
void write_to_file(FILE *fp, Student *head);

#endif
