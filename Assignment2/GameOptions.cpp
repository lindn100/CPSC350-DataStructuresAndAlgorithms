#include <iostream>
#include "GameOptions.h"
#include "Rules.h"
#include <fstream>
#include <unistd.h>
using namespace std;

GameOptions::GameOptions()
{
  //initialize the genration counter to 0
  genCounter = 0;
}

void GameOptions::setSize(int x, int y)
{
  //set the size of all boards to the given inputs
  currentBoard.setRow(x);
  currentBoard.setCol(y);
  nextBoard.setRow(x);
  nextBoard.setCol(y);
  previousBoard.setRow(x);
  previousBoard.setCol(y);
}

GameOptions::~GameOptions()
{

}

void GameOptions::convertBoard() //looping through the currentBoard and setting all elements equal to the nextBoard, as when you play the game, the next generation is stored in nextBoard
{
  for(int i = 0; i < currentBoard.getRow(); ++i)
  {
    for(int j =0; j < currentBoard.getCol(); ++j)
    {
      currentBoard.setElement(i, j, nextBoard.getElement(i, j));
    }
  }
  ++genCounter; //every time the generation is converted, it's as if the game has played through one cycle, and thus the generation increases
}

void GameOptions::printGamePause()
{
  usleep(2000000); //pausing for 2 million milliseconds = 2 seconds. Using this as it works on both windows and mac. Source: http://www.martinbroadhurst.com/sleep-for-milliseconds-in-c.html
  cout << "\r\nGeneration " << genCounter << endl;
  currentBoard.printBoard();
}

void GameOptions::printGameEnter()
{
  if(genCounter > 1) //generation 0 is displayed before GameOptions begins, thus after that, we want the user to press enter to generate the next board
  {
    cout << "Press Enter to proceed.";
  }
  getchar();
  cout << "\r\nGeneration " << genCounter << endl;
  currentBoard.printBoard();
}

void GameOptions::printGameFile()
{
  ofstream writeFile; //writing the output to a file called GameOfLife, NOTE: if the game goes on infinitely, the program hangs here. No way to avoid it
  if(genCounter > 1)
  {
    writeFile.open("GameOfLife.txt", ios::app); //append to the file after the first generation
  }
  else
  {
    writeFile.open("GameOfLife.txt"); //if first generation, then overwrite the previous GameOfLife file
  }
  writeFile << "Generation " << genCounter << "\r\n";
  for(int i = 0; i < currentBoard.getRow(); ++i)
  {
    for(int j = 0; j < currentBoard.getCol(); ++j)
    {
      writeFile << currentBoard.getElement(i,j); //can't use printBoard as it uses cout, but this is essentially the same thing
    }
    writeFile << "\r\n";
  }
  writeFile.close();
}

void GameOptions::loadBoard(Board other) //putting Game's currentBoard value's into this class's currentBoard
{
  for(int i = 0; i < other.getRow(); ++i)
  {
    for(int j = 0; j < other.getCol(); ++j)
    {
      this->currentBoard.setElement(i,j, other.getElement(i,j));
    }
  }
}

void GameOptions::playClassic(Rules ruleBook) //needs a ruleBook to know how to display the game
{
  do //used a do while loop here instead of a while loop. I originally did so so that the game forced at least one generation, but now reflecting back on it, it would've worked perfectly fine if it was a while as well
  {
   int copyCounter = 0; //this int will count the number of cells that are a copy between previousBoard and currentBoard. If copy counter ends up equaling the number of elements in the board, then we know the previous board is exactly the same as previous board, and thus can exit the program as the gnerations will repeat.
   for(int i = 0; i < currentBoard.getRow(); ++i)
    {
      for(int j = 0; j < currentBoard.getCol(); ++j)
      {
        int neighborCount = 0; //this counts the total number of neighbors of the current element
        if(previousBoard.getElement(i,j) == currentBoard.getElement(i,j)) //checking if previous element = current element
        {
          copyCounter++;
        }
          if(i == 0 && j == 0) //checking top left corner
          {
            if(currentBoard.checkRight(i, j)) //remember the bool logic from the Board class, returns true if the element to the Right is 'X'
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
          }
          else if(i == 0 && j == (currentBoard.getCol()- 1)) //checking top right corner
          {
            if(currentBoard.checkLeft(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
          }
          else if(i == 0) //checking top row
          {
            if(currentBoard.checkLeft(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
          }
          else if(i == (currentBoard.getRow()-1) && j == 0) //checking bottom left corner
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
          }
          else if(i == (currentBoard.getRow()-1) && j == (currentBoard.getCol()-1)) //checing bottom right corner
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
          }
          else if(i == (currentBoard.getRow() -1)) //checking bottom row
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
          }
          else if(j == 0) //checking left column
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
          }

          else if (j == currentBoard.getCol()-1) //checking right column
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
          }
          else //the rest of the board is inside the outside elements, checking them
            {
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
          }
          //for the current element, if neighborCount is less than 2 or greater than 3, then kill it (set to -)
          if(neighborCount <2 || neighborCount > 3)
          {
            nextBoard.setElement(i, j, '-');
          }
          else if(neighborCount == 3) //else if the element has 3 neighbors, then make it alive
          {
            nextBoard.setElement(i, j, 'X');
          }
          else //else if it has 2 neighbors, leave it as it currently is
          {
            nextBoard.setElement(i, j, currentBoard.getElement(i,j));
          }
      }
    }
     //converting the currentBoard into previousBoard before we convert nextBoard into currentBoard so that we can check repitition
     for(int i = 0; i < currentBoard.getRow(); ++i)
     {
       for(int j = 0; j < currentBoard.getCol(); ++j)
       {
         previousBoard.setElement(i, j, currentBoard.getElement(i, j));
       }
     }
      convertBoard(); //sets currentBoard = nextBoard
      if(copyCounter == currentBoard.getCol() * currentBoard.getRow()) //if the copyCounter equals the # of elements in the board, all elements are equal between previous and current, thus repeats. We can break out of the game if this is true
      {
        cout << "This generation will repeat." << endl;
        break;
      }

      switch(ruleBook.getDisplayStyle()) //prints based on the style given
      {
        case 'P':
          printGamePause();
          break;
        case 'E':
          printGameEnter();
          break;
        case 'F':
          printGameFile();
          break;
      }
    }while (!currentBoard.isEmpty()); //makes sure the board is not all -
    cout << "Press Enter to exit";
    if(ruleBook.getDisplayStyle() != 'E')
    {
      cin.ignore(); //have to ignore the next cin from Pause and File mode because of endl formatting
    }
    getchar(); //using this to get a char, and then exit the program as instructed
}

void GameOptions::playDoughnut(Rules ruleBook)
{
  do
  {
   int copyCounter = 0;
   for(int i = 0; i < currentBoard.getRow(); ++i)
    {
      for(int j = 0; j < currentBoard.getCol(); ++j)
      {
        if(previousBoard.getElement(i,j) == currentBoard.getElement(i,j))
        {
          copyCounter++;
        }
        int neighborCount = 0;
          if(i == 0 && j == 0)
          {
            if(currentBoard.checkRight(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            //have to check the wrap arounds now
            if(currentBoard.getElement(i+1, currentBoard.getCol()-1) == 'X') //the equivalent of DLeft: checks next row end of col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, currentBoard.getCol() -1) == 'X') //the equivalent of Left: checks same row end of col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, currentBoard.getCol()-1) == 'X') //equivalent of ULeft: checks end row end col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j) == 'X') //Up, checks last row but still 0 in col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j+1) == 'X') //URight, checks last row but 1st col
            {
              ++neighborCount;
            }
            //end of top left corner

          }
          else if(i == 0 && j == (currentBoard.getCol()- 1))
          {
            if(currentBoard.checkLeft(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            //wrap arounds
            if(currentBoard.getElement(i+1, 0) == 'X') //Dright checks the next row down, first element
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, 0) == 'X') //Right checks same row, first element
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, 0) == 'X') //URight checks last row first col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j) == 'X') //Up checks last row, last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j-1) == 'X') //ULeft checks last row, previous column of the last
            {
              ++neighborCount;
            }
            //end of top right corner
          }
          else if(i == 0)
          {
            if(currentBoard.checkLeft(i, j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            //checking the upper wraps
            if(currentBoard.getElement(currentBoard.getRow()-1, j-1) == 'X') //Uleft checks last row, previous column
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j) == 'X') //Up checks last row, same col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(currentBoard.getRow()-1, j+1) == 'X') //Uright checks last row, next col
            {
              ++neighborCount;
            }
            //end of top row
          }
          else if(i == (currentBoard.getRow()-1) && j == 0) //bottom left corner
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, 1) == 'X') //Dright checks first row, second col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, 0) == 'X') //Down checks top left corner
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, currentBoard.getCol()-1) == 'X') //DLeft checks first row, last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, currentBoard.getCol()-1) == 'X') //left checks last row last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i-1, currentBoard.getCol()-1) == 'X') //Uleft checks previous row, last column
            {
              ++neighborCount;
            }
            //end of bottom left corner
          }
          else if(i == (currentBoard.getRow()-1) && j == (currentBoard.getCol()-1)) //bottom right corner
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, j-1) == 'X') //Dleft checks first row, second to last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, j) == 'X') //down checks first row, last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, 0) == 'X') //Dright checks first row, first col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, 0) == 'X') //Right checks same row, first col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i-1, 0) == 'X') //URight checks previous row, first col
            {
              ++neighborCount;
            }
            //end of bottom right corner
          }
          else if(i == (currentBoard.getRow() -1))
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, j-1) == 'X') //Dleft checks first row, previous col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, j) == 'X') //Down checks first row, same col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(0, j+1) == 'X') //DRight checks first row, next col
            {
              ++neighborCount;
            }
            //end of last row
          }
          else if(j == 0)
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i-1, currentBoard.getCol()-1) == 'X') //ULeft checks previous row, last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, currentBoard.getCol()-1) == 'X') //Left checks same row, last col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i+1, currentBoard.getCol()-1) == 'X') //DLeft checks next row, last col
            {
              ++neighborCount;
            }
            //end of left side
          }
          else if (j == currentBoard.getCol()-1)
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i-1, 0) == 'X') //Uright checks prev row, first col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i, 0) == 'X') //Right checks same row, first col
            {
              ++neighborCount;
            }
            if(currentBoard.getElement(i+1, 0) == 'X') //DRight checks next row, fist col
            {
              ++neighborCount;
            }
            //end of right side
          }
          else
            {
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
          }
          //done counting alive neighbors, setting the nextBoard value to it
          if(neighborCount <2 || neighborCount >= 4)
          {
            nextBoard.setElement(i, j, '-');
          }
          else if(neighborCount == 3)
          {
            nextBoard.setElement(i, j, 'X');
          }
          else
          {
            nextBoard.setElement(i, j, currentBoard.getElement(i,j));
          }
      }
    }
     //converting the board from nextBoard into newBoard
     for(int i = 0; i < currentBoard.getRow(); ++i)
     {
       for(int j = 0; j < currentBoard.getCol(); ++j)
       {
         previousBoard.setElement(i, j, currentBoard.getElement(i, j));
       }
     }
      convertBoard();
      if(copyCounter == currentBoard.getCol() * currentBoard.getRow())
      {
        cout << "This generation will repeat." << endl;
        break;
      }

      switch(ruleBook.getDisplayStyle())
      {
        case 'P':
          printGamePause();
          break;
        case 'E':
          printGameEnter();
          break;
        case 'F':
          printGameFile();
          break;
      }
    }while (!currentBoard.isEmpty());
    cout << "Press Enter to exit";
    if(ruleBook.getDisplayStyle() != 'E')
    {
      cin.ignore(); //have to do this for E display style
    }
    getchar();
}

void GameOptions::playMirror(Rules ruleBook)
{
  do
  {
   int copyCounter = 0;
   for(int i = 0; i < currentBoard.getRow(); ++i)
    {
      for(int j = 0; j < currentBoard.getCol(); ++j)
      {
        if(previousBoard.getElement(i,j) == currentBoard.getElement(i,j))
        {
          copyCounter++;
        }
        int neighborCount = 0;
        if(i == 0 && j == 0)
        {
          if(currentBoard.checkRight(i, j))
          {
            neighborCount +=2; //for mirror
          }
          if(currentBoard.checkDown(i,j))
          {
            neighborCount +=2; //for mirror
          }
          if(currentBoard.checkDiagonalDownRight(i,j))
          {
            ++neighborCount;
          }
          if(currentBoard.getElement(0,0) == 'X')
          {
            neighborCount +=3;
          }
        }
          else if(i == 0 && j == (currentBoard.getCol()- 1))
          {
            if(currentBoard.checkLeft(i, j))
            {
              neighborCount +=2; //2 bc of mirror
            }
            if(currentBoard.checkDown(i,j))
            {
              neighborCount +=2; //2 bc of mirror
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            //wrap arounds
            if(currentBoard.getElement(i, j) == 'X') //Dright checks the next row down, first element
            {
              neighborCount +=3;
            }
            //end of top right corner
          }
          else if(i == 0)
          {
            if(currentBoard.checkLeft(i, j))
            {
              neighborCount +=2; //2 bc of mirror
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              neighborCount +=2; //2 bc of mirror
            }
            if(currentBoard.getElement(i, j) == 'X') //in top row, checks if itself is X, if it is then it gets 1 addition bc of mirror
            {
              ++neighborCount;
            }
            //end of top row
          }
          else if(i == (currentBoard.getRow()-1) && j == 0) //bottom left corner
          {
            if(currentBoard.checkUp(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.getElement(i, j) == 'X') //corner adds 3 mirrors to counter
            {
              neighborCount +=3;
            }

            //end of bottom left corner
          }
          else if(i == (currentBoard.getRow()-1) && j == (currentBoard.getCol()-1)) //bottom right corner
          {
            if(currentBoard.checkUp(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.getElement(i, j) == 'X') //corner adds 3 mirrors to counter
            {
              neighborCount +=3;
            }
            //end of bottom right corner
          }
          else if(i == (currentBoard.getRow() -1))
          {
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.getElement(i, j) == 'X') //bottom row checks itself and adds a mirror
            {
              ++neighborCount;
            }
            //end of last row
          }
          else if(j == 0)
          {
            if(currentBoard.checkUp(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.getElement(i, j) == 'X') //left col checks itself, adds on bc of mirror
            {
              ++neighborCount;
            }
            //end of left side
          }
          else if (j == currentBoard.getCol()-1)
          {
            if(currentBoard.checkUp(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              neighborCount +=2;
            }
            if(currentBoard.getElement(i, j) == 'X') //right col checks itelf to add a mirror
            {
              ++neighborCount;
            }
            //end of right side
          }
          else
            {
            if(currentBoard.checkRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkUp(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDown(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpRight(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalUpLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownLeft(i,j))
            {
              ++neighborCount;
            }
            if(currentBoard.checkDiagonalDownRight(i,j))
            {
              ++neighborCount;
            }
          }
          //done counting alive neighbors, setting the nextBoard value to it
          if(neighborCount <2 || neighborCount >= 4)
          {
            nextBoard.setElement(i, j, '-');
          }
          else if(neighborCount == 3)
          {
            nextBoard.setElement(i, j, 'X');
          }
          else
          {
            nextBoard.setElement(i, j, currentBoard.getElement(i,j));
          }
      }
    }
     //converting the board from nextBoard into newBoard
     for(int i = 0; i < currentBoard.getRow(); ++i)
     {
       for(int j = 0; j < currentBoard.getCol(); ++j)
       {
         previousBoard.setElement(i, j, currentBoard.getElement(i, j));
       }
     }
      convertBoard();
      if(copyCounter == currentBoard.getCol() * currentBoard.getRow())
      {
        cout << "This generation will repeat." << endl;
        break;
      }

      switch(ruleBook.getDisplayStyle())
      {
        case 'P':
          printGamePause();
          break;
        case 'E':
          printGameEnter();
          break;
        case 'F':
          printGameFile();
          break;
      }
    }while (!currentBoard.isEmpty());
    cout << "Press Enter to exit";
    if(ruleBook.getDisplayStyle() != 'E')
    {
      cin.ignore(); //have to do this for the ending of enter mode
    }
    getchar();
}
