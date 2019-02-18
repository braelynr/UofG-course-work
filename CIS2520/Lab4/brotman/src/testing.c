/*
  testing.c
  Braelyn Rotman
  July 2018
  Lab 4
*/

#include "balancedTreeAPI.h"
#include "tree.h"
#include <stdio.h>

int main(void){

  Tree *newTree = NULL;
  TreeNode *newNode = NULL;
  int number = 60;
  void *data = (void *)(number);

  printf("\n****************Test File****************\n\n");

  printf("Create Tree:\n");
  printf("Tree variable before: %p\n", newTree);
  newTree = createBalancedBinTree(NULL, NULL, NULL);
  printf("Tree variable after: %p\n", newTree);
  if (newTree != NULL)
  {
    printf("Tree successfully created\n\n");
  }
  else
  {
    printf("ERROR: Tree not created\n\n");
  }

  printf("Create Tree Node:\n");
  printf("Node Variable Before: %p\n", newNode);
  newNode = createBalancedBinNode(data);
  printf("Node Variable After: %p\n", newNode);
  if (newNode != NULL)
  {
    printf("Tree Node successfully created\n\n");
  }
  else
  {
    printf("ERROR: Tree Node not created\n\n");
  }

  printf("Insert Node into Empty Tree:\n");
  printf("Data to insert: %d\n", number);
  printf("Tree Root Before (pointer): %p\n", newTree->root);
  treeInsertNode(newTree, data);
  printf("Tree Root After (pointer): %p\n", newTree->root);
  if (newTree->root != NULL)
  {
    printf("New tree root sucessfully inserted\n\n");
  }
  else
  {
    printf("ERROR: Tree root not inserted\n\n");
  }



  return 0;
}
