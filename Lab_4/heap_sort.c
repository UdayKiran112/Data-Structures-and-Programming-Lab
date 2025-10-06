#include "heap_sort.h"

static int left(int index)
{
  return 2 * index + 1;
}

static int right(int index)
{
  return (2 * index + 2);
}

// static int parent(int index)
// {
//   return (index - 1) / 2;
// }

static void max_heapify(int arr[], int size, int index)
{
  int l = left(index);
  int r = right(index);
  int largest;
  if (l < size && arr[l] > arr[index])
  {
    largest = l;
  }
  else
  {
    largest = index;
  }

  if (r < size && arr[r] > arr[largest])
  {
    largest = r;
  }

  if (largest != index)
  {
    int temp = arr[index];
    arr[index] = arr[largest];
    arr[largest] = temp;
    max_heapify(arr, size, largest);
  }
}

static void build_max_heap(int arr[], int size)
{
  for (int i = (size / 2) - 1; i >= 0; i--)
  {
    max_heapify(arr, size, i);
  }
}

void heap_sort(int arr[], int size)
{
  build_max_heap(arr, size);
  for (int i = size - 1; i > 0; i--)
  {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    size--;
    max_heapify(arr, size, 0);
  }
}