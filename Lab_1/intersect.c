#include "mylib.h"

int cal_intersection(long int set1, long int set2, long int *result)
{
  *result = set1 & set2;
  return count_elements(*result);
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
  FILE *file1 = fopen(argv[1], "r");

  long int set1 = 0L, set2 = 0L;

  // Read and prepare set1 in long int form
  set1 = make_set(file1, set1);

  fclose(file1);

  FILE *file2 = fopen(argv[2], "r");

  // Read and prepare set2 in long int form
  set2 = make_set(file2, set2);

  fclose(file2);

  long int intersection_set = 0L;
  int size = cal_intersection(set1, set2, &intersection_set);

  FILE *out = fopen("output.txt", "w");

  // Write the set to output file
  write_set(out, intersection_set);

  // Print size of intersection set to console
  printf("Size of intersection set: %d\n", size);

  fclose(out);

  return 0;
}
