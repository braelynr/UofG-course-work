/**
 * @file QueueADT.h
 * @author Braelyn Rotman
 * @date June 2, 2018
 * @brief File containing the function definitions of a queue
 */

#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdio.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

/** queue structure: contains the list, front, back, and length of queue
 **/
typedef struct Queue{
  List * list;
  Node * front;
  Node * back;
  int * length;
}Queue;

/** car structure: this is the data that will be stored in the queue
 **/
typedef struct car{
  char direction;
  char turn;
  int arrivalTime;
  double queueTime;
}car;

/**  Creates and Initializes a queue. Allocates memory to the struct.
*@return pointer to the queue
**/
Queue * create();

/**  Function to delete all data within the queue
*@pre 'Queue' type must exist
*@param pQueue pointer to the queue to destroy
**/
void destroy(Queue *pQueue);

/**  Fucntion inserts a Node to the back of a queue.
*@pre 'Queue' type must exist
*@param pQueue pointer to the queue
*@param data a pointer to data that is to be added to the queue
**/
void enqueue(Queue *pQueue, void *data);

/**  Function removed a Node from the front of a queue.
*@pre 'Queue' type must exist and not be empty
*@param pQueue pointer to the queue
*@return the removed element
**/
void * dequeue(Queue *pQueue);

/** Function to look at the front of a queue without removing it.
*@pre 'Queue' type must exist and be initialized
*@param pQueue pointer to the queue
*@return the first element in the queue
**/
void * peek(Queue *pQueue);

/** Function to check if a queue is empty.
*@pre 'Queue' type must exist
*@param pQueue pointer to the queue
*@return true if empty or false if not
**/
bool isEmpty(Queue *pQueue);

/** Function to compare two elements
*@param first const void data
*@param second const void data
*@return -1 if first is smaller, 0 if equal, 1 if first is larger
**/
int compare(const void *first, const void *second);

#endif
