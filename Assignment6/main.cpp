#include <iostream>
#include "AlgoAnalysis.h"
#include "CommandLineChecker.h"
using namespace std;

int main(int argc, char* argv[])
{
  CommandLineChecker checkIt(argc);
  AlgoAnalysis analyze(argv[1]);
  return 0;
}
