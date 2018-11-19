#ifndef DB_H
#define DB_H
#include <iostream>
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
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
  //HAVE TO MAKE THESE ARRAYS INTO LINKED LISTS TO FUNCTION CORRECLTY.
  bool takenStudentID[9000];
  bool takenFacultyID[9000];
  int facultyID[9000];
  int studentID[9000];
  int numberOfStudents;
  int numberOfFaculty;
};
#endif
