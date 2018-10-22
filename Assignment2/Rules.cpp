#include <iostream>
#include "Rules.h"

using namespace std;

Rules::Rules() //constructor, overloaded constructor, and destructor
{
  setFileMode('R');
  setBoundaryMode('C');
  setDisplayStyle('P');
}

Rules::Rules(char x, char y, char z)
{
  setFileMode(x);
  setBoundaryMode(y);
  setDisplayStyle(z);
}

Rules::~Rules()
{

}

//getter and setter methods

char Rules::getFileMode()
{
  return this->fileMode;
}

char Rules::getBoundaryMode()
{
  return this->boundaryMode;
}

char Rules::getDisplayStyle()
{
  return this->displayStyle;
}

void Rules::setFileMode(char c) //checks that the input is correct, else ends the program
{
  if(c == 'R' || c == 'F')
  {
    this->fileMode = c;
  }
  else
  {
    cout << "Invalid file mode. Exiting program." << endl;
    exit(0);
  }
}

void Rules::setBoundaryMode(char c)
{
  if(c == 'C' || c == 'D' || c == 'M')
  {
    this->boundaryMode = c;
  }
  else
  {
    cout << "Invalid boundary mode. Exiting program." << endl;
    exit(0);
  }
}

void Rules::setDisplayStyle(char c)
{
  if(c == 'P' || c == 'E' || c == 'F')
  {
    this->displayStyle = c;
  }
  else
  {
    cout << "Invalid display style. Exiting program." << endl;
    exit(0);
  }
}
