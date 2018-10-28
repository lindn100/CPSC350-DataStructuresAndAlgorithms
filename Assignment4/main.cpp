#include <iostream>
#include "RegistrarOffice.h"
#include "CommandLineChecker.h"
using namespace std;

int main(int argc, char* argv[])
{
  CommandLineChecker checkIt(argc);
  RegistrarOffice chapman(argv[1]);
  return 0;
}
