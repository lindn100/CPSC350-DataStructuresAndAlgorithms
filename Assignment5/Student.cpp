#include "Student.h"
#include <string>
#include <iostream>
#include <string>

using namespace std;

Student::Student()
{
  setID(0);
  setName("default");
  setLevel("default");
  setMajor("default");
  setGPA(0);
  setAdvisorID(0);
  key = getID();
  left = nullptr;
  right = nullptr;
}

Student::Student(int ID, string name, string level, string major, double GPA, int advisorID)
{
  setID(ID);
  setName(name);
  setLevel(level);
  setMajor(major);
  setGPA(GPA);
  setAdvisorID(advisorID);
  key = getID();
  left = nullptr;
  right = nullptr;
}

Student::~Student()
{

}

void Student::setMajor(string major)
{
  this->major = major;
}

string Student::getMajor()
{
  return major;
}

void Student::setGPA(double GPA)
{
  this->GPA = GPA;
}

double Student::getGPA()
{
  return GPA;
}

void Student::setAdvisorID(int advisorID)
{
  this->advisorID = advisorID;
}

int Student::getAdvisorID()
{
  return advisorID;
}

void Student::operator=(Student& s)
{
  setID(s.getID());
  setName(s.getName());
  setLevel(s.getLevel());
  setMajor(s.getMajor());
  setGPA(s.getGPA());
  setAdvisorID(s.getAdvisorID());
  key = s.key;
  left = s.left;
  right = s.right;
}

void Student::displayInfo() //couting in one line gives me a bunch of errors, so doing this way for now
{
  cout << "ID: ";
  cout << getID();
  cout << " Name: ";
  cout << getName();
  cout << " Level: ";
  cout << getLevel();
  cout << " Major: ";
  cout << getMajor();
  cout << " GPA: ";
  cout << getGPA();
  cout << " AdvisorID: ";
  cout << getAdvisorID() << endl;
}
