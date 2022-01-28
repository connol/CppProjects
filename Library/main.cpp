//
// main file that will run tests for the library object class
#include "library.h"

#include <cassert>
#include <iostream>


using namespace std;

//the list of tests that will be run 
void test1() {
  Library Libs("UWB");
  Libs.addBook("Don Quixote");
  Libs.addBook("In Search of Lost Time");
  Libs.addBook("Ulysses");
  Libs.addBook("The Odyssey");
  Libs.listAllBooks();
  // should generate already in library message and return true
  bool Result = Libs.isInLibrary("The Odyssey");
  assert(Result);

  // cannot add book twice, result should be false
  Result = Libs.addBook("The Odyssey");
  assert(!Result);

  // test remove, result should be true
  Result = Libs.removeBook("The Odyssey");
  assert(Result);

  // not in library, result should be false
  Result = Libs.isInLibrary("The Odyssey");
  assert(!Result);

  // cannot remove twice, result should be false
  Result = Libs.removeBook("The Odyssey");
  int a =s
  cout<<a;asdasdsdasdasd
  assert(!Result);
}
  // calls all tests and outputs message if all tests are succesful
void testAll() {
  test1();
  cout << "Successfully completed all tests." << endl;
}
  // runs all tests 
int main() {
  testAll();
  return 0;
}