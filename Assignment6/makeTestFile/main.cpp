#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
  ofstream writeFile("test.txt");
  srand(time(NULL));
  for(int i = 0; i < 10000; ++i){
  double randomNum = (rand() % 10000) + 1;
  writeFile << randomNum << "\r\n";
  }
  writeFile.close();
  return 0;
}
