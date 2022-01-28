//design for a ADT binary tree that contains ints and
//at creation is balanced has
//Connor Lauerman & Daniel Wang
//3/8/2021

#ifndef ASS5_BINARYTREE_H
#define ASS5_BINARYTREE_H


#include <iostream>

using namespace std;

class BinaryTree;

class BNode{
    friend class BinaryTree;

    friend ostream &operator<<(ostream &out, const BinaryTree &bin);

    public:
    //constructor
    explicit BNode(int value);

    int value{ 0 };

    BNode *left;

    BNode *right;

    bool isThread;

    bool isRightThread;

    bool isLeftThread;


};

class BinaryTree{

    //Prints to the screen the binary tree as an inorder print
    //Precondition: bin is not nullptr
    //Postcondition: to screen the binary tee is printed inOrder   
    friend ostream &operator<<(ostream &out, const BinaryTree &bin);

  
    private:

    int height;


    BNode* root;

   //Helper method for constructing tree in a binary search way
   //Precondition:front is beiging of tree and end is last digit
   //Postcondition:A binary tree is created
    BNode* Help(BNode toAdd, int front, int end);

   // Helper method for constructing tree in a binary search way
   // Precondition:front is beiging of tree and end is last digit
   // Postcondition:A binary tree is created
    BNode* Helper(int front, int end);

    // Threads a binary tree with right threads
    // Precondition:root is passed into function and not null
    // Postcondition:The binary tree becomes right threaded
    BNode* makeThreadedRight(BNode *current);

    // Threads a binary tree with left threads
    // Precondition:root is passed and is not null
    // Postcondition:The binary tree becomes threaded
    BNode* makeThreadedLeft(BNode *current);

     // Takes a node from a tree and moves to the most left postion and does not
    // traverse through threads Precondition:current is not nullptr
    // Postcondition:the node retunred is the left most of the node initially
    // passed in
    BNode* goLeft(BNode *current);

    // Takes a node from a binary tee and goes to the right most does not go
    // through threads Precondition:current in not nullptr Postcondition:node
    // passed through is returned as the most right node
    BNode* goRight(BNode *current);

    //Helper for remove if node to be removed has no thread nodes
    //Precondition: current is not nullptr
    //postcondition returns node 
    BNode* noThread(BNode* root, BNode* temp,BNode* current);
    //helper for remove if node to be removed has one thread node
    //Precondition: currnet is not null
    //Postcondition returns node
    BNode* oneThread(BNode* root, BNode* temp,BNode* current);
    
    //helper for remove if node contains both threads
    //Precondition: currnet is not null
    //Postcondition returns node
    BNode* bothThread(BNode* root,BNode* current);


    //Gets the  node above the previous
    //Precondition:currnet is not null
    //postcondition: returns the node above
    BNode *getAbove(BNode *current);
    // gets the node that is above the passed node
    // Precondition:current is not nullptr
    // Postcondition:the node that is above the current connected to current
    BNode *getBelow(BNode *current);

    // Recursive methd to make a deep copy of tree
    // Precondition:the root of the tree is passed in
    // Postcondition:A copy is created and returns the root of the copy;
    BNode* copyHelp(BNode* current);

    // Recursive method to help destruct the tree by unthreaded tree
    // Precondition:tree is threaded
    // Postcondition:tree becomes unthreaded
    void destructorHelp(BNode* current);

    // Deletes all nodes of an unthreaded tree
    // Precondition:ptr is the root of tree
    // Postcondition:every node is deleted
    void destroyTree(BNode* ptr);

    // Recursive function to get height of tree modficartion of Carno method
    // Precondition:
    // Postcondition:returns height of tree
    int getHeightHelper(BNode* subTree) const;

    // Checks the tree if an integer is containeed in the tree
    // Precondition:an int is passed in
    // Postcondition:true or false if the the int is in the tree or not
    bool contains(int n);

    
    
    public:

    //constructor
    explicit BinaryTree(int n);

    //destructor
    virtual ~BinaryTree();

    //copy constructor
    BinaryTree(const BinaryTree &other);

    
    // returns root of tree
    // Precondition:the tee is not null
    // Postcondition:root is returned
    BNode* getRoot();

    // Gets value of root
    // Precondition:root is not null
    // Postcondition:gets value of root
    int getRootData() const;

    // Checks if the tree contains any entries
    // Precondition:
    // Postcondition:true or false weather tree is empty or not
    bool isEmpty() const;

    // gets height
    // Precondition:root of tree is not nullptr
    // Postcondition:an int representing how many nodes are in the tree
    int getHeight() const;

    // get the number of nodes in the tree
    // Precondition:root is not nullptr
    // Postcondition:an int representing how many nodes are in tree
    int getNumberOfNodes();

    // Adds an an int to the tree
    // Precondition:root is not nullptr
    // Postcondition:true or flase of the node is added
    bool add(int toAdd);

    // removes node from tree
    // Precondition:toRemove is in tree
    // Postcondition:does not work well but node is removed from tree
    bool remove(int toRemove);    

    // prints the tree inOrder
    // Precondition:current is not nullptr when passed
    // Postcondition:to console the tree is printed
    void inOrder(BNode* current);


};
#endif //ASS5_BINARYTREE_H