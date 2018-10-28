#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H
#include "ListNode.h"
#include <iostream>
using namespace std;

template<typename T>
class DoublyLinkedList
{
private:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;
public:
  DoublyLinkedList();
  ~DoublyLinkedList();

  void insertFront(T d);
  void insertBack(T d);
  T removeFront();
  T removeBack();
  ListNode<T> *remove(T key);
  T deletePos(int pos);
  int find(T value);
  T getFront();
//  T findPos(int pos);

  void printList();
  unsigned int getSize();
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  front = nullptr;
  back = nullptr;
  size = 0;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  while(front != nullptr)
  {
    ListNode<T> *del = front;
    front = front->next;
    delete del;
  }
}

template<typename T>
void DoublyLinkedList<T>::insertFront(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0) { //empty list
    front = node;
    back = node;
  }
  else
  {
    front->previous = node;
    node->next = front;
    front = node;
  }
  ++size;
}

template<typename T>
void DoublyLinkedList<T>::insertBack(T d)
{
  ListNode<T> *node = new ListNode<T>(d);
  if (size == 0) //empty list
  {
    front = node;
    back = node;
  }
  else // not empty
  {
    back->next = node;
    node->previous = back;
    back = node;
  }
  ++size;
}

template<typename T>
T DoublyLinkedList<T>::removeFront()
{
  ListNode<T> *node = front;
  //check if empty
  if(getSize() == 0)
  {
    throw runtime_error("invalid remove"); //throw error if removing from empty list
  }
  if(getSize() == 1)
  {
    T data = node->data;
    delete node;
    --size;
    return data;
  }
/*  if(front == nullptr) //only node in list
  {
    back = nullptr;
  }*/
  else //more than 1 node in list
  {
    front->next->previous = nullptr;
  }
  front = front->next;
  node->next = nullptr;
  T data = node->data;
  delete node;
  --size;
  return data;
}

template<typename T>
T DoublyLinkedList<T>::removeBack()
{
  --size;
  ListNode<T> *node = back;
  if(back == nullptr)
  {
    front = nullptr;
  }
  else
  {
    back->previous->next = nullptr;
  }
  back = back->previous;
  node->previous = nullptr;
  T data = node->data;
  delete node;
  return data;
}

template<typename T>
ListNode<T>* DoublyLinkedList<T>::remove(T key)
{
  if(size > 0)
  {
    ListNode<T> *current = front;
    while(current->data != key)
    {
      current = current->next;
      if(current == nullptr)
      {
        return nullptr;
      }
    }
    //we found it
    if(current == front) //if the front node, need to set front to the next one before we remove it
    {
      front = current->next;
    }
    else
    {
      current->previous->next = current->next;
    }

    if(current == back) //if back node, set back the previous node
    {
      back = current->previous;
    }
    else
    {
      current->next->previous = current->previous;
    }

    current->next = nullptr;
    current->previous = nullptr;
    size--;
    return current;
  }
  else
  {
    cout << "removing an empty list. exiting program." << endl;
    exit(0);
  }
}

template<typename T>
T DoublyLinkedList<T>::deletePos(int pos)
{
  int idx = 0;
  ListNode<T> *curr = front;
  if(pos == 0) //if deleting at first position, do not moddify previous, set front to next node
  {
    T d = front->data;
    front = curr->next;
    front->previous = nullptr;
    curr->next = nullptr;
    size--;
    delete curr;
    return d;
  }

  ListNode<T> *prev = front;

  while(idx != pos) //responsible for putting pointers in responsible positions
  {
    prev = curr;
    curr = curr->next;
    if(curr == nullptr)
    {
      cout << "OUT OF BOUNDS" << endl;
      return -1;
    }
    ++idx;
  }

  if(curr->next == nullptr)
  {
    back = prev;
  }
  //found the position, lets proceed to delete
  prev->next = curr->next;
  if(curr->next == nullptr)
  {
    back = prev;
  }
  else
  {
    curr->next->previous = prev;
  }
  curr->next = nullptr;
  curr->previous = nullptr;
  T d = curr->data;
  size--;
  delete curr;

  return d;
}

template<typename T>
int DoublyLinkedList<T>::find(T value)
{
  int idx = -1;
  ListNode<T> *curr = front;
  while(curr != nullptr) //being searching for value
  {
    ++idx;
    if(curr->data == value)
    {
      break;
    }
    else
    {
      curr = curr->next;
    }
  }
  if(curr == nullptr)
  {
    idx = -1;
  }
  return idx;
}

template<typename T>
void DoublyLinkedList<T>::printList()
{
  ListNode<T> *curr = front;
  while(curr != nullptr)
  {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template<typename T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}


template<typename T>
T DoublyLinkedList<T>::getFront()
{
  return front->data;
}

/*template<typename T>
T DoublyLinkedList<T>::findPos(int pos)
{
  int temp = 0;
  ListNode<T> *curr = front;
  while(temp != pos)
  {
    curr = curr->next;
    temp++;
  }
  return curr;
}*/

#endif
