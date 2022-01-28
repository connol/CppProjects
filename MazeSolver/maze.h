//h file for maze which has an exit ability to make path and visited and height and width
//Connor Lauerman 
//Date:2/7/2021

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {

  //Overrides the << operator to print the maze to screen as square with marks
  //Preconditions:  Maze is defined
  //Postcondition: the maze writen to screen 
  friend ostream &operator<<(ostream &Out, const Maze &Maze);
private:
  const static int MAX_SIZE = 100;
  char Field[MAX_SIZE][MAX_SIZE];
  int Width, Height;
  int ExitRow, ExitColumn;
public:
  explicit Maze(const string &FileName);

  //Checks if a certain spot has no charcters in the maze
  //Precondition: the spot is within the maze
  //Postcondition: returns true or false based on if the spot is clear or not
  bool isClear(int Row, int Col) const;

  //Marks a spot in the maze as the correct path to escape
  //Precondition:Must be a spot within the dimensions of the array
  //PostConition: no return but will write to maze the spot
  void markAsPath(int Row, int Col);

  //Checks if a certain spot has no charcters in the maze
  //Precondition: the spot is within the maze
  //Postcondition: returns true or false based on if the spot is clear or not
  void markAsVisited(int Row, int Col);

 //retrives the row where the exit is in the maze
 //Precondtion: exit Row is defined in maze file
 //Postcondtion: retruns the row as an int
  int getExitRow() const;

  //retrives the column where the exit is in the maze
  //Precondtion: exit column is defined in maze file
  //Postcondtion: retruns the row as an int
  int getExitColumn() const;

  //retrieves the height of the maze
  //Preconditon: height must be defined in the maze file
  //Postcondition: returns height of maze as int
  int getHeight() const;

  //retrieves the Width of the maze
  //Preconditon: Width must be defined in the maze file
  //Postcondition: returns height of maze as int
  int getWidth() const;

};

#endif //ASS3_MAZE_H
