#include <iostream>

using namespace std;

class ListInterface
{
public:
  ListInterface();
  virtual ~ListInterface();
  virtual void insertFront() = 0;
  virtual void insertBack() = 0;
  virtual void removeFront() = 0;
  virtual void removeBack() = 0;

};
