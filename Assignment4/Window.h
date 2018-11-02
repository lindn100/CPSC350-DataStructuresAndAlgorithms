#ifndef Window_H
#define Window_H
#include "Student.h"
class Window
{
public:
  Window();
  Window(Student);
  ~Window(); 
  bool isOccupied(); //returns value of occupied
  void busy(Student); //set occupied to yes
  void leave(); //set occupied to no
  void clockTick();
  void setIdleTime(double);
  void incrementIdleTime();
  double getIdleTime();
  int getMeetingTime();
private:
  Student myStudent;
  bool occupied;
  double idleTime;
};

#endif
