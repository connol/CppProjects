//Runs tests for binary tree
#include <cassert>
#include <iostream>

#include "binarytree.h"

using namespace std;
//Asks for a number to give and if a number isnt given will repromt
int askForNumber()
{
    int n;
    cout << "Give number to create binary tree"<<endl;
    cin>> n;
    while(cin.fail())
    {
        cout << "Give number to create binary tree"<<endl;
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>n;
    }
    return n;
} 
//test for remove and copy constructor
void test1()
{
    int n= askForNumber();
    BinaryTree t=BinaryTree(n);
    BinaryTree copy=BinaryTree(t);
    cout<<t<<endl;
    cout<<"tree inOrder"<<endl;
    t.inOrder(t.getRoot());
    cout<<"copy inorder"<<endl;
    copy.inOrder(copy.getRoot());
    copy.remove(n);
    cout<<"original binary"<<endl;
    t.inOrder(t.getRoot());
    cout<<"copy of binary"<<endl;
    copy.inOrder(copy.getRoot());
    bool isEmpty;
    isEmpty=t.isEmpty();
    assert(isEmpty==false);
    cout<<t.getHeight()<<endl;
    int numberofnodes = t.getNumberOfNodes();
    assert(numberofnodes==n);
}
//More tests of binary tree
void test2()
{

    int i = askForNumber();
    bool isEmpty;
    BinaryTree d=BinaryTree(i);
    d.inOrder(d.getRoot());
    isEmpty=d.isEmpty();
    assert(isEmpty==false);
    cout<<d.getHeight()<<endl;
    int numberofnodes = d.getNumberOfNodes();
    assert(numberofnodes=i);
    

}
//Runs the test for bianry tree
int main()
{
    //test2();
    test1();
    return 0;
}