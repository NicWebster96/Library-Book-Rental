// Nicholas Webster
// Section 1
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
}

Person * searchPerson(vector<Person *> myCardholders, int id) {
  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders.at(i)->getId() == id) {
      return myCardholders.at(i);
    }
  }
  cout << "Person not found" << endl;
}


int askCardID(vector<Person *> myCardholders) {
  int cardID;

  cout << "Please enter the card ID: ";
  cin >> setw(4) >> cardID;

  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders.at(i)->getId() == cardID) {
      return cardID;
    }
  }
  return NULL;
}

int askBookID(vector<Book *> myBooks) {
  int bookID;
  cout << "Please enter the book ID: ";
  cin >> setw(5) >> bookID;

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getId() == bookID) {
      return bookID;
    }
  }
  return NULL;
}


bool outputPerson(vector<Person *> myCardholders, int id) {
  if (id == NULL) {
    cout << "Card ID not found" << endl;
    return false;
  }

  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders.at(i)->getId() == id) {
      cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;
      return true;
    }
  }
}

bool outputBook(vector<Book *> myBooks, int id) {
  if (id == NULL) {
    cout << "Book ID not found" << endl;
    return false;
  }

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks.at(i)->getId() == id) {
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      return true;
    }
  }
}

/******************************************************************************/
/* Menu functions */

// 1
void bookCheckout(vector<Book *> myBooks, vector<Person *> myCardholders,
                  int pID, int bID) {
  Person * tmpPerson = searchPerson(myCardholders, pID);

  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getId() == bID) {
      if (myBooks.at(i)->getPersonPtr() != nullptr) {
        cout << "Book already checked out" << endl;
        return;
      }
      myBooks.at(i)->setPersonPtr(tmpPerson);
      cout << "Rental Completed" << endl;
      return;
    }
  }
}

// 2
void bookReturn(vector<Book *> myBooks, int id) {
  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getId() == id) {
      myBooks.at(i)->setPersonPtr(nullptr);
      cout << "Return Completed" << endl;
      return;
    }
  }
}

// 3
void checkAvail(vector<Book *> myBooks) {
  if(myBooks.size() == 0) {
    cout << "No available books" << endl;
    return;
  }

  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() == nullptr) {
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Category: " << myBooks.at(i)->getCategory() << endl << endl;
    }
  }
}

// 4
void outputRentals(vector<Book *> myBooks) {

  int count = 0;

  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr() != nullptr) {
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;

      cout << "Cardholder: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;
      cout << "Card ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl << endl;
      count++;
    }

    if(count == 0) {
      cout << "No outstanding rentals" << endl;
      return;
    }
  }
}

// 5
void checkRental(vector<Book *> myBooks, int id) {
  for(int i=0; i<myBooks.size(); i++) {
    if (myBooks.at(i)->getPersonPtr()->getId() == id) {

      cout << "Cardholder: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;

      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
    }
  }
}

// 6
void openCard(vector<Person *> & myCardholders, int nextID) {
  string firstName, lastName;
  Person * personPtr;
  bool act = true;

  cout << "Please enter first name: ";
  cin >> firstName;
  cout << "Please enter last name: ";
  cin >> lastName;

  personPtr = new Person(nextID, act, firstName, lastName);
  myCardholders.push_back(personPtr);

  cout << "Card ID " << searchPerson(myCardholders, nextID)->getId() << " active" << endl;
  outputPerson(myCardholders, nextID);

  delete personPtr;
  return;
}

// 7
void closeCard(vector<Person *> & myCardholders, int id) {

  char answer;

  if(searchPerson(myCardholders, id)->isActive()) {
    cout << "Are you sure you want to deactivate card (y/n)? ";
    cin >> answer;

    if(answer == 'y' || 'Y') {
      searchPerson(myCardholders, id)->setActive(false);
      cout << "Card ID deactivated" << endl;
      return;
    }

    if(answer == 'n' || 'N') {
      return;
    }

    if(answer != 'y' || 'Y' || 'n' || 'N') {
      cout << "You must input either y or n" << endl;
      return;
    }
  } else {
    cout << "Card ID is already inactive" << endl;
    return;
  }
}

/******************************************************************************/
/* Initilization functions */

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> & myBooks) {
    Book * bookPtr;

    ifstream myFile("books.txt");

    string sbookID, title, author, category;

    while(myFile.good()) {
      getline(myFile, sbookID);
      getline(myFile, title);
      getline(myFile, author);
      getline(myFile, category);
      myFile >> ws;

      int bookID = stoi(sbookID);

      bookPtr = new Book(bookID, title, author, category);
      myBooks.push_back(bookPtr);
    }
    delete bookPtr;
    myFile.close();
    return;
}

int readPersons(vector<Person *> & myCardholders) {

    Person * personPtr;

    ifstream myFile("persons.txt");

    string fName, lName;
    int cardNum, act, nextID;

    while(myFile >> cardNum >> act >> fName >> lName) {
      personPtr = new Person(cardNum, act, fName, lName);
      myCardholders.push_back(personPtr);
      nextID = cardNum + 1;
    }
    delete personPtr;
    myFile.close();
    return nextID;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
  ifstream myFile("rentals.txt");

  int bookID, cardID;

  while(myFile >> bookID >> cardID) {
    searchBook(myBooks, bookID)->setPersonPtr(searchPerson(myCardholders, cardID));
  }
  myFile.close();
}

/******************************************************************************/
/* Main */

int main() {

    vector<Book *> books;
    vector<Person *> cardholders;
    int tmpBID;
    int tmpPID;

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
                tmpPID = askCardID(cardholders);

                if(outputPerson(cardholders, tmpPID)) {
                  tmpBID = askBookID(books);
                  outputBook(books, tmpBID);
                  bookCheckout(books, cardholders, tmpPID, tmpBID);
                }
                break;

            case 2:
                // Book return
                //    Asks for Book ID,
                //    if ID is not valid, returns to menu
                //    if valid, sets book personPtr to nullptr
                tmpBID = askBookID(books);
                outputBook(books, tmpBID);
                bookReturn(books, tmpBID);

                break;

            case 3:
                // View all available books
                checkAvail(books);
                break;

            case 4:
                // View all outstanding rentals
                outputRentals(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                tmpPID = askCardID(cardholders);
                outputPerson(cardholders, tmpPID);
                checkRental(books, tmpPID);

                break;

            case 6:
                // Open new library card
                openCard(cardholders, nextID);
                nextID++;
                break;

            case 7:
                // Close library card
                tmpPID = askCardID(cardholders);
                outputPerson(cardholders, tmpPID);
                closeCard(cardholders, tmpPID);
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
