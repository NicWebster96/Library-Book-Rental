// Created by Nicholas Webster

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "person.cpp"
#include "book.cpp"

using namespace std;

/******************************************************************************/
/* Search, ask, and output functions for user input and console output */

Book * searchBook(vector<Book *> myBooks, int id) {
  for(int i=0; i<myBooks.size(); i++) {
      if(myBooks.at(i)->getId() == id) {
        return myBooks.at(i);
      }
  }
  cout << "Book ID not found" << endl;
  return nullptr;
}

Person * searchPerson(vector<Person *> myCardholders, int id) {
  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders.at(i)->getId() == id) {
      return myCardholders.at(i);
    }
  }
  cout << "Person not found" << endl;
  return nullptr;
}

int askCardID(vector<Person *> myCardholders) {
  int cardID;

  cout << "\nPlease enter the card ID: ";
  cin >> setw(4) >> cardID;

  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders.at(i)->getId() == cardID) {
      cout << "User: " << myCardholders.at(i)->fullName();
      return cardID;
    }
  }
  return 0;
}

int askBookID(vector<Book *> myBooks) {
  int bookID;
  cout << "\nPlease enter the book ID: ";
  cin >> setw(5) >> bookID;

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getId() == bookID) {
      cout << "Book Title: " << myBooks.at(i)->getTitle() << "\n";
      return bookID;
    }
  }
  return 0;
}

/******************************************************************************/
/* Menu functions */

// 1
void checkoutBook(int personID, int bookID, vector<Person *> myCardholders, vector<Book *> & myBooks) {
  if(personID == 0){
    cout << "No Library ID found.\n";
    return;
  }
  if(bookID == 0){
    cout << "No Book ID found.\n";
    return;
  }

  Person * tmpPerson = searchPerson(myCardholders, personID);

  for(int i=0; i<myBooks.size(); i++) {
      if (myBooks.at(i)->getId() == bookID) {
        if (myBooks.at(i)->getPersonPtr() != nullptr) {
          cout << "Book already checked out\n";
          return;
        }
        myBooks.at(i)->setPersonPtr(tmpPerson);
        cout << "\nRental Completed!\n";
        return;
      }
  }
}

// 2
void returnBook(int bookID, vector<Book *> & myBooks) {
  if(bookID == 0){
    cout << "No Book ID found.";
    return;
  }

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getId() == bookID) {
      cout << "User: " << myBooks.at(i)->getPersonPtr()->fullName();
      myBooks.at(i)->setPersonPtr(nullptr);
      cout << "\nReturn Completed!";
      return;
    }
  }
  cout << "No Book Found\n";
  return;
}

// 3
void outputAvailBooks(vector<Book *> myBooks) {
  if(myBooks.size() == 0) {
    cout << "No available books" << endl;
    return;
  }

  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() == nullptr) {
      cout << "\nBook ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Category: " << myBooks.at(i)->getCategory() << endl;
    }
  }
}

// 4
void outputRentals(vector<Book *> myBooks) {

  int count = 0;

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getPersonPtr() != nullptr) {
      cout << "\n\nBook ID: " << myBooks.at(i)->getId();
      cout << "\nTitle: " << myBooks.at(i)->getTitle();
      cout << "\nAuthor: " << myBooks.at(i)->getAuthor();
      cout << "\nCardholder: " << myBooks.at(i)->getPersonPtr()->fullName();
      cout << "\nCard ID: " << myBooks.at(i)->getPersonPtr()->getId();
      count++;
    }
  }
  if(count == 0) {cout << "No outstanding rentals\n";}
  return;
}

// 5
void checkRental(int personID, vector<Book *> myBooks, vector<Person *> myCardholders) {

  if(personID == 0){
    cout << "No Library ID found.\n";
    return;
  }

  int count = 0;

  for(int i=0; i<myBooks.size(); i++) {
    if((myBooks.at(i)->getPersonPtr() != nullptr) &&
      (myBooks.at(i)->getPersonPtr()->getId() == personID) &&
      (myBooks.at(i)->getPersonPtr()->isActive())) {
        cout << "\n\nBook ID: " << myBooks.at(i)->getId();
        cout << "\nTitle: " << myBooks.at(i)->getTitle();
        cout << "\nAuthor: " << myBooks.at(i)->getAuthor();
        count++;
    }
  }
    if(count > 0){return;}
    cout << "No books currently checked out";
}

// 6
void openCard(vector<Person *> & myCardholders, int nextID) {
  string firstName, lastName;
  Person * personPtr;
  bool act = true;

  cout << "\nPlease enter first name: ";
  cin >> firstName;
  cout << "Please enter last name: ";
  cin.ignore();
  cin >> lastName;

  personPtr = new Person(nextID, act, firstName, lastName);
  myCardholders.push_back(personPtr);

  cout << myCardholders.back()->getLastName() << "(Card ID " <<
          myCardholders.back()->getId() << ") is now active";

  delete personPtr;
  return;
}

// 7
void closeCard(Person *tmpPerson) {

  char response;

  if(tmpPerson->isActive()) {
    cout << "Are you sure you want to deactivate card (y/n)? ";
    cin >> response;

    switch(response) {
      case 'y':
          tmpPerson->setActive(false);
          cout << "Card ID deactivated" << endl;
          break;
      case 'n':
          cout << tmpPerson->fullName() << "\'s account will remain active";
          break;
      default:
          cout << "Please enter \'y\' or \'n\'\n";
    }
  } else {
    cout << tmpPerson->fullName() << "\'s account is currently inactive\n";
    return;
  }
  return;
}

// 8
void update(vector<Person *> myCardholders, vector<Book *> myBooks) {
  ofstream myPFile("persons.txt");

  std::cout <<  myCardholders.size()<< '\n';
  for(int i = 0; i < myCardholders.size(); i++) {
    myPFile << myCardholders.at(i)->getId() << " "
            << myCardholders.at(i)->isActive() << " "
            << myCardholders.at(i)->fullName() << endl;
  }
  myPFile.close();

  ofstream myRFile("rentals.txt");

  for(int i = 0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getPersonPtr() != nullptr) {
      myRFile << myBooks.at(i)->getId() << " "
              << myBooks.at(i)->getPersonPtr()->getId() << endl;
    }
  }
  myRFile.close();

}

/******************************************************************************/
/* Initilization functions */

void printMenu() {
    cout << "\n----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system\n\n";
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> & myBooks) {

    string sbookID, title, author, category;
    ifstream myFile("books.txt");

    while(myFile.good()) {
      getline(myFile, sbookID);
      getline(myFile, title);
      getline(myFile, author);
      getline(myFile, category);
      myFile >> ws;

      int bookID = stoi(sbookID);

      Book * bookPtr = new Book(bookID, title, author, category);
      myBooks.push_back(bookPtr);
    }
    myFile.close();
    return;
}

int readPersons(vector<Person *> & myCardholders) {

    string fName, lName;
    int cardNum, act, nextID;
    ifstream myFile("persons.txt");

    if(!myFile) {
      cout << "Unable to open file";
      exit(1);
    }

    while(myFile >> cardNum >> act >> fName >> lName) {
      Person * personPtr = new Person(cardNum, act, fName, lName);
      myCardholders.push_back(personPtr);
    }

    nextID = cardNum + 1;
    myFile.close();
    return nextID;
}

void readRentals(vector<Book *> myBooks, vector<Person *> myCardholders) {
  ifstream myFile;
  int bookID, cardID;

  myFile.open("rentals.txt");
  if(!myFile) {
    cout << "Unable to open file";
    exit(1);
  }

  while(myFile >> bookID >> cardID) {
    searchBook(myBooks, bookID)->setPersonPtr(searchPerson(myCardholders, cardID));
  }
  myFile.close();
}

/******************************************************************************/

int main() {

    vector<Book *> books;
    vector<Person *> cardholders;

    int nextID = readPersons(cardholders);
    readBooks(books);
    readRentals(books, cardholders);

    int choice;
    do
    {
        printMenu();
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                // Book checkout
                //    Asks user for ID,
                //    if ID is not valid, does not ask for Book ID
                //    if valid, gets Book ID and sets personPtr
                checkoutBook(askCardID(cardholders), askBookID(books), cardholders, books);
                break;

            case 2:
                // Book return
                //    Asks for Book ID,
                //    if ID is not valid, returns to menu
                //    if valid, sets book personPtr to nullptr
                returnBook(askBookID(books), books);
                break;

            case 3:
                // View all available books
                outputAvailBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                outputRentals(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                checkRental(askCardID(cardholders), books, cardholders);
                break;

            case 6:
                // Open new library card
                openCard(cardholders, nextID);
                nextID++;
                break;

            case 7:
                // Close library card
                closeCard(searchPerson(cardholders, askCardID(cardholders)));
                break;

            case 8:
                // Must update records in files here before exiting the program
                update(cardholders, books);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
