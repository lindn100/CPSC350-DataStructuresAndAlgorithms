#include <iostream>
#include "Student.h"

using namespace std;

Student::Student()
{
  meetingTime = 0;
  waitTime = 0;
}

Student::Student(int time)
{
  setMeetingTime(time);
  waitTime = 0;
}

Student::~Student()
{

}

void Student::setMeetingTime(int time)
{
  meetingTime = time;
}

int Student::getMeetingTime()
{
  return meetingTime;
}

void Student::incrementWaitTime()
{
  ++waitTime;
}

double Student::getWaitTime()
{
  return waitTime;
}

void Student::setWaitTime(double wait)
{
  waitTime = wait;
}
