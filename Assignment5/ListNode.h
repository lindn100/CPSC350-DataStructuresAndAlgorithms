#ifndef ListNode_H
#define ListNode_H
#include <iostream>

using namespace std;

template<typename T>
class ListNode
{
public:
  ListNode();
  ListNode(T d);
  ~ListNode();

  T data;
  ListNode *next;

};

template<typename T>
ListNode<T>::ListNode()
{
  //do this
}

template<typename T>
ListNode<T>::ListNode(T d)
{
  data = d;
  next = nullptr;
}

template<typename T>
ListNode<T>::~ListNode()
{

}

#endif
