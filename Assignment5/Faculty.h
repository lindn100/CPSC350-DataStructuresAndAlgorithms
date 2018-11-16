#ifndef Faculty_H
#define Faculty_H
#include <string>
#include "Person.h"
#include "Student.h"
#include "NaiveList.h"

using namespace std;

class Faculty : public Person
{
public:
  Faculty();
  Faculty(int, string, string, string);
  ~Faculty();
  void setDepartment(string);
  string getDepartment();
  void printAdvisees();
  void addAdvisee(int);
  int removeAdvisee(int);
  int getAdviseeSize();
  bool containsAdvisee(int);
private:
  NaiveList<int> adviseeID;
  string department;
  //singlelinkedlist<int> *myList

};

#endif
