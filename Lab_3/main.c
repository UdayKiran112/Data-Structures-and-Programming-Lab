#include "parser.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL)
  {
    fprintf(stderr, "Error opening file\n");
    return 1;
  }

  // Parse testing
  parse_file(input);

  // Close opened file
  fclose(input);

  // Write output to file
  FILE *output = fopen("output.txt", "w");
  if (output == NULL)
  {
    fprintf(stderr, "Error opening output file\n");
    return 1;
  }

  write_output(output);

  fclose(output);

  return 0;
}
