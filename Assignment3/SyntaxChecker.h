#ifndef SyntaxChecker_H
#define SyntaxChecker_H
#include <string>
#include "GenStack.h"

class SyntaxChecker
{
public:
  SyntaxChecker();
  SyntaxChecker(string); //take in a fileName
  ~SyntaxChecker();

  void runSyntax(); //run the program

private:
  GenStack<char> delims; //stack of chars of deliminators
  GenStack<int> lineNums; //stack of ints of lineNumbers
  string fileName;
  void doublePush(char, int); //pushing to both delims and lineNums
  bool isOpposite(char, char); //returns true if the two chars are opposite delims: (), {}, [], else false
  int lineCounter;
  void reRun(); //takes in new file, checks that it exists, sets fileName to it, and resets lineCounter to 1


};
#endif
