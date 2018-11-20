#include "DB.h"
#include <iostream>
#include <ctime> //using this for srand, REF: https://stackoverflow.com/questions/7748071/same-randome-numbers-every-time-i-run-the-program
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

DB::DB()
{
  numberOfFaculty = 0;
  numberOfStudents = 0;
  ifstream readFileFaculty;
  ifstream readFileStudent;

  int nameLength;
  int levelLength;
  int deptLength;
  int GPALength;

  string tempString;

  int tempID;
  string tempName;
  string tempLevel;
  string tempDept;
  string tempMajor;
  double tempGPA;
  int tempAdvisorID;

  int digitsInName;
  int digitsInLevel;
  int digitsInDept;
  int digitsInMajor;
  int digitsInGPA;

  readFileFaculty.open("facultyTable.csv");
  string line;

  while(getline(readFileFaculty, line))
  {
    istringstream ss(line); //https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
    getline(ss, tempString);
    tempString.erase(remove(tempString.begin(), tempString.end(), ','), tempString.end()); https://stackoverflow.com/questions/20326356/how-to-remove-all-the-occurrences-of-a-char-in-c-string

    digitsInName = stoi(tempString.substr(0, 1));
    digitsInLevel = stoi(tempString.substr(1, 1));
    digitsInDept = stoi(tempString.substr(2, 1));

    nameLength = stoi(tempString.substr(3, digitsInName));
    levelLength = stoi(tempString.substr(3 + digitsInName, digitsInLevel));
    deptLength = stoi(tempString.substr(3 + digitsInName + digitsInLevel, digitsInDept));


    tempID = stoi(tempString.substr(3+digitsInName+digitsInLevel+digitsInDept, 5));
    tempName = tempString.substr(13, nameLength);
    tempLevel = tempString.substr(13 +nameLength, levelLength);
    tempDept = tempString.substr(13 + nameLength + levelLength, deptLength);

    facultyIDs.insertFront(tempID);
    ++numberOfFaculty;

    tempFaculty = new Faculty(tempID, tempName, tempLevel, tempDept);
    masterFaculty.insert(tempFaculty);
  }
  readFileFaculty.close();

  readFileStudent.open("studentTable.csv");
  while(getline(readFileStudent, line))
  {
    istringstream ss(line);
    getline(ss, tempString);
    tempString.erase(remove(tempString.begin(), tempString.end(), ','), tempString.end());

    digitsInName = stoi(tempString.substr(0, 1));
    digitsInLevel = stoi(tempString.substr(1, 1));
    digitsInMajor = stoi(tempString.substr(2, 1));
    digitsInGPA = stoi(tempString.substr(3, 1));

    nameLength = stoi(tempString.substr(4, digitsInName));
    levelLength = stoi(tempString.substr(4 + digitsInName, digitsInLevel));
    deptLength = stoi(tempString.substr(4 + digitsInName + digitsInLevel, digitsInMajor));
    GPALength = stoi(tempString.substr(4 + digitsInName + digitsInLevel + digitsInMajor, digitsInGPA));

    tempID = stoi(tempString.substr(4+digitsInName+digitsInLevel+digitsInMajor+digitsInGPA, 4));
    tempName = tempString.substr(8+digitsInName+digitsInLevel+digitsInMajor+digitsInGPA, nameLength);
    tempLevel = tempString.substr(8+digitsInName+digitsInLevel+digitsInMajor+digitsInGPA+nameLength, levelLength);
    tempMajor = tempString.substr(8 +digitsInName+digitsInLevel+digitsInMajor+digitsInGPA+nameLength + levelLength, deptLength);
    tempGPA = stod(tempString.substr(8 +digitsInName+digitsInLevel+digitsInMajor+digitsInGPA+nameLength + levelLength+ deptLength, GPALength));
    tempAdvisorID = stoi(tempString.substr(8 +digitsInName+digitsInLevel+digitsInMajor+digitsInGPA+nameLength + levelLength+ deptLength+ GPALength, 5));
//http://www.cplusplus.com/reference/string/stod/
    studentIDs.insertFront(tempID);
    ++numberOfStudents;

    tempStudent = new Student(tempID, tempName, tempLevel, tempMajor, tempGPA, tempAdvisorID);
    masterFaculty.find(tempAdvisorID)->addAdvisee(tempID);
    masterStudent.insert(tempStudent);
  }

  readFileStudent.close();

  startProgram();
}

DB::~DB()
{

}

void DB::startProgram()
{
  bool exitProgram = false;


while(!exitProgram){
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
  int temp2;
  int temp3;

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
        //remove student ID in LL and remove the node in the tree
        studentIDs.removeID(temp);
        masterStudent.deleteNode(temp);
        --numberOfStudents;

        //go through each faculty, if they are in the advisee list, remove them
        for(int i = 0; i < numberOfFaculty; ++i)
        {
          Faculty *ptr3 = masterFaculty.find(facultyIDs.nodeAtPos(i));
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
    cout << temp << endl;
    if(!masterFaculty.contains(temp))
    {
      cout << "No entry found with entered ID #." << endl;
    }
    else
    {
      facultyIDs.removeID(temp);
      --numberOfFaculty;
      masterFaculty.deleteNode(temp);
      if(numberOfFaculty == 0)
      {
        cout << "No more faculty at the school? Guess school is cancelled, thus the application is canceled." << endl;
        exit(0);
      }
      for(int i = 0; i < numberOfStudents; ++i)
      {
        Student *ptr4 = masterStudent.find(studentIDs.nodeAtPos(i));
        if(ptr4->getAdvisorID() == temp)
        {
          srand(time(NULL));
          int facultyPos = 0;
          facultyPos = (rand() % numberOfFaculty); //0-number of faculty for random index for faculty assignment.
          ptr4->setAdvisorID(facultyIDs.nodeAtPos(facultyPos)); //set student's advisor ID to the new ID
          masterFaculty.find(facultyIDs.nodeAtPos(facultyPos))->addAdvisee(ptr4->getID()); //set faculty's ID to the student's ID
        }
      }
    }
      break;
    case 11:
      cout << "Enter the student's ID: ";
      cin >> temp;
      cout << "Enter the new faculty's ID: ";
      cin >> temp2;

      if(!masterStudent.contains(temp) || !masterFaculty.contains(temp2))
      {
        cout << "No entry found with entered ID #." << endl;
      }
      else
      {
      int removeID = masterStudent.find(temp)->getAdvisorID();
      masterStudent.find(temp)->setAdvisorID(temp2); //change student's advisor ID
      masterFaculty.find(removeID)->removeAdvisee(temp); //change old advisor ID to remove the student's ID
      masterFaculty.find(temp2)->addAdvisee(temp); //change the new adivsor ID to include student's ID
      }
      break;
    case 12:
      cout << "Enter the student's ID: ";
      cin >> temp;
      cout << "Enter the new faculty's ID: ";
      cin >> temp2;

      if(!masterStudent.contains(temp) || !masterFaculty.contains(temp2))
      {
        cout << "No entry found with entered ID #." << endl;
      }
      else
      {
        if(numberOfFaculty == 1)
        {
          cout << "Only 1 faculty. Sorry, no new advisor for you." << endl;
        }
        else{
        masterFaculty.find(temp2)->removeAdvisee(temp); //remove advisee for advisor list
        temp3 = (rand() % numberOfFaculty); //0-number of faculty for random index for faculty assignment. facultyID needs to be assigned randomly in the LL somehow
        while(facultyIDs.nodeAtPos(temp3) == temp2)
        {
          temp3 = (rand() & numberOfFaculty); //if the random roll picks the same advisor, roll again until it isnt.
        }

        //now have a new advisor
        masterStudent.find(temp)->setAdvisorID(facultyIDs.nodeAtPos(temp3)); //set student's new advisor to his advisorID field
        masterFaculty.find(facultyIDs.nodeAtPos(temp3))->addAdvisee(temp); //set studnet to new faculty's advisee list
        }
      }
      break;
    case 13:
      break;
    case 14:
      //save file off
      cout << "Exiting Program." << endl;
      exitProgram = true;
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
    if(!studentIDs.contains(tempID)) //IF !LL.CONTAINS(TEMPID) BREAK, ELSE CONTINUE TO LOOP
    {
      break;
    }
  }

  facultyPos = (rand() % numberOfFaculty); //0-number of faculty for random index for faculty assignment. facultyID needs to be assigned randomly in the LL somehow
  tempFacultyID = facultyIDs.nodeAtPos(facultyPos);

  studentIDs.insertFront(tempID);
  ++numberOfStudents;

  //need to assign faculty ID

  tempStudent = new Student(tempID, tempName, tempLevel, tempMajor, tempGPA, tempFacultyID);

  masterStudent.insert(tempStudent);
  cout << "The student's ID is " << tempID << " and their advisor's ID is " << tempFacultyID << endl;

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
    if(!facultyIDs.contains(tempID)) //break if not in the list
    {
      break;
    }
  }

  facultyIDs.insertFront(tempID);
  ++numberOfFaculty;

  tempFaculty = new Faculty(tempID, tempName, tempLevel, tempDept);
  masterFaculty.insert(tempFaculty);
}
