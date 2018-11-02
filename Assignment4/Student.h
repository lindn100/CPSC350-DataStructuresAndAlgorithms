#ifndef Student_H
#define Student_H

class Student
{
public:
  Student();
  Student(int);
  ~Student();

  void setMeetingTime(int);
  int getMeetingTime();
  void incrementWaitTime();
  double getWaitTime();
  void setWaitTime(double);
private:
  int meetingTime;
  double waitTime;
};

#endif
