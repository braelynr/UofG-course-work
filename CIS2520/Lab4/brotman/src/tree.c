#include "tree.h"
#include "balancedTreeAPI.h"

TreeNode * insert(TreeNode * treeRoot, void * data, int (*compareFP) (void *data1, void *data2)){

  TreeNode *newNode;

  if (treeRoot == NULL) /* empty "tree"*/
  {
    newNode = createBalancedBinNode(data);
    return newNode;
  }
  else
  {
    if (compareFP(data, treeRoot->data) == -1)
    {
      treeRoot->left = insert(treeRoot->left, data, compareFP); /* recursive call */
      /* rebalance after insertion*/
      if (treeRoot->left->height + 1 > treeRoot->right->height)
      {
        if (compareFP(data, treeRoot->left->data) == -1)
        {
          treeRoot = rotateWithLeftChild(treeRoot);
        }
        else
        {
          treeRoot = doubleRotateWithLeftChild(treeRoot);
        }
      }
    }
    else if (compareFP(data, treeRoot->data) == 1)
    {
      treeRoot->right = insert(treeRoot->right, data, compareFP); /* recursive call */
      /* rebalance after insertion*/
      if (treeRoot->right->height + 1 > treeRoot->left->height)
      {
        if (compareFP(data, treeRoot->right->data) == 1)
        {
          treeRoot = rotateWithRightChild(treeRoot);
        }
        else
        {
          treeRoot = doubleRotateWithRightChild(treeRoot);
        }
      }
    }
  }
  if (treeRoot->left == NULL && treeRoot->right == NULL)
  {

  }
  else if (treeRoot->left != NULL && treeRoot->right == NULL)
  {
    treeRoot->height = treeRoot->left->height + 1;
  }
  else if (treeRoot->left == NULL && treeRoot->right != NULL)
  {
    treeRoot->height = treeRoot->right->height + 1;
  }
  else if (treeRoot->left->height > treeRoot->right->height)
  {
    treeRoot->height = treeRoot->left->height + 1;
  }
  else if (treeRoot->left->height < treeRoot->right->height)
  {
    treeRoot->height = treeRoot->right->height + 1;
  }
  return treeRoot;
}

TreeNode * rotateWithLeftChild(TreeNode * oldRoot){
  TreeNode * temp = oldRoot->left;
	oldRoot->left = temp->right;
	temp->right = oldRoot;
  if (temp->left->height > temp->right->height)
  {
    temp->height = temp->left->height + 1;
  }
  else
  {
    temp->height = temp->right->height + 1;
  }
  if (oldRoot->left->height > oldRoot->right->height)
  {
    oldRoot->height = oldRoot->left->height + 1;
  }
  else
  {
    oldRoot->height = oldRoot->right->height + 1;
  }
	return temp;
}

TreeNode * rotateWithRightChild(TreeNode * oldRoot){
  TreeNode * temp = oldRoot->right;
  oldRoot->right = temp->left;
  temp->left = oldRoot;
  if (temp->right->height > temp->left->height)
  {
    temp->height = temp->right->height + 1;
  }
  else
  {
    temp->height = temp->left->height + 1;
  }

  if (oldRoot->right->height > oldRoot->left->height)
  {
    oldRoot->height = oldRoot->right->height + 1;
  }
  else
  {
    oldRoot->height = oldRoot->left->height + 1;
  }
  return temp;
}

TreeNode * doubleRotateWithRightChild(TreeNode * oldRoot){
  oldRoot->right = rotateWithLeftChild(oldRoot->right);
	oldRoot = rotateWithRightChild(oldRoot);

	return oldRoot;
}

TreeNode * doubleRotateWithLeftChild(TreeNode * oldRoot){
  oldRoot->left = rotateWithRightChild(oldRoot->left);
	oldRoot = rotateWithLeftChild(oldRoot);

	return oldRoot;
}
/*
TreeNode * delete(TreeNode * root, void * data, Tree * theTree){

  TreeNode *temp;
  void * removedData;

  if (root == NULL)
  {
    return NULL;
  }
  else if (theTree->compareFP(root->data, data) == 1)
  {
    root->left = delete(root, data, theTree);
  }
  else if (theTree->compareFP(root->data, data) == -1)
  {
    root->right = delete(root, data, theTree);
  }
  else
  {
    if (root->left != NULL && root->right != NULL)
    {
      temp = treeFindNode(theTree, treeFindMin(theTree));
      removedData = root->data;
      theTree->destroyFP(root->data);
      root->data = temp->data;
      root->right = delete(root->right, temp->data, theTree);
    }
    else
    {
      temp = root;
      if (root->left == NULL)
      {
        root = root->right;
      }
      else if (root->right == NULL)
      {
        root = root->left;
      }
    }
    theTree->destroyFP(temp->data);

    free(temp);
  }
}
*/
