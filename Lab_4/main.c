#include "parser.h"

int main(int argc, char *argv[])
{
  // Argument Error
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
    return 1;
  }

  int count = 0;

  FILE *input = fopen(argv[1], "r");

  count_length(input, &count);

  int arr[count];

  // Parse file for input
  parse_file(input, arr, count);

  FILE *output = fopen(argv[2], "w");

  // Write sorted array to output file
  write_to_file(output, arr, count);

  // Close Files
  fclose(input);
  fclose(output);

  return 0;
}
