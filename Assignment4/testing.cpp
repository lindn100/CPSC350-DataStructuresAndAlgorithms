#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include "ListNode.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
using namespace std;

int main(int argc, char* argv[])
{
  int x = 5;
  Window myArr[5];
  Student me(10);
  for(int i = 0; i < x; ++i)
  {
    if(!myArr[i].isOccupied())
    {
      myArr[i].busy(me);
    }
  }
  myArr[0].clockTick();
  cout << myArr[0].getMeetingTime() << endl;
/*  GenQueue<Student> myQ;
  Student me(10);

  myQ.insert(me);
  Window lol;
  lol.busy(me);
  lol.clockTick();
  cout << lol.getMeetingTime() << endl;
  myQ.insert('o');
  myQ.insert('g');

  myQ.printQueue();

  myQ.remove();
  myQ.printQueue();*/
  return 0;
}
