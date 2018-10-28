#include <iostream>
#include "Window.h"
#include "Student.h"

using namespace std;

Window::Window()
{
  occupied = false;
  idleTime = 0;
}

Window::Window(Student s)
{
  occupied = true;
  idleTime = 0;
  myStudent.setMeetingTime(s.getMeetingTime());
}

Window::~Window()
{

}

bool Window::isOccupied()
{
  return occupied;
}

void Window::busy(Student s)
{
  myStudent.setMeetingTime(s.getMeetingTime());
  setIdleTime(0);
  occupied = true;
}

void Window::leave()
{
  setIdleTime(0);
  occupied = false;
}

void Window::setIdleTime(double x)
{
  idleTime = x;
}

void Window::incrementIdleTime()
{
  ++idleTime;
}

double Window::getIdleTime()
{
  return idleTime;
}

void Window::clockTick()
{
  myStudent.setMeetingTime((myStudent.getMeetingTime())-1);
}

int Window::getMeetingTime()
{
  return myStudent.getMeetingTime();
}
