#ifndef BST_H
#define BST_H
#include "TreeNode.h"

#include <iostream>
using namespace std;

template<typename T>
class BST
{
public:
  BST();
  ~BST();

  void insert(TreeNode<T> *node);
  bool contains(int value);
  bool deleteNode(int value);
  bool isEmpty();

  void printTree();
  void recPrint(TreeNode<T> *node); //in order Traversal
  TreeNode<T>* getSuccessor(TreeNode<T> *d);
  void clearPointers(TreeNode<T> *d);
private:
  TreeNode<T> *root;
};

template<typename T>
BST<T>::BST()
{
  root = nullptr;
}

template<typename T>
BST<T>::~BST()
{
  while(root != nullptr)
  {
    deleteNode(root->key);
  }
  //iterate and delete each node
}

template<typename T>
void BST<T>::printTree()
{
  recPrint(root);
}

template<typename T>
bool BST<T>::isEmpty()
{
  return root == nullptr;
}

template<typename T>
void BST<T>::recPrint(TreeNode<T> *node) //inorder traversal
{
  if(node == nullptr)
  {
    return;
  }
  else
  {
    recPrint(node->left);
    cout << node->key << endl;
    recPrint(node->right);
  }
}

template<typename T>
void BST<T>::insert(TreeNode<T> *node)
{
  int value = node->key;
  //check for duplicates ifcontains(value) break
  if(isEmpty())
  {
    root = node;
  }
  else //not empty tree
  {
    TreeNode<T> *current = root;
    TreeNode<T> *parent;
    while(true) //begin search for insertion point
    {
      parent = current;
      if(value < current->key) //go left
      {
        current = current->left;
        if(current==nullptr)
        {
          parent->left = node;
          break;
        }
      }
      else
      {
        current = current->right;
        if(current == nullptr)
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

//basically a search method
template<typename T>
bool BST<T>::contains(int value)
{
  if(isEmpty())
  {
    return false;
  }
  else //not empty tree, continue to search
  {
    TreeNode<T> *current = root;

    while(current->key != value)
    {
      if(value < current->key)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
      if(current == nullptr)
      {
        return false;
      }
    }
    return true;
  }
}

template<typename T>
bool BST<T>::deleteNode(int k)
{
  if(!contains(k)) //contains checks that the tree is not empty
  {
    return false;
  }

  //proceed to find the node
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;

  while(current->key != k)
  {
    parent = current;
    if(k < current->left->key)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    /*without using contains
    if(current == NULL)
    {
    return false
    }
    */
  }

  //current is now the node we needed to find

  //no child

  if(current->left == nullptr && current->right == nullptr)
  {
    if(current == root)
    {
      root = nullptr;
    }
    else if(isLeft)
    {
      parent->left = nullptr;
    }
    else
    {
      parent->right = nullptr;
    }
  }

  //one child

  else if(current->right == nullptr) //right child is null, thus only child is left
  {
    if(current == root)
    {
      root = current->left;
      clearPointers(current);
      delete current;
    }
    else if(isLeft)
    {
      parent->left = current->left;
      clearPointers(current);
      delete current;
    }
    else //right child
    {
      parent->right = current->left;
      clearPointers(current);
      delete current;
    }
  }

  else if(current->left == nullptr)
  {
    if(current == root)
    {
      root = current->right;
      clearPointers(current);
      delete current;
    }
    else if(isLeft)
    {
      parent->left = current->right;
      clearPointers(current);
      delete current;
    }
    else //right child
    {
      parent->right = current->right;
      clearPointers(current);
      delete current;
    }
  }

  else //it has two children, gonna go one right then all the way left
  {
    TreeNode<T> *succ = getSuccessor(current);

    if(current == root)
    {
      root = succ;
    }
    else if(isLeft)
    {
      parent->left = succ;
    }
    else
    {
      parent->right = succ;
    }

    succ->left = current->left;
    clearPointers(current);
    delete current;
  }
  return true;
}

template<typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) //d is the node we r deleting
{
  TreeNode<T> *sp = d; //successor parent
  TreeNode<T> *succ = d;
  TreeNode<T> *current = d->right;

  while(current != nullptr)
  {
    sp = succ;
    succ = current;
    current = current->left;
  }

  if(succ != d->right) //descendant of right child, left most of right
  {
    sp->left = succ->right;
    succ->right = d->right;
  }

  return succ;
}

template<typename T>
void BST<T>::clearPointers(TreeNode<T> *d)
{
  d->left = nullptr;
  d->right = nullptr;
}

#endif
