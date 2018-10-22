#ifndef Rules_h
#define Rules_h

class Rules
{
public:
  Rules(); //default constructor
  Rules(char, char, char); //setting game modes
  ~Rules();
  char getFileMode();
  char getBoundaryMode();
  char getDisplayStyle();
  void setFileMode(char);
  void setBoundaryMode(char);
  void setDisplayStyle(char);

private:
  char fileMode; //asking if they want a random configuration or to use their file
  char boundaryMode; //Classic, Donut, or Mirror
  char displayStyle; //printPause, Enter, or File

};
#endif
