#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
    return 1;
  }

  FILE *input_file = fopen(argv[1], "r");
  if (input_file == NULL)
  {
    fprintf(stderr, "Error opening file\n");
    return 1;
  }

  // Declare Student head
  Student *studentHead = NULL;

  // Parse the file and build the database
  parse_file(input_file, &studentHead);

  // Close the file after parsing
  fclose(input_file);

  // Print all students and their courses
  print_students(studentHead);

  // Write the student and course data back to a file
  FILE *out = fopen(argv[2], "w");
  write_to_file(out, studentHead);
  fclose(out);

  // Free the student list
  freeStudentList(studentHead);

  return 0;
}
