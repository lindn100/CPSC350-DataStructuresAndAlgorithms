#ifndef Faculty_H
#define Faculty_H
#include <string>
#include "Person.h"

using namespace std;

class Faculty : public Person
{
public:
  Faculty();
  Faculty(int, string, string, string);
  ~Faculty();
  void setDepartment(string);
  string getDepartment();
private:
  string department;
  //singlelinkedlist<int> *myList

};

#endif
