#include <iostream>
#ifndef GenQueue_H
#define GenQueue_H
#include "DoublyLinkedList.h"
using namespace std;

template<typename T>
class GenQueue
{
public:
  GenQueue();
  ~GenQueue();
  void insert(T data);
  T remove();
  T peek();
  void printQueue();

  bool isEmpty();

private:
  int numElements;
  DoublyLinkedList<T> *myQueue;

};

template<typename T>
GenQueue<T>::GenQueue()
{
  numElements = 0;
  myQueue = new DoublyLinkedList<T>();
}

template<typename T>
GenQueue<T>::~GenQueue()
{
  delete myQueue;
}

template<typename T>
void GenQueue<T>::insert(T data)
{
  myQueue->insertBack(data);
  numElements++;
}

template<typename T>
T GenQueue<T>::remove()
{
  numElements--;
  return myQueue->removeFront();
}

template<typename T>
T GenQueue<T>::peek()
{
  return myQueue->getFront();
}

template<typename T>
bool GenQueue<T>::isEmpty()
{
  return (numElements == 0);
}

template<typename T>
void GenQueue<T>::printQueue()
{
  myQueue->printList();
}
#endif
