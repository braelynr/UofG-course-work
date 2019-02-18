/*
Lab 2
CIS 2520
Braelyn Rotman
June 18th, 2018
testing.c
*/

#include "HashTableAPI.h"

int hashFunction(size_t tableSize, int key);
void destroyData (void *data);
void printData (void *toBePrinted);


int main(void){
  HTable *hashTable;
  size_t size = 9;
  int i;
  int key;
  void *data = NULL;

  hashTable = createTable(size, &hashFunction, &destroyData, &printData);

  for (i = 0 ; i < 100 ; i = i + 4){
      key = i;
      insertData(hashTable, key, data);
  }

  data = lookupData(hashTable, 44);
  removeData(hashTable, 44);
  destroyTable(hashTable);

  return 0;
}

int hashFunction (size_t tableSize, int key){
  int hash = key;

  while (tableSize < hash)
  {
    hash = hash % 10;
  }

  return hash;
}

void destroyData (void *data){

}

void printData (void *toBePrinted){

}
