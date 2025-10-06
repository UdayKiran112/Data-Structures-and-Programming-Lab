#include "parser.h"

int main(int argc, char *argv[])
{
    // Argument Error
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    // Parse file for input
    process_file(input, output);

    // Close Files
    fclose(input);
    fclose(output);

    return 0;
}
