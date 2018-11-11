#ifndef Person_H
#define Person_H
#include <string>

using namespace std;

class Person
{
public:
  Person();
  Person(int,string,string);
  ~Person();
  void setID(int);
  int getID() const;
  void setName(string);
  string getName();
  void setLevel(string);
  string getLevel();
  bool operator==(const Person&); //REF: https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr318.htm
  bool operator<(const Person&);
  bool operator>(const Person&);
private:
  int ID;
  string name;
  string level;
};

#endif
