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
  
private:
  int ID;
  string name;
  string level;
};

#endif
