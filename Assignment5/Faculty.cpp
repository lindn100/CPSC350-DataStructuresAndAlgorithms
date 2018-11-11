#include "Faculty.h"
#include <iostream>

using namespace std;

Faculty::Faculty()
{

}

Faculty::Faculty(int ID, string name, string level, string department)
{
  setID(ID);
  setName(name);
  setLevel(level);
  setDepartment(department);
}

Faculty::~Faculty()
{

}

void Faculty::setDepartment(string department)
{
  this->department = department;
}

string Faculty::getDepartment()
{
  return department;
}
