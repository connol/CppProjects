//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <iostream>


class Creature {
public:
  //Overrides the << operrator to write loaction of creature in maze 
  //Precondition: Object Creature is not null
  //PosstCondtion: Outputs location of Creature 
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  int Row;

  int Col;

  bool end;

  //Will reverse a string thats inputed
  //Precondtion: path must not be an empty string
  //Postcondtion: the inputed string will be returned reversed
  string reverse(string path) const;
public:
  //Initializes the starting location of the Creatrue
  //Precondition: should be a positive numbers within maze for code fucntion correctly
  //Poscondtion: a new creature object with location intialzed
  Creature(int Row, int Col);

  //checks if the creature is at the exit of the maze
  //Precondition: Maze must have one or no exits with border of walls and empty postions as open spots
  //Postcondition: returns true or false based on if the creature is at exit or not
  bool atExit(const Maze &Maze) const;

  //a helper for solve which does the recursive bit to solve a maze
  //Precondition: row and col should be within the Maze boudaries
  //Postcondition: returns a string of the path taken by the creature backwards in the form N,E,S,W for direction
  string solveHelp(Maze &Maze,int row,int col);
  
  //will solve a maze if possible based on starting postion
  //Precondition: Maze must have one or no exits with border of walls and empty postions as open spots
  //Postcondition: returns string of the moves taken by the creature in form of N,E,S,W for directions 
  string solve(Maze &Maze);

  

  //Moves creature North
  //Precondition: Creature must not be on edge of Maze
  //Postcondition:Will move Creature North in maze
  string goNorth(Maze &Maze);
  
  //Moves creature East
  //Precondition: Creature must not be on edge of Maze
  //Postcondition:Will move Creature East in maze
  string goEast(Maze &Maze);

  //Moves creature West
  //Precondition: Creature must not be on edge of Maze
  //Postcondition:Will move Creature West in maze
  string goWest(Maze &Maze);

  //Moves creature South
  //Precondition: Creature must not be on edge of Maze
  //Postcondition:Will move Creature North in maze
  string goSouth(Maze &Maze);



};

#endif //ASS3_CREATURE_H
