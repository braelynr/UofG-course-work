/*//////////////////////////
Assignment 2
CIS 2520
Braelyn Rotman
ID: 1006740
brotman@uoguelph.ca
July 16th, 2018
Queue.c
//////////////////////////*/

#include "LinkedListAPI.h"
#include "QueueADT.h"

Queue * create(){
  Queue * newQueue = malloc(sizeof(Queue));;
  List * newList = initializeList(NULL, NULL, NULL );
  newQueue->front = NULL;
  newQueue->back = NULL;
  newQueue->list = newList;
  newQueue->length = 0;

  return newQueue;
}

void destroy(Queue *pQueue){
  if (pQueue != NULL) /* if queue exists */
  {
    pQueue->front = NULL;
    pQueue->back = NULL;
    pQueue->length = 0;
    deleteList(pQueue->list);
  }
}

void enqueue(Queue *pQueue, void *data){
  insertBack(pQueue->list, data);
  pQueue->back = pQueue->list->tail;
  pQueue->front = pQueue->list->head;
  pQueue->length = pQueue->length + 1;
}

void * dequeue(Queue *pQueue){
  void * removedElement = pQueue->front;
  deleteDataFromList(pQueue->list, pQueue->front->data);
  pQueue->front = pQueue->list->head;
  pQueue->length = pQueue->length - 1;

  return removedElement;
}

void * peek(Queue *pQueue){
  if (pQueue != NULL && pQueue->front != NULL) /* if queue exists and is not empty */
  {
    return getFromFront(pQueue->list);
  }
  return NULL;
}

bool isEmpty(Queue *pQueue){
  if (pQueue->list->head != NULL) /* list is not empty */
  {
    return false;
  }
  return true;
}
