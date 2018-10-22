#include <iostream>
#include "GenStack.h"
#include <string>
#include "CommandLineChecker.h"
#include <string>
#include <fstream>
#include "SyntaxChecker.h"
using namespace std;

int main(int argc, char* argv[])
{
  //below class checks that the command line has exactly 1 file name
  CommandLineChecker checkIt(argc);
  //run the syntaxChecker on the file in the command line
  SyntaxChecker checkMe(argv[1]);

  return 0;
}
