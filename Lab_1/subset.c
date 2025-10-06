#include "mylib.h"

bool is_subset(long int set1, long int set2)
{
  return ((set1 & set2) == set1);
}

int main(int argc, char *argv[])
{
  // Check for correct number of arguments
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <set1.txt> <set2.txt>\n", argv[0]);
    return 1;
  }

  // Open the input files
  FILE *file1 = fopen("set1.txt", "r");

  long int set1 = 0L, set2 = 0L;

  // Read and prepare set1 in long int form
  set1 = make_set(file1, set1);

  fclose(file1);

  FILE *file2 = fopen("set2.txt", "r");

  // Read and prepare set2 in long int form
  set2 = make_set(file2, set2);

  fclose(file2);

  bool is_sub = is_subset(set1, set2);

  FILE *out = fopen("output.txt", "w");

  if (is_sub != 0)
  {
    fputs("TRUE", out);
  }
  else
  {
    fputs("FALSE", out);
  }

  // Print 1 if set1 is subset of set2 else print 0
  if (is_sub)
  {
    printf("1\n");
  }
  else
  {
    printf("0\n");
  }

  fclose(out);

  return 0;
}
