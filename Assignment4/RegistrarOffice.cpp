#include <iostream>
#include "RegistrarOffice.h"
#include "Student.h"
#include "Window.h"
#include "GenQueue.h"
#include "DoublyLinkedList.h"
#include <string>
#include <fstream>

using namespace std;

RegistrarOffice::RegistrarOffice()
{
  this->fileName = "test.txt";
  //testing that the file exists, if not exits program
  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }
  //run the simulation
  startSim();
}

RegistrarOffice::RegistrarOffice(string fileName)
{
  this->fileName = fileName;

  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }

  startSim();
}

RegistrarOffice::~RegistrarOffice()
{

}

void RegistrarOffice::startSim()
{
  ifstream readFile(fileName);
  //setting up an array of windows based on first line of the file
  int numOfWindows;
  readFile >> numOfWindows;
  Window myWindows[numOfWindows];

  int currTime; //currTime is keeping track of the time given by the file
  readFile >> currTime;

  int time = 0; //time will be the time in the simulation
  double totalWaitTime = 0; //of all the students
  double allWaitTimes[100]; //in an array for median
  double maxWaitTime = 0;
  int waitOverTenMins = 0;
  double totalIdleTime = 0; //of all windows
  double maxIdleTime = 0;
  int idleOverFiveMins = 0;
  int totalStudents = 0;
  int studentCount = 0;
  bool simStarted = false; //this bool checks if the first student has arrived.

  while(true)
  {
    if(time == currTime) //if the time in the sim matches the time given by the file, then enter this loop
    {
      simStarted = true;
      int numOfStudents = 0;
      readFile >> numOfStudents;
      totalStudents += numOfStudents;
      for(int i = 0; i < numOfStudents; ++i) //make a student for each num inputted by the file
      {
        double x;
        readFile >> x;
        Student me(x); //x is the student's mtgTime
        waitLine.insert(me); //insert the student into the waitLine
      }
      if(!readFile.eof()) //if not the end of the file, get the new current time
      {
        readFile >> currTime;
      }
    }

      for(int i = 0; i < numOfWindows; ++i) //go through each window
      {
        if(myWindows[i].isOccupied()) //if there's a student at the window
        {
          myWindows[i].clockTick(); //clock tick sets the mtg time of the student in the window to 1 less
          if(myWindows[i].getMeetingTime() == 0) //if the mtg ends, make the student leave and open the window
          {
            myWindows[i].leave(); //this checks if the meeting time has gotten to 0, if so, change occupied back to false. also sets idle time to 0
          }
        }
      }
      for(int i = 0; i < numOfWindows; ++i)
      {
        if(!myWindows[i].isOccupied()) //if the given window doesn't have a student at it
        {
          if(!waitLine.isEmpty()) //if the line is still not empty after previous iterations through. Ex: line is only 1 person long so goes to first window. Next window, the line would be empty, so stop
          {
            if(myWindows[i].getIdleTime() > 5)
            {
              ++idleOverFiveMins;
            }

            if(myWindows[i].getIdleTime() > maxIdleTime)
            {
              maxIdleTime = myWindows[i].getIdleTime();
            }

            double currentWaitTime = waitLine.peek().getWaitTime();
            allWaitTimes[studentCount] = currentWaitTime; //add the wait time of the student being added to the window to the array of allWaitTimes to calculate median
            studentCount++;
            totalWaitTime += currentWaitTime; //add the student at the front's wait time to the total wait time
            if(currentWaitTime > maxWaitTime)
            {
              maxWaitTime = currentWaitTime;
            }
            if(currentWaitTime > 10)
            {
              waitOverTenMins++;
            }
            myWindows[i].busy(waitLine.remove()); //remove the student at the front of the line and make the window busy with them
          }
        }

        if(!myWindows[i].isOccupied() && !simDone(myWindows, waitLine, numOfWindows)) //if the window is not occupied and the simulation isn't done
        {
          myWindows[i].incrementIdleTime();
          if(myWindows[i].getIdleTime() > maxIdleTime)
          {
            maxIdleTime = myWindows[i].getIdleTime();
          }
          totalIdleTime++;
        }
      }
    if(simDone(myWindows, waitLine, numOfWindows) && simStarted) //checks if myWindows are empty and that the line is empty
    {
      for(int i = 0; i < numOfWindows; ++i)
      {
        if(myWindows[i].getIdleTime() > 5)
        {
          idleOverFiveMins++;
        }
        if(myWindows[i].getIdleTime() > maxIdleTime)
        {
          maxIdleTime = myWindows[i].getIdleTime();
        }
      }
      break; //exit the main simulation loop
    }
    if(!simStarted) //if the no students have shwon up yet, all window wait times are bumpd up and included
    {
      for(int i = 0; i < numOfWindows; ++i)
      {
        myWindows[i].incrementIdleTime();
      }
      totalIdleTime += numOfWindows;
    }
    IncrementWaitTime(waitLine.getSize()); //this takes the queue of students, takes the students out, increments their wait times, and puts them back in, in their order
    ++time;
  }
//  cout << "num of students: " << studentCount << endl;
  cout << "Mean wait time for students: " << (double)totalWaitTime / totalStudents << endl;
  cout << "Median wait time for students: " << calcMedian(allWaitTimes, studentCount) << endl;
  cout << "Longest wait time for studnets: " << maxWaitTime << endl;
  cout << "Number of students that waited over 10 mins: " << waitOverTenMins << endl;
  //cout << "Total of all window's idle time: " << totalIdleTime << endl;
  cout << "Mean of all window's idle time: " << (double)totalIdleTime / numOfWindows << endl;
  if(idleOverFiveMins > numOfWindows)
  {
    idleOverFiveMins = numOfWindows;
  }
  cout << "Longest idle time of a window: " << maxIdleTime << endl;
  cout << "Number of windows idle over 5 minutes: " << idleOverFiveMins << endl;
}

bool RegistrarOffice::simDone(Window myWindows[], GenQueue<Student> waitLine, int size)
{
  for(int i = 0; i < size; ++i) //go through each window
  {
    if(myWindows[i].isOccupied()) //if the given window doesn't have a student at it
    {
      return false;
    }
  }

  if(!waitLine.isEmpty())
  {
    return false;
  }
  return true;
}

double RegistrarOffice::calcMedian(double allWaitTimes[], int studentCount) //source for bubblesort: https://www.geeksforgeeks.org/bubble-sort/
{
  //bubble sorting the array to find median
  int i, j;
  for (i = 0; i < studentCount-1; i++)
  {
      // Last i elements are already in place
      for (j = 0; j < studentCount-i-1; j++)
      {
          if (allWaitTimes[j] > allWaitTimes[j+1])
          {
            double temp = allWaitTimes[j];
            allWaitTimes[j] = allWaitTimes[j+1];
            allWaitTimes[j+1] = temp;
          }
      }
  }
  //bubble sort is done

  if(studentCount % 2 == 1) //if even list, just return middle number
  {
    return allWaitTimes[(studentCount/2)];
  }
  else //odd list, have to add the two middle numbers
  {
    return ((allWaitTimes[(studentCount-1)/2] + allWaitTimes[studentCount/2])/2);
  }
}

void RegistrarOffice::IncrementWaitTime(int numInQ)
{
  GenQueue<Student> *temp = new GenQueue<Student>();
  int counter = 0;
  while(!waitLine.isEmpty())
  {
    Student c(waitLine.peek().getMeetingTime());
    c.setWaitTime(waitLine.peek().getWaitTime());
    c.incrementWaitTime();
    temp->insert(c);
    waitLine.remove();
    ++counter;
  }
  while(counter != 0)
  {
    Student c(temp->peek().getMeetingTime());
    c.setWaitTime(temp->peek().getWaitTime());
    waitLine.insert(c);
    temp->remove();
    counter--;
  }
  delete temp;
}
