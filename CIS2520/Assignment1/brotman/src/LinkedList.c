#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){

  List *newList = malloc(sizeof(List));

  newList->head = NULL;
  newList->tail = NULL;
  newList->printData = printFunction;
  newList->deleteData = deleteFunction;
  newList->compare = compareFunction;

  return newList;
}

/**Function for creating a node for a linked list. This node contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data){

  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  newNode->previous = NULL;

  return newNode;
}

/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded){

  Node *newNode = initializeNode(toBeAdded);
  if (list == NULL)
  {
    free(newNode);
    return;
  }
  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
    return;
  }

  newNode->next = list->head;
  list->head->previous = newNode;
  list->head = newNode;
}

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded){

  Node *newNode = initializeNode(toBeAdded);

  if (list == NULL)
  {
    free(newNode);
    return;
  }
  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
    return;
  }

  list->tail->next = newNode;
  newNode->previous = list->tail;
  list->tail = newNode;
}

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list){

  Node *temp;

  if (list == NULL || list->head == NULL)
  {
      return;
  }
  while(list->head != NULL)
  {
    temp = list->head;

    list->head = list->head->next;
    temp->next = NULL;
    free(temp->data);
    free(temp);
  }
}

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded)
{
  Node *temp;
  Node *newNode;
  car *car1;
  car *car2;

  if (list == NULL)
  {
    return;
  }
  newNode = initializeNode(toBeAdded);

  if (list->head == NULL) /* empty list */
  {
    list->head = newNode;
    list->tail = newNode;
    return;
  }

  temp = list->head;
  while (temp != NULL)
  {
    car1 = temp->data;
    car2 = newNode->data;

    if (list->compare(car2, car1) <= 0) /* insert before temp */
    {
      if (temp == list->head)
      {
        list->head = newNode;
        newNode->next = temp;
        temp->previous = newNode;
        return;
      }
      temp->previous->next = newNode;
      newNode->previous = temp->previous;
      temp->previous = newNode;
      newNode->next = temp;

      return;
    }

    temp = temp->next;
  }

  list->tail->next = newNode;
  newNode->previous = list->tail;
  list->tail = newNode;
}

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure.
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteDataFromList(List *list, void *toBeDeleted){

  Node *temp;
  if (list == NULL || list->head == NULL)
  {
    return 0;
  }

  temp = list->head;
  while (temp != NULL)
  {
    if (temp->data == toBeDeleted)
    {

      if (temp == list->head) /* head of list */
      {
        list->head = temp->next;
        if (list->head != NULL)
        {
          list->head->previous = NULL;
        }
      }
      else if (temp->next == NULL) /* tail of list */
      {
        if (temp->previous != NULL)
        {
          temp->previous->next = NULL;
        }
        list->tail = temp->previous;
      }
      else /* middle node */
      {
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
      }

      free(temp->data);
      free(temp);
      return 0;
    }

    temp = temp->next; /* move through list */
  }
  return -1;
}

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list){

  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }
  return list->head->data;
}

/**Function to return the data at the back of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the tail of the list
 *@return pointer to the data located at the tail of the list
 **/
void *getFromBack(List *list){

    if (list == NULL || list->head == NULL)
    {
      return NULL;
    }
    return list->tail->data;
}

/**Function to print list from head to tail. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list){

  Node *temp;
  if (list == NULL)
  {
    return;
  }
  temp = list->head;
  while (temp != NULL)
  {
    list->printData(temp->data);
    temp = temp->next;
  }
}

/**Function to print list from tail to head. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list){

  Node *temp;
  if (list == NULL)
  {
    return;
  }
  temp = list->tail; /* start at tail */
  while (temp != NULL)
  {
    list->printData(temp->data);
    temp = temp->previous;
  }
}
