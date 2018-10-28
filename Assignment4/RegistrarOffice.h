#ifndef RegistrarOffice_H
#define RegistrarOffice_H
#include <string>
#include <iostream>
#include "Window.h"
#include "Student.h"
#include "GenQueue.h"

class RegistrarOffice
{
public:
  RegistrarOffice();
  RegistrarOffice(std::string);
  ~RegistrarOffice();

  void startSim();
  bool simDone(Window myWindows[], GenQueue<Student> waitLine, int size);
  double calcMedian(double allWaitTimes[], int numOfStudents);
  void IncrementWaitTime(int numInQ);

private:
  std::string fileName;
  GenQueue<Student> waitLine;

};

#endif
