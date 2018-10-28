#ifndef Student_H
#define Student_H

class Student
{
public:
  Student();
  Student(int); //set meetingTime
  ~Student(); //time varible in sim class, if readLineTime or something == time, then read in next # of students, do a for(int i = 0; i < # of students, ++i)
              //then Student newStudent(nextLine.readLine() or something);
              //myQ.insert(newStudent);
              //mean can be done with a sum of total wait time / total time. This means when a student is added to a window, add their waitTime to totalWaitTime;
              //median can be done by adding all wait times to an array, then chopping off each end slowly. This means we are gonna need to sort the array.
              //maxWaitTime can be done with just an int check, ez
              //sim class needs a int waitOverTenMins var.
              //mean window just needs a total in sim
              //maxIdleTime for window
              //idleOverFiveMins var

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
