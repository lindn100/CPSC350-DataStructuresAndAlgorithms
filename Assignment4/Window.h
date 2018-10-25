#ifndef Window_H
#define Window_H
#include "Student.h"
class Window
{
public:
  Window();
  ~Window(); //for window c : windowArray
             //if(!isOccupied)
             //occupy, setIdleTime to 0, decrease student meetingTime by 1 each loop
             //then loop through every window, if (!isOccupied), increment idleTime by 1
             //for max, check for each window if idleTime > maxIdleTime in sim class
  bool isOccupied(); //returns value of occupied
  void busy(); //set occupied to yes
  void leave(); //set occupied to no
  void setIdleTime(double);
  void incrementIdleTime();
  double getIdleTime();
private:
  bool occupied;
  double idleTime;
};

#endif
