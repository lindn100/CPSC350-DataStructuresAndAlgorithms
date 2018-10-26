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
  occupied = true;
}

void Window::leave()
{
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
