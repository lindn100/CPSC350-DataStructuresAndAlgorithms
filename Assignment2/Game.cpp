#include <iostream>
#include "Game.h"
#include <string>
#include "Rules.h"
#include <time.h> //time
#include <stdlib.h> //srand,rand for random generation
#include <stdio.h> //using null in srand http://www.cplusplus.com/reference/cstdlib/srand/
#include <fstream> //file I/O
#include "GameOptions.h"

using namespace std;

Game::Game() //nothing done in constructor or destructor, main needs to call the newGame method
{

}

Game::~Game()
{

}


void Game::newGame()
{
  Rules ruleBook; //rulebook to store mode settings and load into the GameOptions class
  GameOptions options; //this class will carry out actually playing of the game
  cout << "Welcome to the Game of Life!" << endl;
  cout << "Would you like to use a random configuration, or provide a file? (R for random, F for file): ";
  char input;
  cin >> input;
  ruleBook.setFileMode(input); //this setFileMode checks that the input is a valid input, else exits the program

  switch(ruleBook.getFileMode())
  {
    case 'R':
      int x, y; //row and col temp values
      double z; //%alive temp value
      cout << "Enter the amount of rows you would like: ";
      cin >> x;
      cout << "Enter the amount of cols you would like: ";
      cin >> y;
      cout << "Enter the decimal value for intital population: ";
      cin >> z;
      randomAssign(x, y, z); //creates board of size(int, int) with %alive of double
      cout << "This is your board" << endl;
      currentBoard.printBoard(); //printing the board so the user sees what they have randomly created
      cout << "\r\n";
      break;
    case 'F':
      cout << "What is your file name? ";
      string file;
      cin >> file;
      loadFile(file); //checks that file exists, then loads the file contents into the Game
      break;
  }

  cout << "What boundary mode would you like to run in? (C for Classic, D for Doughnut, M for mirror): ";
  cin >> input;
  ruleBook.setBoundaryMode(input); //not playing yet becaues need to know the display style first

  cout << "What display mode would you like to run in? (P for Pause, E for Enter, or F for file) ";
  cin >> input;
  ruleBook.setDisplayStyle(input); //now we can play based on their boundar mode and display style

//the play loop
  switch(ruleBook.getBoundaryMode())
  {
    case 'C':
      if(ruleBook.getDisplayStyle() != 'F') //file mode should not print to console to display gen 0
      {
        //displaying gen 0
        cout << "Generation 0" << endl;
        currentBoard.printBoard();
      }
      options.setSize(currentBoard.getRow(), currentBoard.getCol()); //copying the currentBoard dimensions into GameOptions (which plays the game)
      options.loadBoard(currentBoard); //take all individual elements in currentBoard and loads them into GameOptions copied board with the same dimension
      options.playClassic(ruleBook); //play the game based on the rules we accepted in this class
      break;
    case 'D':
      if(ruleBook.getDisplayStyle() != 'F')
      {
        cout << "Generation 0" << endl;
        currentBoard.printBoard();
      }
      options.setSize(currentBoard.getRow(), currentBoard.getCol());
      options.loadBoard(currentBoard);
      options.playDoughnut(ruleBook);
      break;
    case 'M':
     if(ruleBook.getDisplayStyle() != 'F')
      {
        cout << "Generation 0" << endl;
        currentBoard.printBoard();
      }
      options.setSize(currentBoard.getRow(), currentBoard.getCol());
      options.loadBoard(currentBoard);
      options.playMirror(ruleBook);
      break;
  }
}

void Game::loadFile(string fileName)
{
  if(!ifstream(fileName)) //checking that the file exists
  {
    cout << "Invalid file name. Exiting program." << endl;
    exit(0);
  }
  else
  {
    ifstream readFile(fileName);
    int x, y;
    string z;
    readFile >> x;
    readFile >> y;
    currentBoard.setRow(x);
    currentBoard.setCol(y);
    for(int i = 0; i < currentBoard.getRow(); ++i)
    {
      readFile >> z; //read in a string as a row from the file for each row
      for(int j = 0; j < currentBoard.getCol(); ++j)
      {
        currentBoard.setElement(i, j, z[j]); //set the currentBoard's index to the string's index
      }
    }
    readFile.close();
  }

}

void Game::randomAssign(int row, int col, double pop)
{
  currentBoard.setRow(row);
  currentBoard.setCol(col);
  srand(time(NULL)); //random number based on the time the method is called, see reference in the include statements at top
  for(int i = 0; i < currentBoard.getRow(); ++i)
  {
    for(int j = 0; j < currentBoard.getCol(); ++j)
    {
      double r = ((double) rand() / (RAND_MAX)); //random number between 0 and 1
      if(r <= pop)
      {
        currentBoard.setElement(i, j, 'X');
      }
      else
      {
        currentBoard.setElement(i, j, '-');
      }
    }
  }
}
