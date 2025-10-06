#include "parser.h"

void print_array(int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    fprintf(stdout, "%d\n", arr[i]);
  }
}

void count_length(FILE *fp, int *length)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file\n");
  }

  int num;
  while (fscanf(fp, "%d", &num) == 1)
  {
    (*length)++;
  }
}

void parse_file(FILE *fp, int arr[], int length)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file\n");
  }

  rewind(fp);

  for (int i = 0; i < length; i++)
  {
    fscanf(fp, "%d", &arr[i]);
  }

  // print_array(arr, length);

  // Sort using heap sort
  heap_sort(arr, length);
}

void write_to_file(FILE *fp, int arr[], int size)
{
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file\n");
  }

  for (int i = 0; i < size; i++)
  {
    if (i == size - 1)
      fprintf(fp, "%d", arr[i]);
    else
    {
      fprintf(fp, "%d\n", arr[i]);
    }
  }
}
