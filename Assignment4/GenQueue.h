#include <iostream>
#ifndef GenQueue_H
#define GenQueue_H
using namespace std;

template<typename T>
class GenQueue
{
public:
  GenQueue();
  GenQueue(int);
  ~GenQueue();
  void insert(T data);
  T remove();
  T peek();

  bool isFull();
  bool isEmpty();
  int getSize();

private:
  int front;
  int rear;
  int numElements;
  int size;
  T *myQueue;

};

template<typename T>
GenQueue<T>::GenQueue()
{
  //stuff
}

template<typename T>
GenQueue<T>::GenQueue(int maxSize)
{
  myQueue = new T[maxSize];
  size = maxSize;
  front = 0;
  rear = -1;
  numElements = 0;
}

template<typename T>
GenQueue<T>::~GenQueue()
{
  delete [] myQueue;
}

template<typename T>
void GenQueue<T>::insert(T data)
{
  //check if full
  if(!isFull() && rear == (size-1))
  {
    rear = -1;
  }
  myQueue[++rear] = data;
  numElements++;
}

template<typename T>
T GenQueue<T>::remove()
{
  T c;
  c = myQueue[front];
  front++;
  numElements--;
  return c;
}

template<typename T>
T GenQueue<T>::peek()
{
  return myQueue[front];
}

template<typename T>
bool GenQueue<T>::isEmpty()
{
  return (numElements == 0);
}

template<typename T>
bool GenQueue<T>::isFull()
{
  return numElements == size;
}

template<typename T>
int GenQueue<T>::getSize()
{
  return size;
}
#endif
