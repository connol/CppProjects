/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 * also used by MemSQL
 * https://www.singlestore.com/blog/what-is-skiplist-why-skiplist-index-for-memsql/
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 *
 * 2/20/2021
 * Connor Lauerman
 */

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

// only SkipList class can create SNode objects

class SkipList;

class SNode {
  friend class SkipList;
  // writes to console the list and its layers
  // precondition: must be a valid Skiplis object
  // postcondition:the list will be wriiten to console
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // constructor
  explicit SNode(int value);

  // data contained in the object
  int value{ 0 };

  // link to Next SNode
  SNode *forward;

  // link to Prev SNode
  SNode *backward;

  // link to up node
  SNode *up;

  // link to down SNode
  SNode *down;
};

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &out, const SkipList &skip);

private:
  // maximum number of levels
  int maxLevel = 1;

  // probability of inserting at a higher level
  // as an integer between 0% and 100% (exclusive)
  int probability = 0;

  // given a SNode, place it before the given nextNode
  void addBefore(SNode *newNode, SNode *nextNode);

  // return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigher() const;

  // Checks to see whether or not a data value exists in the list
  // Returns the NODE if the value exists in the SkipList.
  // Returns nullptr otherwise
  // Precondition:data valid int
  // Postcondition:will return the node that is in the list else returns nullptr
  SNode *containsSNode(int data) const;

  // Sheilds at beginning and end that help list
  SNode **FrontGuards;
  SNode **RearGuards;

  // A helper function to remove all layers of the data
  // Precondition:Node is in skiplist
  // Postcondition: The node will be removed and return true
  bool removeHelp(SNode *toRemove);

public:
  // default SkipList has only 1 level, just one doubly-linked list
  explicit SkipList(int maxLevel = 1, int probability = 0);

  // destructor
  virtual ~SkipList();

  // copy not allowed
  SkipList(const SkipList &other) = delete;

  // move not allowed
  SkipList(SkipList &&other) = delete;

  // assignment not allowed
  SkipList &operator=(const SkipList &other) = delete;

  // move assignment not allowed
  SkipList &operator=(SkipList &&other) = delete;

  // return true if successfully added, no duplicates allowed
  // Will add one value to the list
  // Precondition:value is valid int
  // Postcondition:value will be added to list and possibly its layers and
  // return true if added else false
  bool add(int value);

  // return true if successfully added, no duplicates
  // will add multiple nodes to the list based on value in vector
  // Precondition:all values must be valid ints
  // Postcondition:values added to list in correct locations and return true if
  // added else false
  bool add(const vector<int> &values);

  // return true if successfully removed
  // will remove a value fromt the list including the layers
  // Precondition:data valid int
  // Postcondition:the data will be removed from the list including its layers
  // and return true if complted else false
  bool remove(int data);

  // return true if found in SkipList
  // Checks to see whether or not a data value exists in the list
  // Returns true if the value exists in the SkipList.
  // Returns false otherwise
  // Precondition: data is in list
  // Postcondition: will return true if is in list or false otherwise
  bool contains(int data) const;
};

#endif // ASS4_SKIPLIST_H
