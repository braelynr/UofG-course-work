#include "LinkedListAPI.h"
#include "QueueADT.h"

Queue * create(){
  Queue * newQueue = malloc(sizeof(Queue));;
  List * newList = initializeList(NULL, NULL, &compare );
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

int compare( const void * first, const void * second){
  int arrive1, arrive2;
  arrive1 = ((car *) first)->arrivalTime;
  arrive2 = ((car *) second)->arrivalTime;
  if (arrive1 < arrive2)
  {
    return -1;
  }
  else if (arrive1 == arrive2)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
