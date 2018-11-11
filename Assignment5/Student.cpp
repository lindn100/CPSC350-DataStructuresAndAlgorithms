#include "Student.h"
#include <string>
#include <iostream>

using namespace std;

Student::Student()
{
  setID(0);
  setName("default");
  setLevel("default");
  setMajor("default");
  setGPA(0);
  setAdvisorID(0);
}

Student::Student(int ID, string name, string level, string major, double GPA, int advisorID)
{
  setID(ID);
  setName(name);
  setLevel(level);
  setMajor(major);
  setGPA(GPA);
  setAdvisorID(advisorID);
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

bool Student::operator==(const Student& s)
{
  return getID() == s.getID();
}

bool Student::operator<(const Student& s)
{
  return getID() < s.getID();
}

bool Student::operator>(const Student& s)
{
  return getID() > s.getID();
}
