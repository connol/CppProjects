
//
// Created by Connor Lauerman on 1/10/2021.
//
// Library class demonstrating partially filled arrays
// Can add/remove books from library
// findbooks in library
//list all book in library

#include "library.h"
#include <iostream>

// constructor with default name 
//inputs:
// name: will name the libray, type string
Library::Library(const string &Name)
{
  Library::name = Name 
  numberOfBooks = 0;
}

// destructor
// nothing on heap
Library::~Library()
{
  // destructor
}

//checks to see if the book is in the library
//input:
//BookName: string for the name of the book
//output:
//false or true based on if the book is in library or not
bool Library::isInLibrary(const string &BookName) const
{
  int i = 0;
  i = findBook(BookName);
  if (i == -1)
  {
    cout << "Book not in library" << endl;
    return false;
  }
  else
  {
    cout << "Book is already in library" << endl;
    return true;
  }
}

// add a new book to library
// input: BookName:as string for name of book to be added
//output true or false if the book is added or not
bool Library::addBook(const string &BookName)
{
  if(numberOfBooks==100)
  {
    cout << "library full book not added" << endl;
    return false;
  }
  int index = 0;
  index = findBook(BookName);
  if (index == -1)
  {
    books[Library::numberOfBooks] = BookName;
    Library::numberOfBooks++;
    return true;
  }
  else
  {
    return false;
  }
}

// remove a book from library
// input:BookName:string for name of book to be removed
//Output: true or false based on if the book is removed or not
bool Library::removeBook(const string &BookName)
{
  int index = 0;
  index = findBook(BookName);
  if (index == -1)
  {
    cout << "Book not in library cannot remove" << endl;
    return false;
  }
  else
  {
    string temp = Library::books[numberOfBooks - 1];
    Library::books[index] = "";
    Library::books[index] = temp;
    numberOfBooks--;
    cout << "Book removed" << endl;
    return true;
  }
  return false;
}

// lists all books
//output: writes to console the name of all books in the library
void Library::listAllBooks() const
{
  cout << *this;
}

// finds a book by name in a library and returns the index of that book, will return -1
// if book is not in library
//Input:Bookname: string of the book to be found in library
//output: int for the index of the book in the library
int Library::findBook(const string &Bookname) const
{
  int index = -1;
  for (int i = 0; i < Library::numberOfBooks; i++)
  {
    if (Bookname == books[i])
    {
      index = i;
      return index;
    }
  }
  return index;
}
// gets the number of books in the library
//output: int for the amount of books in the library
int Library::getNumberOfBooks() const
{
  return Library::numberOfBooks;
}

// overloadsthe << operator to write all book names currently in the library
//input:out ostream
//Lib:object that the operator will overload for
ostream &operator<<(ostream &Out, const Library &Lib)
{

  for (int i = 0; i < Lib.getNumberOfBooks(); i++)
  {
    cout << Lib.books[i] << " ";
  }
  cout << endl;
  return Out;
}