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

  //LOADING IN PREVIOUS FILES
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

//i've made my own storage of students/faculty by using csv's and converting them to strings
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
    tempName = tempString.substr(3+digitsInName+digitsInLevel+digitsInDept + 5, nameLength);
    tempLevel = tempString.substr(3+digitsInName+digitsInLevel+digitsInDept + 5 + nameLength, levelLength);
    tempDept = tempString.substr(3+digitsInName+digitsInLevel+digitsInDept + 5 + nameLength + levelLength, deptLength);

    facultyIDs.insertFront(tempID);
    ++numberOfFaculty;


    tempFaculty = new Faculty(tempID, tempName, tempLevel, tempDept);
    masterFaculty.insert(tempFaculty);
  }
  readFileFaculty.close();

  //faculty is in masterFaculty, need to load in students now

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
  cout << "12. Remove an advisee from a faculty member given the ID of the student." << endl;
  cout << "13. Rollback" << endl;
  cout << "14. Exit" << endl;

  int x;
  cin >> x;
  int temp;
  int temp2;
  int temp3;
  int counter;

  int digitsInName2;
  int digitsInLevel2;
  int digitsInMajor2;
  int digitsInDept2;
  int digitsInGPA2;
  int numOfAdvisees;


  int nameLength2;
  int levelLength2;
  int deptLength2;
  int GPALength2;


  int tempID2;
  string tempName2;
  string tempLevel2;
  string tempMajor2;
  double tempGPA2;
  string tempDept2;
  int tempAdvisorID2;

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

        string workingName = masterStudent.find(temp)->getName();
        string workingLevel = masterStudent.find(temp)->getLevel();
        string workingMajor = masterStudent.find(temp)->getMajor();
        string workingGPA = to_string(masterStudent.find(temp)->getGPA());
        string workingAdvisorID = to_string(masterStudent.find(temp)->getAdvisorID());
        int sizeOfGPA;
        workingGPA.erase(workingGPA.find_last_not_of('0'), std::string::npos); //cut all 0's off the double. ref: https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros

        if(workingGPA.find('.') == string::npos)
        {
          sizeOfGPA = workingGPA.length();
        }
        else
        {
          sizeOfGPA = workingGPA.length() + 1;
        }

        int sizeOfName = workingName.length();
        int sizeOfLevel = workingLevel.length();
        int sizeOfMajor = workingMajor.length();

        int tempNameSize = sizeOfName;
        int tempLevelSize = sizeOfLevel;
        int tempMajorSize = sizeOfMajor;
        int tempGPASize = sizeOfGPA;

        int digitsOfName = 0;
        int digitsOfLevel = 0;
        int digitsInMajor = 0;
        int digitsInGPA = 0;


        while(tempNameSize > 0)
        {
          tempNameSize /= 10;
          ++digitsOfName;
        }

        while(tempLevelSize > 0)
        {
          tempLevelSize /= 10;
          ++digitsOfLevel;
        }

        while(tempMajorSize > 0)
        {
          tempMajorSize /= 10;
          ++digitsInMajor;
        }

        while(tempGPASize > 0)
        {
          tempGPASize /= 10;
          ++digitsInGPA;
        }

//this is for rollback
        string addToStack = "3" + to_string(digitsOfName) + to_string(digitsOfLevel) + to_string(digitsInMajor) + to_string(digitsInGPA) + to_string(sizeOfName) + to_string(sizeOfLevel) + to_string(sizeOfMajor) + to_string(sizeOfGPA) + to_string(temp) + workingName + workingLevel + workingMajor + workingGPA + workingAdvisorID;
        rollBack.push(addToStack);

        masterStudent.deleteNode(temp);
        --numberOfStudents;

        //go through each faculty, if they are in the advisee list, remove them
        for(int i = 0; i < numberOfFaculty; ++i)
        {
          Faculty *ptr3 = masterFaculty.find(facultyIDs.nodeAtPos(i));
          if(ptr3->containsAdvisee(temp))
          {
            ptr3->removeAdvisee(temp);
            break;
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
      --numberOfFaculty;

      int workingID = facultyIDs.removeID(temp);
      string workingName = masterFaculty.find(workingID)->getName();
      string workingLevel = masterFaculty.find(workingID)->getLevel();
      string workingDept = masterFaculty.find(workingID)->getDepartment();

      int sizeOfName = workingName.length();
      int sizeOfLevel = workingLevel.length();
      int sizeOfDept = workingDept.length();

      int tempNameSize = sizeOfName;
      int tempLevelSize = sizeOfLevel;
      int tempDeptSize = sizeOfDept;

      int digitsOfName = 0;
      int digitsOfLevel = 0;
      int digitsInDept = 0;

      while(tempNameSize > 0)
      {
        tempNameSize /= 10;
        ++digitsOfName;
      }

      while(tempLevelSize > 0)
      {
        tempLevelSize /= 10;
        ++digitsOfLevel;
      }

      while(tempDeptSize > 0)
      {
        tempDeptSize /= 10;
        ++digitsInDept;
      }

      string allAdvisees;
      int numOfAdvisees = 0;
      while(masterFaculty.find(temp)->sizeOfAdvisees() != 0)
      {
        allAdvisees += to_string(masterFaculty.find(temp)->removeAdviseeFront());
        ++numOfAdvisees;
      }

      string addToStack = "4" + to_string(digitsOfName) + to_string(digitsOfLevel) + to_string(digitsInDept) + to_string(numOfAdvisees) + to_string(sizeOfName) +  to_string(sizeOfLevel) + to_string(sizeOfDept) + to_string(workingID) + workingName + workingLevel + workingDept + allAdvisees;
      rollBack.push(addToStack);

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

      string addToStack = "5" + to_string(temp) + to_string(temp2) + to_string(removeID);
      rollBack.push(addToStack);
      }
      break;
    case 12:
      cout << "Enter the student's ID: ";
      cin >> temp;
      temp2 = masterStudent.find(temp)->getAdvisorID();

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
        string addToStack = "5" + to_string(temp) + to_string(masterFaculty.find(facultyIDs.nodeAtPos(temp3))->getID()) + to_string(temp2);
        rollBack.push(addToStack);
        }
      }
      break;
    case 13:
    if(rollBack.isEmpty())
    {
      cout << "Nothing to undo." << endl;
    }
    else
    {
      string poppedString = rollBack.pop();
      char choice = poppedString[0];
      switch(choice)
      {
        case '1': //we must remove a student
          temp = stoi(poppedString.substr(1, 4));
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
                break;
              }
            }
          }
          break;
        case '2': //must remove a faculty with no advisee's
          temp = stoi(poppedString.substr(1, 5));
          facultyIDs.removeID(temp);
          --numberOfFaculty;
          masterFaculty.deleteNode(temp);
          break;
        case '3':
          digitsInName2 = stoi(poppedString.substr(1, 1));
          digitsInLevel2 = stoi(poppedString.substr(2, 1));
          digitsInMajor2 = stoi(poppedString.substr(3, 1));
          digitsInGPA2 = stoi(poppedString.substr(4, 1));


          nameLength2 = stoi(poppedString.substr(5, digitsInName2));
          levelLength2 = stoi(poppedString.substr(5 + digitsInName2, digitsInLevel2));
          deptLength2 = stoi(poppedString.substr(5 + digitsInName2 + digitsInLevel2, digitsInMajor2));
          GPALength2 = stoi(poppedString.substr(5 + digitsInName2 + digitsInLevel2 + digitsInMajor2, digitsInGPA2));


          tempID2 = stoi(poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2, 4));
          tempName2 = poppedString.substr(9+digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2, nameLength2);
          tempLevel2 = poppedString.substr(9+digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2+nameLength2, levelLength2);
          tempMajor2 = poppedString.substr(9 +digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2+nameLength2 + levelLength2, deptLength2);
          tempGPA2 = stod(poppedString.substr(9 +digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2+nameLength2 + levelLength2+ deptLength2, GPALength2));
          tempAdvisorID2 = stoi(poppedString.substr(9 +digitsInName2+digitsInLevel2+digitsInMajor2+digitsInGPA2+nameLength2 + levelLength2+ deptLength2+ GPALength2, 5));
      //http://www.cplusplus.com/reference/string/stod/
          studentIDs.insertFront(tempID2);
          ++numberOfStudents;

          tempStudent = new Student(tempID2, tempName2, tempLevel2, tempMajor2, tempGPA2, tempAdvisorID2);
          masterFaculty.find(tempAdvisorID2)->addAdvisee(tempID2);
          masterStudent.insert(tempStudent);
          break;
        case '4':
          digitsInName2 = stoi(poppedString.substr(1, 1));
          digitsInLevel2 = stoi(poppedString.substr(2, 1));
          digitsInDept2 = stoi(poppedString.substr(3, 1));
          numOfAdvisees = stoi(poppedString.substr(4, 1));



          nameLength2 = stoi(poppedString.substr(5, digitsInName2));
          levelLength2 = stoi(poppedString.substr(5 + digitsInName2, digitsInLevel2));
          deptLength2 = stoi(poppedString.substr(5 + digitsInName2 + digitsInLevel2, digitsInDept2));


          tempID2 = stoi(poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInDept2, 5));
          tempName2 = poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInDept2 + 5, nameLength2);
          tempLevel2 = poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInDept2 + 5 + nameLength2, levelLength2);
          tempDept2 = poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInDept2 + 5 + nameLength2 + levelLength2, deptLength2);

          facultyIDs.insertFront(tempID2);
          ++numberOfFaculty;

          tempFaculty = new Faculty(tempID2, tempName2, tempLevel2, tempDept2);
          masterFaculty.insert(tempFaculty);
          counter = 0;

          while(numOfAdvisees > 0)
          {
            temp2 = stoi(poppedString.substr(5+digitsInName2+digitsInLevel2+digitsInDept2 + 5 + nameLength2 + levelLength2 + deptLength2 + (4*counter), 4));
            ++counter;
            temp3 = masterStudent.find(temp2)->getAdvisorID();
            masterFaculty.find(temp3)->removeAdvisee(temp2);
            masterStudent.find(temp2)->setAdvisorID(tempID2);
            masterFaculty.find(tempID2)->addAdvisee(temp2);
            --numOfAdvisees;
          }

          break;
        case '5':
          temp = stoi(poppedString.substr(1, 4)); //student's ID
          temp2 = stoi(poppedString.substr(5, 5)); //current ID
          temp3 = stoi(poppedString.substr(10, 5)); //old ID

          masterStudent.find(temp)->setAdvisorID(temp3);
          masterFaculty.find(temp2)->removeAdvisee(temp);
          masterFaculty.find(temp3)->addAdvisee(temp);
          break;
      }
    }
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

//write to file here
ofstream writeFacultyFile("facultyTable.csv");
while(!masterFaculty.isEmpty())
{
  int workingID = facultyIDs.removeFront();
  string workingName = masterFaculty.find(workingID)->getName();
  string workingLevel = masterFaculty.find(workingID)->getLevel();
  string workingDept = masterFaculty.find(workingID)->getDepartment();

  int sizeOfName = workingName.length();
  int sizeOfLevel = workingLevel.length();
  int sizeOfDept = workingDept.length();

  int tempNameSize = sizeOfName;
  int tempLevelSize = sizeOfLevel;
  int tempDeptSize = sizeOfDept;

  int digitsOfName = 0;
  int digitsOfLevel = 0;
  int digitsInDept = 0;

  while(tempNameSize > 0)
  {
    tempNameSize /= 10;
    ++digitsOfName;
  }

  while(tempLevelSize > 0)
  {
    tempLevelSize /= 10;
    ++digitsOfLevel;
  }

  while(tempDeptSize > 0)
  {
    tempDeptSize /= 10;
    ++digitsInDept;
  }

  writeFacultyFile << digitsOfName << digitsOfLevel << digitsInDept << "," << sizeOfName << "," << sizeOfLevel << "," << sizeOfDept << "," << workingID << "," << masterFaculty.find(workingID)->getName() << "," << masterFaculty.find(workingID)->getLevel() << "," << masterFaculty.find(workingID)->getDepartment() << endl;
  masterFaculty.deleteNode(workingID);
}
writeFacultyFile.close();


ofstream writeStudentFile("studentTable.csv");
while(!masterStudent.isEmpty())
{
  int workingID = studentIDs.removeFront();
  string workingName = masterStudent.find(workingID)->getName();
  string workingLevel = masterStudent.find(workingID)->getLevel();
  string workingMajor = masterStudent.find(workingID)->getMajor();
  string workingGPA = to_string(masterStudent.find(workingID)->getGPA());
  int sizeOfGPA;
  workingGPA.erase(workingGPA.find_last_not_of('0'), std::string::npos); //cut all 0's off the double. ref: https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros

  if(workingGPA.find('.') == string::npos)
  {
    sizeOfGPA = workingGPA.length();
  }
  else
  {
    sizeOfGPA = workingGPA.length() + 1;
  }

  int sizeOfName = workingName.length();
  int sizeOfLevel = workingLevel.length();
  int sizeOfMajor = workingMajor.length();

  int tempNameSize = sizeOfName;
  int tempLevelSize = sizeOfLevel;
  int tempMajorSize = sizeOfMajor;
  int tempGPASize = sizeOfGPA;

  int digitsOfName = 0;
  int digitsOfLevel = 0;
  int digitsInMajor = 0;
  int digitsInGPA = 0;


  while(tempNameSize > 0)
  {
    tempNameSize /= 10;
    ++digitsOfName;
  }

  while(tempLevelSize > 0)
  {
    tempLevelSize /= 10;
    ++digitsOfLevel;
  }

  while(tempMajorSize > 0)
  {
    tempMajorSize /= 10;
    ++digitsInMajor;
  }

  while(tempGPASize > 0)
  {
    tempGPASize /= 10;
    ++digitsInGPA;
  }

  writeStudentFile << digitsOfName << digitsOfLevel << digitsInMajor << digitsInGPA << "," << sizeOfName << "," << sizeOfLevel << "," << sizeOfMajor << "," << sizeOfGPA << "," << workingID << "," << masterStudent.find(workingID)->getName() << "," << masterStudent.find(workingID)->getLevel() << "," << masterStudent.find(workingID)->getMajor() << "," <<  masterStudent.find(workingID)->getGPA() << "," << masterStudent.find(workingID)->getAdvisorID() << endl;
  masterStudent.deleteNode(workingID);
}
writeStudentFile.close();

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
  cin.ignore();
  getline(cin, tempName);
  cout << endl;
  cout << "Student's level (Freshmen, sophmore, etc.): ";
  getline(cin, tempLevel);
  cout << endl;
  cout << "Student's Major: ";
  getline(cin, tempMajor);
  cout << endl;
  cout << "Student's GPA: ";
  cin >> tempGPA;
  cout << endl;
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
  string addToStack = "1" + to_string(tempID);
  rollBack.push(addToStack);
}

void DB::addFaculty()
{
  int tempID = 0;
  string tempName = "";
  string tempLevel = "";
  string tempDept= "";
  Student *tempPtr = nullptr;

  cout << "Faculty's name: ";
  cin.ignore();
  getline(cin, tempName);
  cout << endl;
  cout << "Faculty's level (Lecturer, Assistant Prof, etc.): ";
  getline(cin, tempLevel);
  cout << endl;
  cout << "Faculty's department: ";
  getline(cin, tempDept);
  cout << endl;

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
  string addToStack = "2" + to_string(tempID);
  rollBack.push(addToStack);
}
