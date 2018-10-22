#include <iostream>
#include "SyntaxChecker.h"
#include <fstream>

using namespace std;

SyntaxChecker::SyntaxChecker()
{
  this->fileName = "test.txt";
  //testing that the file exists, if not exits program
  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }
  //run the syntax checker
  runSyntax();
}

SyntaxChecker::SyntaxChecker(string fileName)
{
  //checks that the file exists, exits if not, then runs syntax checker
  this->fileName = fileName;
  if(!ifstream(fileName))
  {
    cout << "File not found. Exiting program." << endl;
    exit(0);
  }
  runSyntax();
}

SyntaxChecker::~SyntaxChecker()
{

}

void SyntaxChecker::runSyntax()
{
  string line = "";
  lineCounter = 1;
  char missingOpener;
  //using a try/catch block to catch the popping an empty list exception
  try{
    while(true)
    {
      ifstream readFile(fileName);
      while(getline(readFile, line))
      {
        for(int i = 0; i < line.length(); ++i)
        {
          if(i < (line.length()-1) && line[i] == '/' && line[i+1] == '/') //i has to less than line.length()-1 to not go out of bounds
          {
            //go to next line by breaking out of the for loop of the current line if its a single line comment
            break;
          }
          //if line[i] is an opening deliminator, push it to the delim stack, push line number to the lineNum stack

          if(line[i] == '{' || line[i] == '[' || line[i] == '(')
          {
            doublePush(line[i], lineCounter);
          }

          //if line[i] is a closing deliminator, pop the delim stack.
          if(line[i] == '}' || line[i] == ']' || line[i] == ')')
          {
            missingOpener = line[i]; //assigning the char to var missingOpener to use in the catch statement.
            char check = delims.pop(); //if delim is an empty list, it will throw a runtime error, which is caught below.
            //missingOpener variable is used to print the the char that doesn't have an opening delim
            if(!isOpposite(check, line[i])) //isOpposite checks that the popped char is the opening to the closing char line[i]
            {
              //if its not opposite, then we know that we have something like ({)} which is incorrect syntax
              cout << "Invalid Syntax: '" << line[i] << "' without an opening on line: " << lineCounter << endl;
              exit(0);
            }
            else //they are oppsoites, delims already popped, need the pop the lineNum
            {
              lineNums.pop();
            }
          }
        }
        ++lineCounter; //after each line, increment the lineCounter
      }
      //if we reach the end of the file but delims is not empty, there is an opening without a closing
      if(!delims.isEmpty())
      {
        cout << "Invalid syntax: '" << delims.pop() << "' without a closing on line: " << lineNums.pop() << endl;
        exit(0);
      }
      //if it passes all above tests, then the syntax is correct
      cout << "The file has correct syntax." << endl;
      cout << "Do you want to check another file? (Y/N): ";
      char choice;
      cin >> choice;
      if(choice == 'Y')
      {
        //this reRun method asks for a new file, checks that it exists, then changes fileName to it
        reRun();
        //stay in the while loop to re-run the program. DO NOT BREAK HERE
      }
      else if(choice == 'N')
      {
        cout << "Exiting program." << endl;
        break;
      }
      else
      {
        cout << "Invalid input. Exiting program." << endl;
        break;
      }
    }
  }
  catch(runtime_error e) //this catches popping an empty stack, meaning that its a closing delim without an opener
  {
    cout << " Invalid syntax: '" << missingOpener << "' without opening on line: " << lineCounter << endl;
    exit(0);
  }
}

bool SyntaxChecker::isOpposite(char c, char d)
{
  if(c == '(' && d == ')')
  {
    return true;
  }
  else if(c == '{' && d == '}')
  {
    return true;
  }
  else if(c == '[' && d == ']')
  {
    return true;
  }
  else
  {
    return false;
  }
}

void SyntaxChecker::reRun()
{
  cout << "What is the name of your file? ";
  string newFile = "";
  cin >> newFile;
  if(!ifstream(newFile))
  {
    cout << "File not found. Exiting program" << endl;
    exit(0);
  }
  this->fileName = newFile;
  lineCounter = 1;
}

void SyntaxChecker::doublePush(char c, int d)
{
  delims.push(c);
  lineNums.push(d);
}
