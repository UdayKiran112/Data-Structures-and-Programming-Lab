#include "mylib.h"

long int add(int num, long int S)
{
  if (num < 1 || num > 64)
  {
    fprintf(stderr, "Error values are not in range: %d\n", num);
    exit(1);
  }
  return (S | (1L << (num - 1)));
}

bool ismember(int num, long int S)
{
  if (num < 1 || num > 64)
  {
    fprintf(stderr, "Error values are not in range: %d\n", num);
    exit(1);
  }
  return ((S & (1L << (num - 1))) != 0);
}

int count_elements(long int S)
{
  int count = 0;
  for (int i = 1; i < 65; i++)
  {
    if (ismember(i, S))
    {
      count++;
    }
  }
  return count;
}

long int make_set(FILE *file, long int S)
{
  if (file == NULL)
  {
    fprintf(stderr, "Error opening file\n");
    return 0;
  }
  int num;
  while (fscanf(file, "%d ", &num) == 1)
  {
    S = add(num, S);
  }
  return S;
}

void write_set(FILE *file, long int S)
{
  if (!file)
  {
    fprintf(stderr, "Error opening file\n");
    return;
  }

  int first = 1; // Flag to track the first element
  for (int i = 1; i < 65; i++)
  {
    if (ismember(i, S))
    {
      if (!first)
      {
        fprintf(file, "\n"); // Print newline before every element except the first
      }
      fprintf(file, "%d", i);
      first = 0; // Clear the flag after printing the first element
    }
  }
}
