#ifndef GameOptions_H
#define GameOptions_H
#include "Board.h"
#include "Rules.h"

class GameOptions
{
public:
  GameOptions();
  void setSize(int, int); //creating current, previous, and next boards of the size(int, int) which must match the currentBoard in Game, next and previous defaulted to '-' everywhere as is the defaulsetUp of Boards
  ~GameOptions();
  void playClassic(Rules); //different play types based on Boundary Mode from Rules
  void playDoughnut(Rules);
  void playMirror(Rules);
  void loadBoard(Board); //copying the currentBoard from game into currentBoard of this class GameOptions

private:
  int genCounter; //counting the generations
  void convertBoard(); //after setting the nextGeneration through the game logic, convert currentBoard to be the same as nextBoard
  Board currentBoard;
  Board nextBoard;
  Board previousBoard;
  void printGamePause(); //different modes for printing based on Rules
  void printGameEnter();
  void printGameFile();
};
#endif
