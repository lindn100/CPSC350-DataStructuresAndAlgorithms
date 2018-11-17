#ifndef Student_H
#define Student_H
#include <string>
#include "Person.h"

using namespace std;

class Student : public Person
{
public:
  Student();
  Student(int, string, string, string, double, int);
  ~Student();
  void setMajor(string);
  string getMajor();
  void setGPA(double);
  double getGPA();
  void setAdvisorID(int);
  int getAdvisorID();

  int key;
  string data;
  Student *left;
  Student *right;
  void operator=(Student&);
  void displayInfo();


private:
  string major;
  double GPA;
  int advisorID;

};

#endif
