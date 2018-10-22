#include <iostream>
#include "ListNode.h"
#include "DoublyLinkedList.h"
#include "GenQueue.h"
using namespace std;

int main(int argc, char* argv[])
{
  //ListNode h(5);
  DoublyLinkedList<int> list;
  list.insertFront(10);
  list.insertFront(2);
  list.insertBack(6);
  list.printList();
  cout << "removing shit" << endl;
  list.removeFront();
  list.removeBack();
  list.printList();
  list.remove(10);
  cout << "dead list" << endl;
  list.printList();
  list.insertFront(10);
  list.insertFront(2);
  list.insertBack(6);
  list.insertBack(7);
  list.deletePos(1);
  list.printList();
  cout << list.find(10) << endl;

  GenQueue<char> myQ(10);
  myQ.insert('d');
  cout << myQ.peek() << endl;
  return 0;
}
