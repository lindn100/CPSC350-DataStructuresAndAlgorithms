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
  data = this->displayInfo();
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
  data = this->displayInfo();
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
  data = s.displayInfo();
}

string Student::displayInfo()
{
  string t1 = to_string(getID());
  string t2 = to_string(getGPA());
  string t3 = to_string(getAdvisorID());

  //sstm <<  "ID: " << getID() << " Name: " << getName() << " Level: " << getLevel() << " Major: " << getMajor() << " GPA: " << getGPA() << " AdvisorID: " << getAdvisorID();
  return ("ID: " + t1 + " Name: " + getName() + " Level " + getLevel() + " Major: " + getMajor() + " GPA: " + t2 + " AdvisorID: " + t3);
}
