/*
Lab 2
CIS 2520
Braelyn Rotman
June 18th, 2018
HashTable.c
*/

#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted)){

  HTable *newHash = malloc(sizeof(HTable));

  newHash->size = size;
  newHash->table = malloc(sizeof(Node)*size);
  newHash->destroyData = destroyData;
  newHash->hashFunction = hashFunction;
  newHash->printData = printData;

  return newHash;
}

Node *createNode(int key, void *data){

  Node *newNode = malloc(sizeof(Node));

  newNode->next = NULL;
  newNode->key = key;
  newNode->data = data;

  return newNode;
}

void destroyTable(HTable *hashTable){

  int i = 0;
  Node *temp = NULL;
  Node *tempDelete = NULL;

  if (hashTable != NULL)
  {
    for (i = 0 ; i < hashTable->size ; i++)
    {
      if (hashTable->table[i] != NULL)
      {
        temp = hashTable->table[i];
      }

      while (temp != NULL)
      {
        tempDelete = temp;
        temp = temp->next;
        free(tempDelete->data);
        free(tempDelete);
      }
    }
    free(hashTable->table);
    free(hashTable);
  }
}

void insertData(HTable *hashTable, int key, void *data){

  Node *insert = NULL;
  size_t index;
  Node *temp;

  if (hashTable != NULL)
  {
    insert = createNode(key, data);
    index = hashTable->hashFunction(hashTable->size, key);

    if (hashTable->table[index] != NULL) /*exists???????????????????????*/
    {
      //check the collision list first element, else check the rest */

      if (hashTable->table[index]->key == key)
      {
      /*  insert->next = hashTable->table[index]->next;*/
        hashTable->table[index] = insert;
      }
      else
      {
        /*find last position in collision list */
        temp = hashTable->table[index];
        while (temp->next != NULL)
        {
          temp = temp->next;
        }
        temp->next = insert;
      }
    }
    else /* does not exist yet */
    {
        hashTable->table[index] = insert;
    }
  }
}

void removeData(HTable *hashTable, int key){

  Node *temp;
  Node *prev;
  size_t index;

  if (hashTable != NULL)
  {
    index = hashTable->hashFunction(hashTable->size, key);

    if (hashTable->table[index] != NULL) /* exists??????????????????*/
    {
      temp = hashTable->table[index];
      prev = NULL;
      while (temp->key != key)
      {
        prev = temp;
        temp = temp->next;
      }

      if (temp->key == key)
      {
        if (prev == NULL)
        {
          /* remove head of list */
          hashTable->table[index] = temp->next;
          free(temp->data);
          free(temp);
          if (hashTable->table[index] == NULL) /* is now empty */
          {
            free(hashTable->table[index]);
          }
        }
        else
        {
          prev->next = temp->next;
          free(temp->data);
          free(temp);
        }
      }

    }
  }
}

void *lookupData(HTable *hashTable, int key){

  size_t index;
  Node *temp;

  if (hashTable != NULL)
  {
    index = hashTable->hashFunction(hashTable->size, key);

    if (!hashTable->table[index]) /*does not exist */
    {
      return NULL;
    }

    temp = hashTable->table[index];
    while (temp != NULL)
    {
      if (temp->key == key)
      {
        return temp->data;
      }
      temp = temp->next;
    }
  }

  return NULL;
}
