#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

Person::Person()
{
  setID(0);
  setName("default");
  setLevel("default");
}

Person::Person(int ID, string name, string level)
{
  setID(ID);
  setName(name);
  setLevel(level);
}

Person::~Person()
{

}

void Person::setID(int ID)
{
  this->ID = ID;
}

int Person::getID() const //adding const here to resolve compiler errors: REFERENCE: https://stackoverflow.com/questions/5973427/error-passing-xxx-as-this-argument-of-xxx-discards-qualifiers
{
  return this->ID;
}

void Person::setName(string name)
{
  this->name = name;
}

string Person::getName()
{
  return this->name;
}

void Person::setLevel(string level)
{
  this->level = level;
}

string Person::getLevel()
{
  return this->level;
}
