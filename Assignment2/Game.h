#ifndef Game_H
#define Game_H
#include <string>
#include "Board.h"
#include "Rules.h"

using namespace std;

class Game
{
public:
  Game();
  ~Game();
  void newGame(); //using this to start the game -get options for fileMode, boundaryMode, and displayStyle;



private:

  void loadFile(string); //given a file in format: row endl, col endl, board, loading it as our board
  void randomAssign(int, int, double); //randomly creating a board of size(int,int) with a %alive of their given double
  Board currentBoard; //what we use as current generation
  Rules ruleBook; //tracks game option modes

};
#endif
