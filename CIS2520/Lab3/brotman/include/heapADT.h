/**
 * @file HeapAPI.h
 * @author Braelyn Rotman
 * @date June 2018
 * @brief File containing the structures of a heap
 */

#ifndef HEAPADT_H
#define HEAPADT_H

#include <stdlib.h>

/**
*HeapNode structure
**/
typedef struct Node
{
  void *data; ///< contains void type data
  struct Node *left; ///< contains left child node
  struct Node *right; ///< contains right child node
  struct Node *parent; ///< contains parent node
} HeapNode;

/**
*Heap structure
**/
typedef struct Heap
{
    HeapNode **arr; /// array that contains all of the heap nodes
    HEAP_TYPE type; ///< flag for choosing between min and max heap
    HeapNode * lastPosition; //optional element useful for finding where to insert the next value
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
    int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    int size; ///< number of elements in array
}Heap;

/** Swaps parent and child nodes to satisfy heap requirements
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param HeapNode pointer to the recently inserted node
**/
void heapify (Heap *heap, HeapNode * newNode);


#endif
