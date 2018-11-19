#include "DB.h"
#include <iostream>
#include <ctime> //using this for srand, REF: https://stackoverflow.com/questions/7748071/same-randome-numbers-every-time-i-run-the-program

using namespace std;

DB::DB()
{
  numberOfFaculty = 0;
  numberOfStudents = 0;
  for(int i = 0; i < 9000; ++i)
  {
    takenStudentID[i] = false;
    takenFacultyID[i] = false;
    facultyID[i] = 0;
    stuentID[i] = 0;
  }
  startProgram();
}

DB::~DB()
{

}

void DB::startProgram()
{
  bool exit = false;

  //read in file stuff to add to trees

while(!exit){
  cout << "Please select an action from the below menu by typing in it's corresponding number." << endl;
  cout << "1. Print all students and their information (sorted by ascending id #)." << endl;
  cout << "2. Print all faculty and their information (sorted by ascending id#)." << endl;
  cout << "3. Find and display student information given the student's ID." << endl;
  cout << "4. Find and display faculty information given the faculty's ID." << endl;
  cout << "5. Given a student's ID, print the name and infor of their faculty advisor" << endl;
  cout << "6. Given a faculty's ID, print ALL the names and info of his/her advisees." << endl;
  cout << "7. Add a new student." << endl;
  cout << "8. Delete a student given the ID." << endl;
  cout << "9. Add a new faculty member." << endl;
  cout << "10. Delete a faculty member given the ID." << endl;
  cout << "11. Change a student's advisor given the student ID and the new faculty ID." << endl;
  cout << "12. Remove an advisee from a faculty member given the ID of oth the student and faculty." << endl;
  cout << "13. Rollback" << endl;
  cout << "14. Exit" << endl;

  int x;
  cin >> x;
  int temp;

  switch(x)
  {
    case 1:
      cout << "Student Database." << endl << endl;
      masterStudent.printTree();
      break;
    case 2:
      cout << "Faculty Database." << endl << endl;
      masterFaculty.printTree();
      break;
    case 3:
      cout << "Enter the student's ID: ";
      cin >> temp;
      masterStudent.printNode(temp);
      break;
    case 4:
      cout << "Enter the faculty's ID: ";
      cin >> temp;
      masterFaculty.printNode(temp);
      break;
    case 5:
      cout << "Enter the student's ID: ";
      cin >> temp;

      if(!masterStudent.contains(temp))
      {
        cout << "No entry found with entered ID #." << endl;
      }
      else{
        Student *ptr = masterStudent.find(temp);
        masterFaculty.printNode(ptr->getAdvisorID());
      }
      break;
    case 6:
      cout << "Enter the faculty's ID: ";
      cin >> temp;
      if(!masterFaculty.contains(temp))
      {
        cout << "No entry found with entered ID #." << endl;
      }
      else
      {
        Faculty *ptr2 = masterFaculty.find(temp); //have the ptr to the faculty member
        int count = 0;
        while(count < ptr2->getAdviseeSize()) //print until the advisees
        {
          masterStudent.printNode(ptr2->printAdviseeID(count)); //printNode in the masterStudent BST of the faculty's AdviseeID at the count position in its LL
          ++count;
        }
      }
      break;
    case 7:
      addStudent();
      break;
    case 8:
      cout << "Enter the student's ID: ";
      cin >> temp;
      if(!masterStudent.contains(temp))
      {
        cout << "No entry found with entered ID #." << endl;
      }
      else
      {
        /*takenStudentID[temp-1000] = false; NEED TO REPLACE WITH LINKED LIST
        for(int i = 0; i < numberOfStudents; ++i)
        {
          if(studentID[i] == temp)
          {
            studentID
          }
        }*/
        masterStudent.deleteNode(temp);
        for(int i = 0; i < numberOfFaculty; ++i)
        {
          Faculty *ptr3 = masterFaculty.find(facultyID[i]);
          if(ptr3->containsAdvisee(temp))
          {
            ptr3->removeAdvisee(temp);
          }
        }
      }
      break;
    case 9:
      addFaculty();
      break;
    case 10:
    cout << "Enter the faculty's ID: ";
    cin >> temp;
    if(!masterFaculty.contains(temp))
    {
      cout << "No entry found with entered ID #." << endl;
    }
    else
    {
      /*takenFacultyID[temp-10000] = false; REPLACE WITH LL
      for(int i = 0; i < numberOfFaculty; ++i)
      {
        if(facultyID[i] == temp)
        {
          facultyID = 0;
          break;
        }
      }*/
      --numberOfFaculty;
      masterFaculty.deleteNode(temp);
      for(int i = 0; i < numberOfStudents; ++i)
      {
        Student *ptr4 = masterStudent.find(studentID[i]);
        if(ptr4->getAdvisorID == temp)
        {
          srand(time(NULL));
          int facultyPos = 0;
          facultyPos = (rand() % numberOfFaculty); //0-number of faculty for random index for faculty assignment.
          ptr4->setAdvisorID(facultyID[facultyPos]);
        }
      }
    }
      break;
    case 11:
      break;
    case 12:
      break;
    case 13:
      break;
    case 14:
      //save file off
      cout << "Exiting Program." << endl;
      exit = true;
      break;
    default:
      cout << "Invalid entry. Try again" << endl;
      break;
  }
}
}

void DB::addStudent()
{
  int tempID = 0;
  string tempName = "";
  string tempLevel = "";
  string tempMajor = "";
  double tempGPA = 0;
  int tempFacultyID = 0;
  int facultyPos = 0;

  cout << "Student's name: ";
  cin >> tempName;
  cout << "Student's level (Freshmen, sophmore, etc.): ";
  cin >> tempLevel;
  cout << "Student's Major: ";
  cin >> tempMajor;
  cout << "Student's GPA: ";
  cin >> tempGPA;
  srand(time(NULL));
  while(true) //ensuring that the studentID is not taken
  {
    tempID = (rand() % 9000) + 1000; //STUDENT IDS: 1000-9999, REF: https://stackoverflow.com/questions/4067135/c-generating-a-4-digit-random-number
    if(takenStudentID[tempID - 1000] == false) //IF !LL.CONTAINS(TEMPID) BREAK, ELSE CONTINUE TO LOOP
    {
      takenStudentID[tempID - 1000] = true;
      break;
    }
  }

  /*facultyPos = (rand() % numberOfFaculty); //0-number of faculty for random index for faculty assignment. facultyID needs to be assigned randomly in the LL somehow
  tempFacultyID = facultyID[facultyPos];*/

  //StudentID[numberOfStudents] = tempID;
  ++numberOfStudents;

  //need to assign faculty ID

  tempStudent = new Student(tempID, tempName, tempLevel, tempMajor, tempGPA, tempFacultyID);

  masterStudent.insert(tempStudent);
  cout << "The student's ID is " << tempID << "and their advisor's ID is " << tempFacultyID << endl;

//update the facult's advisee list
  masterFaculty.find(tempFacultyID)->addAdvisee(tempID);
}

void DB::addFaculty()
{
  int tempID = 0;
  string tempName = "";
  string tempLevel = "";
  string tempDept= "";
  Student *tempPtr = nullptr;

  cout << "Faculty's name: ";
  cin >> tempName;
  cout << "Faculty's level (Lecturer, Assistant Prof, etc.): ";
  cin >> tempLevel;
  cout << "Faculty's department: ";
  cin >> tempDept;

  srand(time(NULL));
  while(true) //ensuring that the studentID is not taken
  {
    tempID = (rand() % 9000) + 10000; //FACULTY IDS: 10000-19999, REF: https://stackoverflow.com/questions/4067135/c-generating-a-4-digit-random-number
    if(takenFacultyID[tempID - 10000] == false) //CHANGE TO LL CONTAINS
    {
      takenFacultyID[tempID - 10000] = true;
      break;
    }
  }

  facultyID[numberOfFaculty] = tempID;
  ++numberOfFaculty;

  tempFaculty = new Faculty(tempID, tempName, tempLevel, tempDept);
  masterFaculty.insert(tempFaculty);
}
