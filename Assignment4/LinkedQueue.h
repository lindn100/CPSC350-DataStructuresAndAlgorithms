#ifndef LinkedQueue_H
#define LinkedQueue_H
#include "DoublyLinkedList.h"
#include "GenQueue.h"
#include <iostream>
using namespace std;

template<typename T>
class LinkedQueue : public GenQueue{
public:
  LinkedQueue();
  ~LinkedQueue();

  void insert(T data);
  T remove();
  T peek();

private:
  DoublyLinkedList<T> *myList;
};

template<typename T>
LinkedQueue<T>::LinkedQueue()
{

}

template<typename T>
LinkedQueue<T>::~LinkedQueue()
{
  //DoublyLinkedList deconstructor removes all the nodes
}

template<typename T>
void LinkedQueue<T>::insert(T data)
{
  myList.insertBack(data);
}

template<typename T>
T LinkedQueue<T>::remove();
{
  try{
    return myList.removeFront();
  }
  catch(runtime_error e)
  {
    cout << "Removing from an empty list. Exiting application." << endl;
    exit(0);
  }
}

template<typename T>
T LinkedQueue<T>::peek()
{
  return myList->front;
}



#endif
