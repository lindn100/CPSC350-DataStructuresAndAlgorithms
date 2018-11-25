#ifndef GenStack_H
#define GenStack_H

#include <iostream>

using namespace std;

template<typename T>
class GenStack
{
public:
  GenStack(); //default constructor
  GenStack(int maxSize); //overload constructor
  ~GenStack();

  void push(T d);
  T pop();
  T peek();

  bool isFull();
  bool isEmpty();

private:

  int size;
  int top;

  T *myArray;

};

template<typename T>
GenStack<T>::GenStack()
{
  this->myArray = new T[10]; //new allocates to the heap
  this->size = 10;
  this->top = -1;
  //intialize variable to default values
}

template<typename T>
GenStack<T>::GenStack(int maxSize)
{
  this->myArray = new T[maxSize]; //new allocates to the heap
  this->size = maxSize;
  this->top = -1;
}

template<typename T>
GenStack<T>::~GenStack()
{
  delete [] this->myArray;
}

template<typename T>
void GenStack<T>::push(T d)
{
  if(!isFull()) //if stack is not full, add d to the top
  {
    this->myArray[++top] = d;
  }
  else
  {
    //cout << "Error occurred. Pushing to a full stack. Creating stack twice as big" << endl;
    for(int i = 1; i < size; ++i) //this shifts all elements 1 over, and adds element to the front
    {
      myArray[i-1] = myArray[i];
    }
  myArray[size-1] = d;
  }
}

template<typename T>
T GenStack<T>::pop()
{
  if(!isEmpty())
  {
    return myArray[top--];
  }
  else
  {
    throw runtime_error("Error! Popping an empty list.");
    //REF FOR ABOVE: https://stackoverflow.com/questions/26171631/throwing-a-run-time-error
  }
}

template<typename T>
T GenStack<T>::peek()
{
  if(!isEmpty())
  {
    return myArray[top];
  }
  else
  {
    throw runtime_error("Error! Peeking an empty list.");
  }
}

template<typename T>
bool GenStack<T>::isFull()
{
  return (top == (size-1));
}

template<typename T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}

#endif
