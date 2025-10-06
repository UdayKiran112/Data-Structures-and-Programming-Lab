#include "mylib.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <set1.txt> <set element>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    long int set = 0L;

    // Read and prepare set in long int form
    set = make_set(file, set);

    fclose(file);

    // Convert element to integer
    int element = atoi(argv[2]);

    bool is_member = ismember(element, set);

    // Print 1 if element is in the set else print 0
    if (is_member)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}