#ifndef DB_H
#define DB_H
#include <iostream>
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "NaiveList.h"
using namespace std;

class DB
{
public:
  DB();
  ~DB();
  void startProgram();
  void addStudent();
  void addFaculty();

private:
  BST<Student> masterStudent;
  BST<Faculty> masterFaculty;
  Student *tempStudent;
  Faculty *tempFaculty;
  NaiveList<int> studentIDs;
  NaiveList<int> facultyIDs;
  int numberOfStudents;
  int numberOfFaculty;
};
#endif
