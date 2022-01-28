//Object that is capable of solving a maze with the ability to go noth south east and west
//Connor Lauerman
//Date:2/7/2021

#include "creature.h"
#include <string>
#include <iostream>

//Overrides the << operrator to write loaction of creature in maze 
//Precondition: Object Creature is not null
//PosstCondtion: Outputs location of Creature 
std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
  Out << "C("<< Creature.Row <<"," << Creature.Col << ")"<< endl;
  
  return Out;
}

//Will reverse a string thats inputed
//Precondtion: path must not be an empty string
//Postcondtion: the inputed string will be returned reversed
string Creature::reverse(string Path)  const
{
  if(Path.length()<=1)
  {
    return Path;
  }
  else
  {
   return reverse(Path.substr(1,Path.length())) + Path.at(0);
  }
}

//Initializes the starting location of the Creatrue
//Precondition: should be a positive numbers within maze for code fucntion correctly
//Poscondtion: a new creature object with location intialzed
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}


//checks if the creature is at the exit of the maze
//Precondition: Maze must have one or no exits with border of walls and empty postions as open spots
//Postcondition: returns true or false based on if the creature is at exit or not
bool Creature::atExit(const Maze &Maze) const {
  if(Row==Maze.getExitRow() && Col==Maze.getExitColumn())
  {
  return true;
  }
  else{
    return false;
  }
}

//a helper for solve which does the recursive bit to solve a maze
//Precondition: row and col should be within the Maze boudaries
//Postcondition: returns a string of the path taken by the creature backwards in the form N,E,S,W for direction
string Creature::solveHelp(Maze &Maze,int row,int col)
{
string Path;

Maze.markAsVisited(row,col);
Row=row;
Col=col;
bool found = (atExit(Maze));
if(found)
{

  Maze.markAsPath(row,col);
  end=true;
}
if(!found)
{
  
    while(!found && !end && ((Maze.isClear(row+1,col)|| Maze.isClear(row-1,col)||Maze.isClear(row,col+1)||Maze.isClear(row,col-1))))
    {      
      if(Maze.isClear(row+1,col) && !end) //South
    {
      Maze.markAsPath(row,col);
      Path = Path+solveHelp(Maze,row+1,col);
      if(end)
      {
      Path = Path +"S";
      }
      
      
    }
    if(Maze.isClear(row,col+1)&& !end) //East
    {
      Maze.markAsPath(row,col);
      Path = Path+ solveHelp(Maze,row,col+1);
       if(end)
      {
       Path = Path + "E";
      }
      
    }
    if(Maze.isClear(row-1,col) && !end)//North
    {
      
       Maze.markAsPath(row,col);
      Path = Path + solveHelp(Maze,row-1,col);
       if(end)
      {
       Path = Path + "N";
      }
    }

    if(Maze.isClear(row,col-1) &&!end) //West
    {
      Maze.markAsPath(row,col);
      Path = Path  + solveHelp(Maze,row,col-1);
      if(end)
      {
        Path = Path + "W";
      }
    }
    }
    }

if(!(Maze.isClear(row+1,col)|| Maze.isClear(row-1,col)||Maze.isClear(row,col+1)||Maze.isClear(row,col-1))&& !end)
{
  Maze.markAsVisited(row,col);
  return Path;
}
return Path;
}

//will solve a maze if possible based on starting postion
//Precondition: Maze must have one or no exits with border of walls and empty postions as open spots
//Postcondition: returns string of the moves taken by the creature in form of N,E,S,W for directions 
string Creature::solve(Maze &Maze) {
  string Path;
  bool noExit=false;
  end=false;
  if(!Maze.isClear(Maze.getExitRow(),Maze.getExitColumn()))
  {
    noExit=true;
  }
  Path=solveHelp(Maze,Row,Col);
  if(noExit)
  {
    return "No exit";
  }
  else
  {
  Path=reverse(Path);
  return Path;
  }
}
  
//Moves creature North
//Precondition: Creature must not be on edge of Maze
//Postcondition:Will move Creature North in maze
string Creature::goNorth(Maze &Maze) {
 if(Row>-1 &&  Row< Maze.getHeight()+1)
 {
 Row--;
 }
  return "X";
}

//Moves creature East
//Precondition: Creature must not be on edge of Maze
//Postcondition:Will move Creature East in maze
string Creature::goWest(Maze &Maze) {
  if(Row>-1 &&  Row< Maze.getHeight()+1)
 {
 Col--;
 }

  return "X";
}

//Moves creature West
//Precondition: Creature must not be on edge of Maze
//Postcondition:Will move Creature West in maze
string Creature::goEast(Maze &Maze) {
  if(Row>-1 &&  Row< Maze.getHeight()+1)
 {
 Col++;
 }
  return "X";
}

//Moves creature South
//Precondition: Creature must not be on edge of Maze
//Postcondition:Will move Creature North in maze
string Creature::goSouth(Maze &Maze) {
  if(Row>-1 &&  Row< Maze.getHeight()+1)
 {
 Row++;
 }
  return "X";
}
