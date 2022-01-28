//Tests to be run for creature and maze objects
//Connor Lauerman
//Date: 2/7/2021
#include <iostream>
#include <cassert>
#include "creature.h"
#include "maze.h"

//Tests a standard mazes and asserts if the path is correct
//Precondition:
//Postcondition: will exit program if path is wrong
void test() {
    Maze M("maze.txt");
    // cout << m << endl;
    Creature C(4, 4);
    string Path = C.solve(M);
    cout << "Path: " <<  Path << endl;
    cout << M << endl;
    assert(Path=="EEENNNEEEEEESEESSSEEENNNNN");
}

//Tests a maze that must go in all directions and asserts if the path is correct
//Precondition:
//Postcondition: will exit program if path is wrong
void test1()
{
    Maze A("maze1.txt");
    // cout << m << endl;
    Creature C(5,20);
    string Path=C.solve(A);
    cout<< "Path: "<< Path << endl;
    cout << A << endl;
    assert(Path=="ENNNNWWWSSSSWWNNNNWWWSSSSWWNNNNWWWSSSSWWNNNNWWWSSSSWWW");
}

//Tests a maze with no exit
//Precondition:
//Postcondition: will exit program if path is wrong
void test2()
{
    Maze B("maze2.txt");
    // cout << m << endl;
    Creature C(4, 4);
    string Path = C.solve(B);
    cout << "Path: " << Path << endl;
    assert(Path=="No exit");
    cout << B << endl;
}

//Another maze to test
//Precondition:
//Postcondition: will exit program if path is wrong
void test3()
{
     Maze B("maze3.txt");
    // cout << m << endl;
    Creature C(4, 4);
    string Path = C.solve(B);
    cout << "Path: " << Path << endl;
    assert(Path=="EEEEEEEEEEENNWWNWWWWWWWWWWWSWW");
    cout << B << endl;
}
int main() {
    test();
    test1();
    test2();
    test3();
    cout << "Done!" << std::endl;
    return 0;
}