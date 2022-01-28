
// modified by mashhadi on 14th feb to add an alternative op<<
// Skiplist object that holds int data members with search of O(logn)
// 2/20/2021
// Connor Lauerman

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// writes to console the list and its layers
// precondition: must be a valid Skiplis object
// postcondition:the list will be wriiten to console
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--) {
    Out << "Level: " + to_string(Index) + " -- ";
    SNode *Curr = SkipL.FrontGuards[Index];
    while (Curr != nullptr) {
      Out << to_string(Curr->value) + ", ";
      Curr = Curr->forward;
    }
    Out << "\n";
  }
  return Out;
}

// Constructor for nodes stored in list
// Precondtion: must have a int value for node to store
// Postcondition: node is created with value intialized
SNode::SNode(int value) : value{ value } {
  forward = nullptr;
  backward = nullptr;
  up = nullptr;
  down = nullptr;
}

// array of Depth SNode* objects as FrontGuards linking levels
// SNode **FrontGuards;

// array of Depth SNode* objects as RearGuards linking levels
// SNode **RearGuards;

// creates the layered skiplist object initializeing the maxLevel and the
// probablitiy of values being stored in farther layers
// Precondition:the maxLevel must be positive and probablity must be between 0
// and 100 Postcondition:List will be created with the correct amount of layers
SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{ maxLevel }, probability{ probability } {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  FrontGuards = new SNode *[maxLevel];
  RearGuards = new SNode *[maxLevel];
  for (int i = 0; i < maxLevel; i++) {
    FrontGuards[i] = new SNode(INT_MIN);
    RearGuards[i] = new SNode(INT_MAX);
    FrontGuards[i]->forward = RearGuards[i];
    RearGuards[i]->backward = FrontGuards[i];
    if (i > 0) {
      FrontGuards[i]->down = FrontGuards[i - 1];
      RearGuards[i]->down = RearGuards[i - 1];
    }
    if (i != maxLevel) {
      FrontGuards[i]->up = FrontGuards[i + 1];
      RearGuards[i]->up = RearGuards[i + 1];
    }
  }
  for (int i = 0; i < maxLevel; i++) {
    if (i > 0) {
      FrontGuards[i]->down = FrontGuards[i - 1];
      RearGuards[i]->down = RearGuards[i - 1];
    }
    if (i != maxLevel - 1) {
      FrontGuards[i]->up = FrontGuards[i + 1];
      RearGuards[i]->up = RearGuards[i + 1];
    }
  }
}

// will give true or false 50 percent of the time
// Precondition:
// Postcondition: true or false randomly
bool SkipList::shouldInsertAtHigher() const { return rand() % 2 == 1; }

// will add multiple nodes to the list based on value in vector
// Precondition:all values must be valid ints
// Postcondition:values added to list in correct locations and return true if
// added else false
bool SkipList::add(const vector<int> &values) {
  int containAll = 0;
  for (int i = 0; i < (int)values.size(); i++) {
    if (!contains(values[i])) {
      containAll++;
    }
  }
  if (containAll == (int)values.size()) {
    for (int i = 0; i < (int)values.size(); i++) {
      add(values[i]);
    }
    return true;
  } else {
    return false;
  }
}

// Will add one value to the list
// Precondition:value is valid int
// Postcondition:value will be added to list and possibly its layers and return
// true if added else false
bool SkipList::add(int newValue) {
  bool found = false;
  int level = 0;
  SNode *temp = FrontGuards[0];
  SNode *toAdd = new SNode(newValue);
  while (!found) {
    if (temp->forward->value < newValue) {
      temp = temp->forward;
    } else if (temp->forward->value == newValue) {
      found = true;
      cout << "no duplicates" << endl;
      delete toAdd;
      toAdd = nullptr;
      return false;
    } else {
      addBefore(toAdd, temp->forward);
      found = true;
    }
  }
  bool again = shouldInsertAtHigher();
  SNode *newUpper;
  if (again) {
    while (again && level != maxLevel - 1) {
      level++;
      newUpper = new SNode(newValue);
      newUpper->down = toAdd;
      toAdd->up = newUpper;
      toAdd = toAdd->backward;

      while (toAdd->up == nullptr) {

        toAdd = toAdd->backward;
      }
      toAdd = toAdd->up;
      toAdd = toAdd->forward;
      addBefore(newUpper, toAdd);
      toAdd = newUpper;
      again = shouldInsertAtHigher();
    }
  }
  return true;
}

// destructor destroys each node added to the list
SkipList::~SkipList() {
  SNode *temp = FrontGuards[maxLevel - 1];
  bool atRear;
  for (int i = 0; i < maxLevel; i++) {
    temp = FrontGuards[i];
    atRear = false;
    while (!atRear) {
      temp->up = nullptr;
      temp->down = nullptr;
      temp->backward = nullptr;
      if (temp->value != RearGuards[i]->value) {
        temp = temp->forward;
        temp->backward->forward = nullptr;
        delete temp->backward;
      } else {
        temp->forward = nullptr;
        delete temp;
        atRear = true;
        temp = nullptr;
      }
    }
  }
  delete[] RearGuards;
  delete[] FrontGuards;
  delete temp;
}

// will remove a value fromt the list including the layers
// Precondition:data valid int
// Postcondition:the data will be removed from the list including its layers and
// return true if complted else false
bool SkipList::remove(int data) {
  if (containsSNode(data)) {
    SNode *temp = containsSNode(data);
    return removeHelp(temp);
  } else {
    return false;
  }
}

// A helper function to remove all layers of the data
// Precondition:Node is in skiplist
// Postcondition: The node will be removed and return true
bool SkipList::removeHelp(SNode *toRemove) {
  if (toRemove->down == nullptr) {
    toRemove->backward->forward = toRemove->forward;
    toRemove->forward->backward = toRemove->backward;
    toRemove->down = nullptr;
    delete toRemove;
    toRemove = nullptr;
    return true;
  } else {
    removeHelp(toRemove->down);
    toRemove->backward->forward = toRemove->forward;
    toRemove->forward->backward = toRemove->backward;
    toRemove->down = nullptr;
    toRemove->up = nullptr;
    delete toRemove;
    toRemove = nullptr;
    return true;
  }
}

// Given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
  // Link next to node in front
  NewNode->forward = NextNode;
  // Link prev to node behind
  NewNode->backward = NextNode->backward;
  // Link node in back to new node
  NextNode->backward->forward = NewNode;
  // Link node in front to new node
  NextNode->backward = NewNode;
}

// Checks to see whether or not a data value exists in the list
// Returns the NODE if the value exists in the SkipList.
// Returns nullptr otherwise
// Precondition:data valid int
// Postcondition:will return the node that is in the list else returns nullptr
SNode *SkipList::containsSNode(int data) const {

  SNode *temp = FrontGuards[maxLevel - 1];
  int max = maxLevel;
  for (int i = max - 1; i >= 0; i--) {
    temp = FrontGuards[i];
    while (temp != nullptr) {
      if (temp->forward->value == data) {
        return temp->forward;
      } else if (temp->forward->value < data) {
        temp = temp->forward;
      } else {
        temp = temp->down;
      }
    }
  }
  return nullptr;
}
// Checks to see whether or not a data value exists in the list
// Returns true if the value exists in the SkipList.
// Returns false otherwise
// Precondition: data is in list
// Postcondition: will return true if is in list or false otherwise
bool SkipList::contains(int data) const {
  SNode *temp = FrontGuards[maxLevel - 1];
  int max = maxLevel;
  for (int i = max - 1; i >= 0; i--) {
    temp = FrontGuards[i];
    while (temp != nullptr) {
      if (temp->forward->value == data) {
        return true;
      } else if (temp->forward->value < data) {
        temp = temp->forward;
      } else {
        temp = temp->down;
      }
    }
  }
  return false;
}
