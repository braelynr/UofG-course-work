/*
testing.c
July 8th, 2018
Braelyn Rotman
*/

#include "heap.h"
#include "heapADT.h"

#include <stdio.h>

void destroyData(void *data);
void printNode(void *toBePrinted);
int compare(const void *first, const void *second);
void printArray (Heap *heap);

int main(void){
  Heap *heap = NULL;
  int * i = malloc(sizeof(int));
  void *data = NULL;

  printf("---\nCreate Max Heap of Size 2\n");
  heap = createHeap(2, 1, &destroyData, &printNode, &compare);
  if (heap != NULL)
  {
    printf("Max Heap Successfully Created\n---\n");
  }
  else
  {
    printf("Heap creation unsuccessful\n---\n");
  }

  printArray(heap);

  printf("Insert int \"50\" into heap (first element)\n");
  *i = 50;
  data = (void *)(i);
  insertHeapNode(heap, data);
  if (heap->compare(heap->arr[0]->data, data) == 0)
  {
    printf("Successfully inserted 50 into heap\n---\n");
  }
  else
  {
    printf("Unsuccessful in inserting 50\n---\n");
  }

  printArray(heap);

  printf("Insert int \"60\" into heap (new root)\n");
  i = malloc(sizeof(int));
  *i = 60;
  data = (void *)(i);
  insertHeapNode(heap, data);
  if (heap->compare(heap->arr[0]->data, data) == 0)
  {
    printf("Successfully inserted 60 into heap\n---\n");
  }
  else
  {
    printf("Unsuccessful in inserting 60\n---\n");
  }

  printArray(heap);

  printf("REALLOC and Insert int \"40\" into heap (leftmost)\n");
    i = malloc(sizeof(int));
  *i = 40;
  data = (void *)(i);
  insertHeapNode(heap, data);
  if (heap->compare(heap->arr[2]->data, data) == 0)
  {
    printf("Successfully inserted 40 into heap\n---\n");
  }
  else
  {
    printf("Unsuccessful in inserting 40\n---\n");
  }

  printArray(heap);

  printf("Insert int \"70\" into heap (new root)\n");
  i = malloc(sizeof(int));
  *i = 70;
  data = (void *)(i);
  insertHeapNode(heap, data);
  if (heap->compare(heap->arr[0]->data, data) == 0)
  {
    printf("Successfully inserted 70 into heap\n---\n");
  }
  else
  {
    printf("Unsuccessful in inserting 70\n---\n");
  }

  printArray(heap);

  printf("Remove Root of Heap\n");
  i = malloc(sizeof(int));
  *i = 60;
  data = (void *)(i);
  deleteMinOrMax(heap);
  if (heap->compare(heap->arr[0]->data, data) == 0)
  {
    printf("Successfully removed root\n---\n");
  }
  else
  {
    printf("Unsuccessful in removing root\n---\n");
  }

  printArray(heap);

  printf("Change Heap Type\n\n");
  changeHeapType(heap);

  printArray(heap);

  printf("Delete Entire Heap\n\n");
  deleteHeap(heap);


  return 0;
}

void destroyData(void *data){
  HeapNode *delete = (HeapNode *)(data);
  delete->parent = NULL;
  delete->left = NULL;
  delete->right = NULL;
  free(delete->data);
}

void printNode(void *toBePrinted){

}

int compare(const void *first, const void *second){
  int *one = (int *)first;
  int *two = (int *)second;

  if (*one > *two)
  {
    return 1;
  }
  else if (*one < *two)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

void printArray (Heap *heap){
  int i = 0;
  int * iprint;

  printf("ARRAY: ");
  while (heap->arr[i] != NULL)
  {
    iprint = (int *)(heap->arr[i]->data);
    printf("[%d] ", *iprint);
    i++;
  }
  printf("\n");
}
