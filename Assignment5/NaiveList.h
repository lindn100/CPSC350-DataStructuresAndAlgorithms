#ifndef NaiveList_H
#define NaiveList_H
#include "ListNode.h"
#include <iostream>

using namespace std;

template<typename T>
class NaiveList
{
private:
  ListNode<T> *front;
  unsigned int size;
public:
  NaiveList();
  ~NaiveList();

  void insertFront(T d);
  T removeFront();
  T deletePos(int pos);
  int find(T value);
  bool contains(T value);
  T removeID(T value);

  void printList();
  unsigned int getSize();
};

template<typename T>
NaiveList<T>::NaiveList()
{
  front = NULL;
  size = 0;
}

template<typename T>
NaiveList<T>::~NaiveList()
{
  while(front != nullptr)
  {
    ListNode<T> *node = front;
    front = front->next;
    delete node;
  }
}

template<typename T>
void NaiveList<T>::insertFront(T d)
{
  ++size;
  ListNode<T> *node = new ListNode<T>(d);
  node->next = front;
  front = node;
}

template<typename T>
T NaiveList<T>::removeFront()
{
  --size;
  T temp = front->data;
  ListNode<T> *node = front;
  front = front->next;
  node->next = NULL;
  delete node;
  return temp;
}

template<typename T>
T NaiveList<T>::deletePos(int pos)
{
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(idx != pos) //responsible for putting pointers in responsible positions
  {
    prev = curr;
    curr = curr->next;
    ++idx;
  }

  //found the position, lets proceed to delete

  prev->next = curr->next;
  curr->next = NULL;
  T d = curr->data;
  size--;
  delete curr;

  return d;
}

template<typename T>
int NaiveList<T>::find(T value)
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
bool NaiveList<T>::contains(T value)
{
  int x = find(value);
  if(x == (-1))
    {
      return false;
    }
  return true;
}

template<typename T>
T NaiveList<T>::removeID(T value)
{
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;

    while(curr != nullptr) //responsible for putting pointers in responsible positions
    {
      if(value == curr->data)
      {
        break;
      }
      prev = curr;
      curr = curr->next;
    }

    if(curr == nullptr)
    {
      //ID not found in list
      return -1; //returning -1 if not found
    }

    //found the position, lets proceed to delete

    prev->next = curr->next;
    curr->next = NULL;
    T d = curr->data;
    size--;
    delete curr;

    return d;
}

template<typename T>
void NaiveList<T>::printList()
{
  ListNode<T> *curr = front;
  while(curr != nullptr)
  {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template<typename T>
unsigned int NaiveList<T>::getSize()
{
  return size;
}
#endif
