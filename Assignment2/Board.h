#ifndef Board_H
#define Board_H

class Board
{
public:
  Board(); //default constructor
  Board(int, int); //constructor we will be using for our boards
  ~Board(); //deconstructor
  void printBoard(); //printing the contents of the board
  int getRow(); //getter and setters for row and col
  int getCol();
  void setRow(int);
  void setCol(int);
  char getElement(int, int); //to get element at a certain spot in the board
  void setElement(int, int, char);
  bool checkLeft(int, int); //bool logic to check alive neighbors
  bool checkRight(int, int);
  bool checkUp(int, int);
  bool checkDown(int, int);
  bool checkDiagonalDownLeft(int, int);
  bool checkDiagonalDownRight(int, int);
  bool checkDiagonalUpLeft(int, int);
  bool checkDiagonalUpRight(int, int);
  bool isEmpty();
private:
  void setupBoard(int, int); //using setupBoard to create the 2d array of given size(int, int)
  int row;
  int col;
  char **myBoard;

};
#endif
