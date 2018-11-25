#include "Faculty.h"
#include <iostream>

using namespace std;

Faculty::Faculty()
{
  setID(0);
  setName("default");
  setLevel("default");
  setDepartment("default");
  left = nullptr;
  right = nullptr;
  key = getID();
}

Faculty::Faculty(int ID, string name, string level, string department)
{
  setID(ID);
  setName(name);
  setLevel(level);
  setDepartment(department);
  key = getID();
  left = nullptr;
  right = nullptr;
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

void Faculty::printAdvisees()
{
  adviseeID.printList();
}

void Faculty::addAdvisee(int ID)
{
  adviseeID.insertFront(ID);
}

int Faculty::removeAdvisee(int ID)
{
  return adviseeID.removeID(ID);
}

int Faculty::removeAdviseeFront()
{
  return adviseeID.removeFront();
}

int Faculty::getAdviseeSize()
{
  return adviseeID.getSize();
}

bool Faculty::containsAdvisee(int ID)
{
  return adviseeID.contains(ID);
}

int Faculty::sizeOfAdvisees()
{
  return adviseeID.getSize();
}

void Faculty::operator=(Faculty& s)
{
  setID(s.getID());
  setName(s.getName());
  setLevel(s.getLevel());
  setDepartment(s.getDepartment());
  /*while(s.sizeOfAdvisees() > 0)
  {
    s.removeAdvisee()
  }
  setAdvisorID(s.getAdvisorID());*/
  key = s.key;
  left = s.left;
  right = s.right;
}

void Faculty::displayInfo() //couting in one line gives me a bunch of errors, so doing this way for now
{
  cout << "ID: ";
  cout << getID();
  cout << " Name: ";
  cout << getName();
  cout << " Level: ";
  cout << getLevel();
  cout << " Department: ";
  cout << getDepartment();
  cout << " List of Advisees: ";
  adviseeID.printList();
  cout << endl;
}

int Faculty::printAdviseeID(int pos)
{
  return adviseeID.nodeAtPos(pos);
}
