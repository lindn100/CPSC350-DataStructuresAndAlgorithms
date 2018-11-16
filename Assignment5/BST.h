#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template<typename T>
class BST
{
public:
  BST();
  ~BST();

  void insert(T node);
  bool contains(int value);
  bool deleteNode(int value);
  bool isEmpty();

  void printTree();
  void recPrint(T *node); //in order Traversal
  T* getSuccessor(T *d);
  void clearPointers(T *d);
private:
  T *root;
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
void BST<T>::recPrint(T *node) //inorder traversal
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
void BST<T>::insert(T node)
{
  int value = node.key;
  //check for duplicates ifcontains(value) break
  if(isEmpty())
  {
    root = &node;
  }
  else //not empty tree
  {
    T *current = root;
    T *parent;
    while(true) //begin search for insertion point
    {
      parent = current;
      if(value < current->key) //go left
      {
        current = current->left;
        if(current==nullptr)
        {
          parent->left = &node;
          break;
        }
      }
      else
      {
        current = current->right;
        if(current == nullptr)
        {
          parent->right =  &node;
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
    T *current = root;

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
  T *current = root;
  T *parent = root;
  bool isLeft = true;

  while(current->key != k)
  {
    parent = current;
    if(k < current->key)
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
    }
    else if(isLeft)
    {
      parent->left = current->left;
      clearPointers(current);
    }
    else //right child
    {
      parent->right = current->left;
      clearPointers(current);
    }
  }

  else if(current->left == nullptr)
  {
    if(current == root)
    {
      root = current->right;
      clearPointers(current); //current->left = nullptr, current->right = nullptr, "this finished?"
    }
    else if(isLeft)
    {
      parent->left = current->right;
      clearPointers(current);
    }
    else //right child
    {
      parent->right = current->right;
      clearPointers(current);
    }
  }

  else //it has two children, gonna go one right then all the way left
  {
    T *succ = getSuccessor(current);
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
  }
  return true;
}

template<typename T>
T* BST<T>::getSuccessor(T *d) //d is the node we r deleting
{
  T *sp = d; //successor parent
  T *succ = d;
  T *current = d->right;

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
void BST<T>::clearPointers(T *d)
{
  d->left = nullptr;
  d->right = nullptr;
}

#endif
