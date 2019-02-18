#include "balancedTreeAPI.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted), void *(*copyFP)(void *toBeCopy)){
  Tree *newTree = malloc(sizeof(Tree));
  newTree->root = NULL;
  newTree->compareFP = compareFP;
  newTree->destroyFP = destroyFP;
  newTree->copyFP = copyFP;

  return newTree;
}

TreeNode *createBalancedBinNode(void *data){
  TreeNode *newNode = malloc(sizeof(TreeNode));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 0;
  newNode->data = data;

  return newNode;
}

void destroyBalancedBinTree(Tree *toBeDeleted){

}

void treeInsertNode(Tree *theTree, void *toBeInserted){

  TreeNode *current;
  TreeNode *newNode;
  current = insert(theTree->root, toBeInserted, theTree->compareFP);
  theTree->root = current;
}

void treeDeleteNode(Tree *theTree, void *toBeDeleted){

}

int treeIsEmpty(Tree *theTree){
  if (theTree->root == NULL)
  {
    return 1;
  }

  return 0;
}

int treeHasTwoChildren(TreeNode *root){
  if (root == NULL || root->left == NULL || root->right == NULL)
  {
    return 1;
  }

  return 0;
}

void *treeFindNode(Tree *theTree, void *data){
  TreeNode * current = theTree->root;
  while (current != NULL)
  {
    if (theTree->compareFP(current->data, data) == 1)
    {
      current = current->right;
    }
    else if (theTree->compareFP(current->data, data) == -1)
    {
      current = current->left;
    }
    else /* data is equal */
    {
      return current->data;
    }
  }
  return NULL;
}

void *treeFindMin(Tree *theTree){
  TreeNode *min = theTree->root;
  if (min == NULL)
  {
    return NULL;
  }
  while (min->left != NULL)
  {
    min = min->left;
  }
  return min;
}

void *treeFindMax(Tree *theTree){
  TreeNode *max = theTree->root;
  if (max == NULL)
  {
    return NULL;
  }
  while (max->right != NULL)
  {
    max = max->right;
  }
  return max;

}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data)){

}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data)){

}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data)){

}
