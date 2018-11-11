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
  bool operator==(const Student&); //REF: https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr318.htm
  bool operator<(const Student&);
  bool operator>(const Student&);
private:
  string major;
  double GPA;
  int advisorID;

};

#endif
