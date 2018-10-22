#ifndef ListNode_H
#define ListNode_H

template<typename T>
class ListNode
{
public:
  ListNode();
  ListNode(T d);
  ~ListNode();

  T data;
  ListNode<T> *next;
  ListNode<T>  *previous;

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
  next = nullptr; //maybe nullptr?
  previous = nullptr;
}

template<typename T>
ListNode<T>::~ListNode()
{
    //research this, I think it's delete next;
}

#endif
