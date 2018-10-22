#include <iostream>
#include "Board.h"

using namespace std;

//default constructor
Board::Board()
{
  setRow(2); //defaulting the size of the Board to 2x2
  setCol(2);
  setupBoard(row, col);
}

//constructor that we will be using mostly
Board::Board(int x, int y)
{
  setRow(x);
  setCol(y);
  setupBoard(row, col);
}

//deconstructor
Board::~Board()
{
  for (int i = 0; i < row; ++i) //myBoard is a pointer to pointers of an array. This for loop is going through that pointer to clear out all of the other pointers, then deleting the pointer afterwards
  {
    delete myBoard[i];
  }
  delete myBoard;
}

void Board::setupBoard(int x, int y)
{
//creating an array of arrays of chars: REFERENCE http://www.cplusplus.com/forum/general/69673/
myBoard = new char*[x]; //intialize the point of pointers to an array of size x with char pointers
for(int i = 0; i < x; ++i)
{
  myBoard[i] = new char[y]; //assign each pointer an array of size y with chars
  for(int j = 0; j < y; ++j)
  {
    myBoard[i][j] = '-'; //assign each value of the board to -
  }
}
}

void Board::printBoard() //print each value in the board, adding a newline after each row
{
  for(int i = 0; i < row; ++i)
  {
    for(int j = 0; j < col; ++j)
    {
      cout << myBoard[i][j];
    }
    cout << "\n";
  }
}

//accessor and mutator methods

int Board::getRow()
{
  return row;
}

int Board::getCol()
{
  return col;
}

void Board::setRow(int x)
{
  this->row = x;
  setupBoard(row, col); //setting up board (aka creating a new one and discarding the old one) because arrays are static and their size cannot change, thus anytime you want to change size, you have to remake the board
}

void Board::setCol(int x)
{
  this->col = x;
  setupBoard(row, col);
}

//get element to identify what the element at the current index is
char Board::getElement(int x, int y)
{
  return myBoard[x][y];
}

void Board::setElement(int x, int y, char c)
{
  myBoard[x][y] = c;
}

//the below bool logic is used to check if the current element has an 'alive' neighbor in the current direction (checkLeft returns true if its left neighbor is 'X')
bool Board::checkLeft(int x, int y)
{
  return myBoard[x][y-1] == 'X';
}

bool Board::checkRight(int x, int y)
{
  return myBoard[x][y+1] == 'X';
}

bool Board::checkUp(int x, int y)
{
  return myBoard[x-1][y] == 'X';
}

bool Board::checkDown(int x, int y)
{
  return myBoard[x+1][y] == 'X';
}

bool Board::checkDiagonalDownLeft(int x, int y)
{
  return (myBoard[x+1][y-1] == 'X');
}

bool Board::checkDiagonalDownRight(int x, int y)
{
  return (myBoard[x+1][y+1] == 'X');
}

bool Board::checkDiagonalUpLeft(int x, int y)
{
  return (myBoard[x-1][y-1] == 'X');
}

bool Board::checkDiagonalUpRight(int x, int y)
{
  return (myBoard[x-1][y+1] == 'X');
}

bool Board::isEmpty() //returns true if entire board is '-', else returns false
{
  for(int i = 0; i < row; ++i)
  {
    for(int j = 0; j < col; ++j)
    {
      if(myBoard[i][j] != '-')
      {
        return false;
      }
    }
  }
  return true;
}
