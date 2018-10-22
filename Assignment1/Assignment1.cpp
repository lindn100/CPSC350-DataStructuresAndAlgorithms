#include <iostream>
#include <fstream> //using for input/output files
#include <string>
#include <algorithm> //using algorithm to use transform to change all text in the .txt file to uppercase. See that line for reference
#include <cmath> //using for exponents
#include <iomanip> //using this to display only two decimal points in %s, REFERENCE: https://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-points-with-cout
#include <stdlib.h> //for rand
#include <time.h> //using for time to make rand seeds random
#include <math.h> //using for log, cos, pi

using namespace std;

int main(int argc, char* argv[])
{
//REFERENCE FOR argc: https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
  if(argc == 1)
  {
    cout << "File name not included in command line. Please re-run the program with the file name." << endl;
  }
  if(argc > 2)
  {
    cout << "Too many arguments entered in command line. Please re-run the program with only the file name as an argument." << endl;
  }

  if(argc == 2)
  {
    //Checking that the given file exists. If it doesn't print out the below statement and end program. Else, carry on with program.
    //REFERENCE: https://stackoverflow.com/questions/1647557/ifstream-how-to-tell-if-specified-file-doesnt-exist/39315994
    if(!ifstream(argv[1]))
    {
      cout << "File not found. Please enter a .txt file in the command line." << endl;
    }
    else
    {
      string line = "";
      string choice = "";
      string comboLetter = "";
      bool firstPass = true; //using this to tell to append or create new file.
      srand (time(NULL)); //this is to make the rand seeds truly random based on time REFERENCE: www.cplusplus.com/reference/cstdlib/rand/
      while(true)
      {
        int countA = 0;
        int countT = 0;
        int countC = 0;
        int countG = 0;
        int countAA = 0;
        int countAT = 0;
        int countAG = 0;
        int countAC = 0;
        int countTA = 0;
        int countTT = 0;
        int countTG = 0;
        int countTC = 0;
        int countGA = 0;
        int countGT = 0;
        int countGG = 0;
        int countGC = 0;
        int countCA = 0;
        int countCT = 0;
        int countCG = 0;
        int countCC = 0;
        int sumLength = 0;
        int meanLength = 0;
        int varianceLength = 0;
        int stdLength = 0;
        int countLetter = 0;
        int countLine = 0;
        int comboCount = 0;
        double ADec = 0;
        double TDec = 0;
        double CDec = 0;
        double GDec = 0;
        ifstream readFile;
        if(firstPass)
        {
          readFile.open(argv[1]);
        }
        else
        {
          cout << "What is the name of your file? ";
          cin >> choice;
          if(!ifstream(choice))
          {
            cout << "File not found. Exiting program.";
            readFile.close();
            exit(0);
          }
          readFile.open(choice);
        }

        //for the below logic to work, there must be a newline at the end of the file. The below code checks if there is. If there isn't, it adds a newline to the end of the file.
        //REFERENCE: https://stackoverflow.com/questions/36820881/how-to-check-last-line-of-file-for-new-line-character-c

        //the logic of the program requires a newline after each DNA sequence, including the final line. If the file does not end in a newline, then the program adds a newline to the end of the file. Workaround for a bug experienced earlier.
        readFile.clear();
        readFile.seekg(-1, ios_base::end);
        char c;
        readFile.get(c);
        if( c != '\n')
        {
          readFile.close();
          if(firstPass)
          {
            ofstream fixingFile(argv[1], ios::app);
            fixingFile << "\r\n";
            fixingFile.close();
            readFile.open(argv[1]);
          }
          else
          {
            ofstream fixingFile(choice, ios::app);
            fixingFile << "\r\n";
            fixingFile.close();
            readFile.open(choice);
          }
        }

        //reseting cursor position to the beginning of the file
        readFile.clear();
        readFile.seekg(0, readFile.beg);

        while(getline(readFile, line))
        {
        transform(line.begin(), line.end(), line.begin(), ::toupper);
          //REFERENCE FOR UPPER ABOVE: http://www.cplusplus.com/forum/beginner/228166/
          //below is a for loop that counts individual chars and totalLetters
          for(char x : line)
          {
            switch(x)
            {
              case 'A':
                ++countA;
                ++countLetter;
                break;
              case 'C':
                ++countC;
                ++countLetter;
                break;
              case 'T':
                ++countT;
                ++countLetter;
                break;
              case 'G':
                ++countG;
                ++countLetter;
                break;
              default:
                if(x != '\r')
                {
                  cout << "Invalid DNA character. Exiting Progream" << endl;
                  exit(0);
                }
                  //do nothing if new line.
                  break;
            }

          }

//below for loop is for counting the two char DNA combinations. Looping through entire file again. Can't use a switch statment for strings, so using a bunch of ifs instead
          for(int i = 0; i < line.length()-2; i++)
          {
            comboLetter.append(1, line[i]);
            comboLetter.append(1, line[i+1]);

              if(comboLetter == "AA")
              {
                ++countAA;
                ++comboCount;
              }
              else if(comboLetter == "AT")
              {
                ++countAT;
                ++comboCount;
              }
              else if(comboLetter == "AC")
              {
                ++countAC;
                ++comboCount;
              }
              else if(comboLetter == "AG")
              {
                ++countAG;
                ++comboCount;
              }
              else if(comboLetter == "TA")
              {
                ++countTA;
                ++comboCount;
              }
              else if(comboLetter == "TT")
              {
                ++countTT;
                ++comboCount;
              }
              else if(comboLetter == "TC")
              {
                ++countTC;
                ++comboCount;
              }
              else if(comboLetter == "TG")
              {
                ++countTG;
                ++comboCount;
              }
              else if(comboLetter == "CA")
              {
                ++countCA;
                ++comboCount;
              }
              else if(comboLetter == "CT")
              {
                ++countCT;
                ++comboCount;
              }
              else if(comboLetter == "CC")
              {
                ++countCC;
                ++comboCount;
              }
              else if(comboLetter == "CG")
              {
                ++countCG;
                ++comboCount;
              }
              else if(comboLetter == "GA")
              {
                ++countGA;
                ++comboCount;
              }
              else if(comboLetter == "GT")
              {
                ++countGT;
                ++comboCount;
              }
              else if(comboLetter == "GC")
              {
                ++countGC;
                ++comboCount;
              }
              else if(comboLetter == "GG")
              {
                ++countGG;
                ++comboCount;
              }
              comboLetter = "";
            }
          sumLength += line.length() - 1; //subtracting 1 to remove the new lines included in the .length string method
          ++countLine;
        }
        //sumLength += 1; I'm assumming that there is a newline after the last line of DNA sequence. If there is not, the above for loop logic would not calculate correctly, as well as the sumLength would be incorrect. Update: this bug is fixed by guranteeing a newline at the end of the file.
        ofstream writeFile;
        if(firstPass)
        {
          writeFile.open("RyanLindner.out");
          writeFile << "Ryan Lindner, StudentID: 2260250\r\n";
        }
        else
        {
          writeFile.open("RyanLindner.out", ios::app);
          writeFile << "New DNA File: \r\n";
        }
        writeFile << "Sum of the length of the DNA strings: " << sumLength << "\r\n";
        meanLength = (sumLength / countLine);
        writeFile << "Mean of the length of the DNA strings: " << meanLength << "\r\n";
        //Using below two lines to go to the beginning of the file in order to loop through each line again. Opted to not use a vector
        //REFERNCE: https://stackoverflow.com/questions/16393583/how-to-read-same-file-twice-in-a-row
        readFile.clear();
        readFile.seekg(0, readFile.beg);
        //have to calculate variance after obtaining the mean.
        while(getline(readFile, line))
        {
          int x1 = (line.length() - 1) - meanLength;
          int x2 = pow(x1, 2);
          varianceLength += x2;
        }
        varianceLength /= (countLine - 1);

        writeFile << "Variation of the length of the DNA strings: " << varianceLength << "\r\n";
        stdLength = sqrt(varianceLength);
        writeFile << "Standard Deviation of the length of the DNA strings: " << stdLength << "\r\n\r\n";

        ADec = (double) countA/countLetter;
        TDec = (double) countT/countLetter;
        CDec = (double) countC/countLetter;
        GDec = (double) countG/countLetter;

        writeFile << "Probablities of each nucleotide: \r\n";
        writeFile << "A: " << setprecision(4) << ADec * 100 << "%\r\n";
        writeFile << "T: " << setprecision(4) << TDec * 100 << "%\r\n";
        writeFile << "C: " << setprecision(4) << CDec * 100 << "%\r\n";
        writeFile << "G: " << setprecision(4) << GDec * 100 << "%\r\n\r\n";

        writeFile << "Probabilities of each nucleotide bigram: \r\n";
        writeFile << "AA: " << setprecision(4) << (double) countAA/comboCount * 100 << "%\r\n";
        writeFile << "AT: " << setprecision(4) << (double) countAT/comboCount * 100 << "%\r\n";
        writeFile << "AC: " << setprecision(4) << (double) countAC/comboCount * 100 << "%\r\n";
        writeFile << "AG: " << setprecision(4) << (double) countAG/comboCount * 100 << "%\r\n";
        writeFile << "TA: " << setprecision(4) << (double) countTA/comboCount * 100 << "%\r\n";
        writeFile << "TT: " << setprecision(4) << (double) countTT/comboCount * 100 << "%\r\n";
        writeFile << "TC: " << setprecision(4) << (double) countTC/comboCount * 100 << "%\r\n";
        writeFile << "TG: " << setprecision(4) << (double) countTG/comboCount * 100 << "%\r\n";
        writeFile << "CA: " << setprecision(4) << (double) countCA/comboCount * 100 << "%\r\n";
        writeFile << "CT: " << setprecision(4) << (double) countCT/comboCount * 100 << "%\r\n";
        writeFile << "CC: " << setprecision(4) << (double) countCC/comboCount * 100 << "%\r\n";
        writeFile << "CG: " << setprecision(4) << (double) countCG/comboCount * 100 << "%\r\n";
        writeFile << "GA: " << setprecision(4) << (double) countGA/comboCount * 100 << "%\r\n";
        writeFile << "GT: " << setprecision(4) << (double) countGT/comboCount * 100 << "%\r\n";
        writeFile << "GC: " << setprecision(4) << (double) countGC/comboCount * 100 << "%\r\n";
        writeFile << "GG: " << setprecision(4) << (double) countGG/comboCount * 100 << "%\r\n\r\n";

        for(int i = 0; i < 1000; ++i)
        {
        //to create a number below 0-1. REFERNCE: https://stackoverflow.com/questions/9878965/rand-between-0-and-1
        double r = (double) rand() / (RAND_MAX);
        double s = (double) rand() / (RAND_MAX);
        const double PI = atan(1.0) * 4;
        double C = sqrt(-2 * log(r)) * cos(2 * PI * s);
        int D = (stdLength * C) + meanLength;

          for(int j = 0; j < D; ++j)
          {
            double t = (double) rand() / (RAND_MAX);
            if(t <= ADec)
            {
              writeFile << "A";
            }
            else if(t > ADec && t <= (ADec+TDec))
            {
              writeFile << "T";
            }
            else if(t > (ADec + TDec) && t <= (ADec + TDec + CDec))
            {
              writeFile << "C";
            }
            else
            {
              writeFile << "G";
            }
          }

          writeFile << "\r\n";
        }
        firstPass = false;
        writeFile << "\r\n";
        cout << "The list has been processed. See RyanLindner.out to see the statistics about your file. 1000 DNA strings have been appended to RyanLindner.out." << endl;
        cout << "Do you want to process another list?(Y for yes): ";
        cin >> choice;
        if(choice != "Y")
        {
          readFile.close();
          writeFile.close();
          break;
        }
      }
    }
  }
  return 0;
}
