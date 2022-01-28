#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

// File to test skip list object and its functions
// 2/20/2021
// Connor Lauerman

// will test a 5 layered skip list
void test1() {
  // setting seed for easy testing
  srand(10000);
  SkipList skp(5, 80);
  cout << boolalpha;
  skp.add(3);
  skp.add(5);
  skp.add(vector<int>{ 1, 7, 9 });
  // cannot add existing
  assert(!skp.add(vector<int>{ 1, 7 }));
  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}

// Will test a 4 layered skip list and its methods
void test2() {
  SkipList s(4, 2);
  assert(s.add(5));
  s.add(10);
  s.add(7);
  s.add(10); // duplicate
  s.add(2);
  s.add(100);
  s.add(39);
  for (int i = 100; i < 125; i++) {
    s.add(i);
  }
  assert(s.contains(10));
  assert(!s.contains(3));
  cout << s;
  assert(s.remove(10));
  assert(s.remove(5));
  assert(!s.remove(3));
}

// will test a 10 layered skip list and its methods
void test3() {
  SkipList large(10, 50);
  assert(large.add(32));
  large.add(29);
  large.add(10);
  large.add(11);
  large.add(13);
  large.add(13);
  assert(!large.add(13));
  large.add(12);
  large.add(vector<int>{ 1, 7 });
  large.add(vector<int>{ 9, 7 });
  for (int i = 100; i < 125; i++) {
    large.add(i);
  }
  assert(large.contains(32));
  assert(!large.contains(21));
  cout << large;
  assert(large.remove(29));
  cout << large;
  large.remove(111);
  large.remove(115);
  large.remove(101);
  large.remove(105);
  large.remove(-10);
  large.remove(10);
}

// will test a 1 layered skip list and its methods
void test4() {
  SkipList s(1, 10);
  assert(s.add(10));
  s.add(100);
  cout << s;
  assert(s.remove(10));
  assert(s.contains(100));
  assert(!s.contains(3));
  cout << s;
}
// runs the tests for skip list if they run correctly will print done
int main() {
  test1();
  test2();
  test3();
  test4();
  cout << "Done." << endl;
  return 0;
}