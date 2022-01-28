//Implementation of binary tree that is binary search tree that is threaded
//at creation is balanced has
//Connor Lauerman & Daniel Wang
//3/8/2021

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "binarytree.h"

using namespace std;

//Prints to the screen the binary tree as an inorder print
//Precondition: bin is not nullptr
//Postcondition: to screen the binary tee is printed inOrder
ostream &operator<<(ostream &out, const BinaryTree &bin) {
  BNode *current = bin.root;
  while (current->isThread == false && current->left != nullptr) {

    current = current->left;
  }
  while (current->right != nullptr) {

    out << current->value << " ";
    if (current->isThread) {

      current = current->right;
    } else {
      current=current->right;
      while (current->isThread == false && current->left != nullptr) {

        current = current->left;
      }
    }
    
  }
  out << current->value;
    return out;
  }

  BNode::BNode(int value) : value{ value } {
    left = nullptr;
    right = nullptr;
  }

  // Constructor
  // Precondition:An int is passed into the function
  // Postcondition:The binary tree is created with left and right threads
  BinaryTree::BinaryTree(int n) {
    // root = new BNode(n/2);
    root = Helper(1, n);
    makeThreadedRight(root);
    makeThreadedLeft(root);
  }

  // copy constructor
  BinaryTree::BinaryTree(const BinaryTree &other) {
    root = copyHelp(other.root);
    makeThreadedRight(root);
    makeThreadedLeft(root);
  }
  // Recursive methd to make a deep copy of tree
  // Precondition:the root of the tree is passed in
  // Postcondition:A copy is created and returns the root of the copy;
  BNode *BinaryTree::copyHelp(BNode * current) {
    if (current != nullptr) {
      if ((current->isRightThread && current->isLeftThread)) {
        BNode *toAdd = new BNode(current->value);
        return toAdd;
      } else if (current->isRightThread) {
        BNode *toAdd = new BNode(current->value);
        if (current->left != nullptr) {
          toAdd->left = copyHelp(current->left);
        }
        return toAdd;
      } else if (current->isLeftThread) {
        BNode *toAdd = new BNode(current->value);
        toAdd->right = copyHelp(current->right);
        return toAdd;
      } else {
        BNode *toAdd = new BNode(current->value);
        if (current->left != nullptr) {
          toAdd->left = copyHelp(current->left);
        }
        toAdd->right = copyHelp(current->right);
        return toAdd;
      }
    } else {
      return nullptr;
    }
  }

  // Recursive method to help destruct the tree by unthreaded tree
  // Precondition:tree is threaded
  // Postcondition:tree becomes unthreaded
  void BinaryTree::destructorHelp(BNode * current) {
    if (current != nullptr) {
      if ((current->isRightThread && current->isLeftThread)) {
        if (current->isRightThread && current->isLeftThread) {
          current->left = nullptr;
          current->right = nullptr;
        }
      } else if (current->isRightThread) {
        current->right = nullptr;
        destructorHelp(current->left);
      } else if (current->isLeftThread) {
        current->left = nullptr;
        destructorHelp(current->right);
      } else {
        destructorHelp(current->left);
        destructorHelp(current->right);
      }
    }
  }

  // Deletes all nodes of an unthreaded tree
  // Precondition:ptr is the root of tree
  // Postcondition:every node is deleted
  void BinaryTree::destroyTree(BNode * ptr) {
    if (ptr != nullptr) {
      destroyTree(ptr->left);
      destroyTree(ptr->right);
      ptr->left = nullptr;
      ptr->right = nullptr;
      delete ptr;
      ptr = nullptr;
    }
  }

  // destructor
  BinaryTree::~BinaryTree() {
    if (root->left == nullptr) {
      if (root->right == nullptr) {
        delete root;
      } else {
        root->right->left = nullptr;
        root->right->right = nullptr;
        delete root->right;
        root->right = nullptr;
        delete root;
        root = nullptr;
      }
    } else {
      
      destructorHelp(root);
      destroyTree(root);
    }
  }

  // Helper method for constructing tree in a binary search way
  // Precondition:front is beiging of tree and end is last digit
  // Postcondition:A binary tree is created
  BNode *BinaryTree::Helper(int front, int end) {
    if (front > end) {
      return nullptr;
    } else {
      int mid = (front + end) / 2;
      BNode *toAdd = new BNode(mid);

      toAdd->left = Helper(front, mid - 1);

      toAdd->right = Helper(mid + 1, end);

      return toAdd;
    }
  }

  // Threads a binary tree with right threads
  // Precondition:root is passed into function and not null
  // Postcondition:The binary tree becomes right threaded
  BNode *BinaryTree::makeThreadedRight(BNode * current) {
    if (current->left == nullptr && current->right == nullptr) {
      return current;
    }
    if (current->left != nullptr) {
      BNode *thread = makeThreadedRight(current->left);
      thread->right = current;
      thread->isThread = true;
      thread->isRightThread = true;
    }

    if (current->right == nullptr) {
      return current;
    }
    return makeThreadedRight(current->right);
  }

  // Threads a binary tree with left threads
  // Precondition:root is passed and is not null
  // Postcondition:The binary tree becomes threaded
  BNode *BinaryTree::makeThreadedLeft(BNode * current) {
    if (current->left == nullptr && current->isThread == true) {
      return current;
    }
    if (current->right != nullptr) {
      BNode *thread = makeThreadedLeft(current->right);
      thread->left = current;
      thread->isThread = true;
      thread->isLeftThread = true;
    }
    if (current->left == nullptr) {
      return current;
    }
    return makeThreadedLeft(current->left);
  }

  // Takes a node from a tree and moves to the most left postion and does not
  // traverse through threads Precondition:current is not nullptr
  // Postcondition:the node retunred is the left most of the node initially
  // passed in
  BNode *BinaryTree::goLeft(BNode * current) {
    if (current == nullptr) {
      return nullptr;
    } else {
      while (current->isLeftThread == false && current->left != nullptr) {

        current = current->left;
      }
      return current;
    }
  }

  // Takes a node from a binary tee and goes to the right most does not go
  // through threads Precondition:current in not nullptr Postcondition:node
  // passed through is returned as the most right node
  BNode *BinaryTree::goRight(BNode * current) {
    if (current == nullptr) {
      return nullptr;
    } else {
      while (current->isThread == false && current->right != nullptr) {

        current = current->right;
      }
      return current;
    }
  }

  // returns root of tree
  // Precondition:the tee is not null
  // Postcondition:root is returned
  BNode *BinaryTree::getRoot() { return root; }

  // Gets value of root
  // Precondition:root is not null
  // Postcondition:gets value of root
  int BinaryTree::getRootData() const { return root->value; }

  // Checks if the tree contains any entries
  // Precondition:
  // Postcondition:true or false weather tree is empty or not
  bool BinaryTree::isEmpty() const {
    if (root != nullptr) {
      return false;
    }
    { return true; }
  }
  // Recursive function to get height of tree modficartion of Carno method
  // Precondition:
  // Postcondition:returns height of tree
  int BinaryTree::getHeightHelper(BNode * subTree) const {
    if (subTree == nullptr || subTree->isThread) {
      if (subTree == nullptr) {
        return 0;
      } else {
        return 1;
      }
    } else {

      return 1 + max(getHeightHelper(subTree->left),
                     getHeightHelper(subTree->right));
    }
  }

  // gets height
  // Precondition:root of tree is not nullptr
  // Postcondition:an int representing how many nodes are in the tree
  int BinaryTree::getHeight() const { return getHeightHelper(root); }

  // get the number of nodes in the tree
  // Precondition:root is not nullptr
  // Postcondition:an int representing how many nodes are in tree
  int BinaryTree::getNumberOfNodes() {
    int count = 0;
    BNode *other = goLeft(root);

    while (other->right != nullptr) {

      count++;

      if (other->isThread) {

        other = other->right;
      } else {

        other = goLeft(other->right);
      }
    }
    count++;
    return count;
  }

  // Adds an an int to the tree
  // Precondition:root is not nullptr
  // Postcondition:true or flase of the node is added
  bool BinaryTree::add(int toAdd) {
    if (contains(toAdd)) {
      return false;
    } else if (root->value > toAdd) {
      BNode *other = goLeft(root);
      while (other->right->isThread == false) {
        other = other->right;
      }
      other = other->right;
      if (other->left->isThread == false) {
        BNode *temp = new BNode(toAdd);
        temp->left = other->left;
        other->left = temp;
        temp->right = other;
        temp->isThread = true;
        if (other->right->isThread == false) {
        } else {
          other->isThread = false;
        }

        return true;
      } else {
        BNode *temp = new BNode(toAdd);
        temp->right = other->right;
        other->right = temp;
        temp->left = other;
        temp->isThread = true;
        if (other->left->isThread == false) {
        } else {
          other->isThread = false;
        }
        return true;
      }
    } else {
      BNode *other = goRight(root);
      while (other->left->isThread == false) {
        other = other->left;
      }
      other = other->left;
      if (other->left->isThread == false) {
        BNode *temp = new BNode(toAdd);
        temp->left = other->left;
        other->left = temp;
        temp->right = other;
        temp->isThread = true;
        if (other->right->isThread == false) {
        } else {
          other->isThread = false;
        }
        return true;
      } else {
        BNode *temp = new BNode(toAdd);
        temp->right = other->right;
        other->right = temp;
        temp->left = other;
        temp->isThread = true;
        if (other->left->isThread == false) {
        } else {
          other->isThread = false;
        }
        return true;
      }
    }
  }
  // removes node from tree
  // Precondition:toRemove is in tree
  // Postcondition:does not work well but node is removed from tree
  bool BinaryTree::remove(int toRemove) {
    if(root->right!=nullptr)
    {
      root->isRightThread=false;
    }
    if(root->left!=nullptr)
    {
      root->isLeftThread=false;
    }

    
    BNode* current = root;

    bool found = false;

    while (current != nullptr) {
      if (toRemove == current->value) {
        found = true;
        break;
      }
      if (toRemove < current->value) {
        if (current->isLeftThread == false) {
          current = current->left;
        } else {
          break;
        }
      } else {
        if (current->isRightThread == false) {
          current = current->right;
        } else {
          break;
        }
      }
    }
    
    BNode* above = getAbove(current);
    if (found == false) {

      cout << "value not in tree" << endl;
    }

    else if (current->isLeftThread == false && current->isRightThread == false) {
      noThread(root, above, current);
    }

    else if (current->isLeftThread == false) {
      oneThread(root, above, current);
    }
    else if (current->isRightThread == false) {
      oneThread(root,above, current);
    }
    else {
      bothThread(root, current);
    }

    return found;
  }

//Helper for remove if node to be removed has no thread nodes
//Precondition: current is not nullptr
//postcondition returns node
  BNode *BinaryTree::noThread(BNode * ptr, BNode * temp, BNode * current) {
    if (temp == nullptr) {
      destructorHelp(root);
      destroyTree(root);
      ptr = nullptr;
    }
    else if (current == temp->left) {
      temp->isLeftThread = true;
      temp->left = current->left;
    } else {
      temp->isRightThread = true;
      temp->right = current->right;
    }
    delete current;
    current = nullptr;
    return ptr;
  }

  //helper for remove if node to be removed has one thread node
  //Precondition: currnet is not null
  //Postcondition returns node
  BNode *BinaryTree::oneThread(BNode * ptr, BNode * temp, BNode * current) {
    BNode *nonThread;
    if (current->isLeftThread == false) {
      nonThread = current->left;

    }
    else {
      nonThread = current->right;
    }
    if (temp == nullptr) {
      ptr = nonThread;
    }
    else if (current == temp->left) {
      temp->left = nonThread;
    } else {
      temp->right = nonThread;
    }
    BNode *below = getBelow(current);
    BNode *above = getAbove(current);
    if (current->isLeftThread == false) {
      if(above->left==current)
      {
        above->left=current->left;
      }
    }
    else {
      if (below == nullptr) {

      } else if (current->isRightThread == false) {
        if(above->right==current){
        above->right=current->right;
        }
          }
        
        }
      
    
    delete current;
    current = nullptr;
    return ptr;
  }

//Gets the  node above the previous
//Precondition:currnet is not null
//postcondition: returns the node above
  BNode *BinaryTree::getAbove(BNode * current) {
    BNode* toReturn = root;
    BNode* stop = root;
  cout<<current->value<<endl;
  if(current->right==nullptr)
  {
    return current->left;
  }
   if(current->value < root->value)
   {
     if(stop->left==current)
     {
       return toReturn;
     }
     stop=stop->left;
     toReturn=stop;
      while(stop->value != current->value)
      {
        toReturn=stop;
        if(current->value>stop->value)
        {
          stop=stop->right;
        }
        else
        {
          stop=stop->left;
        }
      }
      return toReturn;
   }
   else if(current->value>root->value)
   {
     if(stop->right==current)
     {
       return toReturn;
     }
     stop=stop->right;
     toReturn=stop;
     while(stop!=current)
     {
       toReturn=stop;
       if(current->value>stop->value)
       {
         stop=stop->right;
       }
       else
       {
         stop=stop->left;
       }
       
     }
     return toReturn;
   }
   else 
   {
     cout<<"root removal "<<endl;
     return nullptr;
   }
  }
  
  // gets the node that is above the passed node
  // Precondition:current is not nullptr
  // Postcondition:the node that is above the current connected to current
  BNode *BinaryTree::getBelow(BNode * current) {
   if(!current->isLeftThread && !current->isRightThread)
   {
     if(current->value<=root->value)
     {
       return current->right;
     }
     else
     {
       return current->left;
     }
   }
   else if(current->isRightThread && current->isLeftThread)
   {
     if(current->value<=root->value)
     {
       return current->right;
     }
     else
     {
       return current->left;
     }
   }
   else if(current->isLeftThread)
   {
     return current->right;
   }
   else
   {
     return current->left;
   }
  }
  //helper for remove if node contains both threads
  //Precondition: currnet is not null
  //Postcondition returns node
  BNode *BinaryTree::bothThread(BNode * ptr, BNode * current) {
    BNode *tempBelow = current;
    BNode *below = current->right;
    while (below->isLeftThread) {
      tempBelow = below;
      below = below->left;
    }

    current->value = below->value;

    if (below->isLeftThread&& below->isRightThread) {
      ptr = noThread(root, tempBelow, below);
    } else {
     ptr = oneThread(root, tempBelow, below);
    }

    return ptr;
  }

  // prints the tree inOrder
  // Precondition:current is not nullptr when passed
  // Postcondition:to console the tree is printed
  void BinaryTree::inOrder(BNode * current) {
    BNode *other = goLeft(current);

    while (other->right != nullptr) {

      cout << other->value <<",";
  
      if (other->isRightThread) {

        other = other->right;
      } else {

        other = goLeft(other->right);
      }
    }
    cout << other->value << endl;
  }

  // Checks the tree if an integer is containeed in the tree
  // Precondition:an int is passed in
  // Postcondition:true or false if the the int is in the tree or not
  bool BinaryTree::contains(int n) {
    if (root->value == n) {
      return true;
    } else if (root->value < n) {
      bool cont = true;
      BNode *other = goLeft(root);

      while (other->right != nullptr && cont) {
        if (other->value == n) {
          return true;
        }

        if (other->isThread) {

          other = other->right;
        } else {

          other = goLeft(other->right);
        }
      }
      if (other->value == n) {
        return true;
      } else {
        return false;
      }
    } else {
      bool cont = true;
      BNode *other = goRight(root);

      while (other->left != nullptr && cont) {
        if (other->value == n) {
          return true;
        }

        if (other->isThread) {

          other = other->left;
        } else {

          other = goRight(other->left);
        }
      }

      if (other->value == n) {
        return true;
      } else {
        return false;
      }
    }
  }

