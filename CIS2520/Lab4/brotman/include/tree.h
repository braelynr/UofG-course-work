/**
 * @file tree.h
 * @date July 2018
 * @brief File containing the structures for a self-balancing binary tree and additional functions.
 */

#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS.
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;

#include "balancedTreeAPI.h"


/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.

    //Add additional structure elements here
    int height;
};

//add function prototypes as necessary

/**Function to insert data into the tree
 *@param treeRoot pointer to tree or subtree root
 *@param data pointer to void data type
 *@param compareFP pointer to compare function
 *@return pointer to inserted node
 **/
TreeNode * insert(TreeNode * treeRoot, void * data, int (*compareFP) (void *data1, void *data2));

/**Function to rotate with left child
 *@param oldroot pointer to original subtree root
 *@return pointer to child
 **/
TreeNode * rotateWithLeftChild(TreeNode * oldRoot);

/**Function to rotate with right child
 *@param oldroot pointer to original subtree root
 *@return pointer to child
 **/
TreeNode * rotateWithRightChild(TreeNode * oldRoot);

/**Function to complete double rotatatoion with right child
 *@param oldroot pointer to original subtree root
 *@return pointer to child
 **/
TreeNode * doubleRotateWithRightChild(TreeNode * oldRoot);

/**Function to complete double rotatatoion with left child
 *@param oldroot pointer to original subtree root
 *@return pointer to child
 **/
TreeNode * doubleRotateWithLeftChild(TreeNode * oldRoot);

/**Function to delete a node
 *@param root pointer to root of subtree
 *@param data data that should be deleted
 *@param theTree pointer to entire tree
 **/
TreeNode * delete(TreeNode * root, void * data, Tree *theTree);

#endif
