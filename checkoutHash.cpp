// Created by Nicholas Webster

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

// Global Constant
const int HASH_SIZE = 10;
const int ID_LENGTH = 4;
const int ID_MIN = 1000;

/******************************************************************************/
/* Ask, search, and output functions */
   // Within the book and person functions, the input is taken from the user and
   // the multimap is searched for the corresponding ID. In the event that the
   // ID is already known, the overloaded function will not ask for an ID.

Book * askForIdRetBookPtr(multimap<int, Book *> myBooks) {

  int bookID;

  cout << "\nPlease enter the book ID: ";
  cin >> setw(ID_LENGTH) >> bookID;

  int mapKey = bookID % HASH_SIZE;
  auto mapIter = myBooks.equal_range(mapKey);

  for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
    auto const& item = vecIter->second;
    if(item->getId() == bookID) {
      // return pointer to the book
      return item;
    }
  }

  cout << "Book ID not found" << endl;
  return nullptr;
}

Book * askForIdRetBookPtr(multimap<int, Book *> myBooks, int bookID) {

  int mapKey = bookID % HASH_SIZE;
  auto mapIter = myBooks.equal_range(mapKey);

  for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
    auto const& item = vecIter->second;
    if(item->getId() == bookID) {
      // return pointer to the book
      return item;
    }
  }

  cout << "Book ID not found" << endl;
  return nullptr;
}

Person * askForIdRetPersonPtr(multimap<int, Person *> myCardholders) {

  int personID;

  cout << "\nPlease enter your library ID: ";
  cin >> setw(ID_LENGTH) >> personID;

  int mapKey = personID % HASH_SIZE;
  auto mapIter = myCardholders.equal_range(mapKey);

  for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
    auto const& item = vecIter->second;
    if(item->getId() == personID) {
      // return pointer to the person
      return item;
    }
  }

  cout << "\nPerson not found" << endl;
  return nullptr;
}

Person * askForIdRetPersonPtr(multimap<int, Person *> myCardholders, int personID) {

  int mapKey = personID % HASH_SIZE;
  auto mapIter = myCardholders.equal_range(mapKey);

  for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
    auto const& item = vecIter->second;
    if(item->getId() == personID) {
      // return pointer to the person
      return item;
    }
  }

  cout << "\nPerson not found" << endl;
  return nullptr;
}

void printBookInfo(Book * tmpBook, int amtOfInfo) {
  // If the user's Card ID and name are desired, pass in 5 for amtOfInfo.
  // If the book's info including category are desired, pass in 4.
  // If just the ID, Title, and Author are desired, pass in 3.
  cout << "\n   Book ID: " << tmpBook->getId();
  cout << "\n     Title: " << tmpBook->getTitle();
  cout << "\n    Author: " << tmpBook->getAuthor();

  if(amtOfInfo == 4) {
    cout << "\n  Category: " << tmpBook->getCategory() << "\n";
  }

  if(amtOfInfo == 5) {
    cout << "\nCardholder: " << tmpBook->getPersonPtr()->fullName();
    cout << "\n   Card ID: " << tmpBook->getPersonPtr()->getId() << "\n";
  }
  return;
}

/******************************************************************************/
/* Menu functions */

// 1
void checkoutBook(Person * tmpPerson, Book * tmpBook) {
  if(tmpPerson == nullptr || tmpBook == nullptr){return;}

  if(tmpBook->getPersonPtr() != nullptr) {
    cout << "\nBook already checked out!";
    return;
  }

  tmpBook->setPersonPtr(tmpPerson);
  cout << "\nCheckout Completed!\n";
  cout << tmpBook->getPersonPtr()->fullName() << " has checked out ";
  cout << tmpBook->getTitle();
}

// 2
void returnBook(Book * tmpBook) {
  if(tmpBook == nullptr){return;}

  if(!tmpBook->getPersonPtr()) {
    cout << "\nBook is not checked out";
    return;
  }

  cout << "\nUser: " << tmpBook->getPersonPtr()->fullName();
  cout << "\nBook: " << tmpBook->getTitle();
  tmpBook->setPersonPtr(nullptr);
  cout << "\nReturn Completed!";
}

// 3
void printAllAvailableBooks(multimap<int, Book *> myBooks) {
  if(myBooks.empty()) {
    cout << "No available books" << endl;
    return;
  }

  // Iterate through entire book multimap. If the book is available,
  // prints the book information
  for(int i = 0; i < HASH_SIZE; ++i) {
    auto mapIter = myBooks.equal_range(i);
    for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
      auto const& item = vecIter->second;
      if(item->getPersonPtr() == nullptr) {
        printBookInfo(item, 4);
      }
    }
  }
}

// 4
void printAllRentedBooks(multimap<int, Book *> myBooks) {

  int count = 0;

  for(int i = 0; i < HASH_SIZE; ++i) {
    auto mapIter = myBooks.equal_range(i);
    for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
      auto const& item = vecIter->second;
      if(item->getPersonPtr() != nullptr) {
        printBookInfo(item, 5);
        count++;
      }
    }
  }
  if(count == 0) {cout << "\nNo outstanding rentals";}
  return;
}

// 5
void printPersonsRentals(Person * tmpPerson, multimap<int, Book *> myBooks) {

  if(tmpPerson == nullptr){return;}

  cout << "\nBooks checked out for " << tmpPerson->fullName() << ":";

  int count = 0;

  for(int i = 0; i < HASH_SIZE; ++i) {
    auto mapIter = myBooks.equal_range(i);
    for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
      auto const& item = vecIter->second;
      if(item->getPersonPtr() == tmpPerson) {
        printBookInfo(item, 5);
        count++;
      }
    }
  }

  if(count == 0){
    cout << "\nNo books currently checked out";
  }
}

// 6
void openCard(multimap<int, Person *> & myCardholders, int nextID) {
  string firstName, lastName;
  Person * personPtr;
  bool act = true;
  int mapKey = nextID % HASH_SIZE;

  cout << "\nPlease enter first name: ";
  cin >> firstName;
  cin.ignore();
  cout << "Please enter last name: ";
  cin >> lastName;

  personPtr = new Person(firstName, lastName, nextID, act);
  myCardholders.insert(pair<int, Person *>(mapKey, personPtr));
  delete personPtr;

  auto mapIter = myCardholders.equal_range(mapKey);
  auto vecIter = mapIter.first;
  auto item = vecIter->second;
  while(vecIter != mapIter.second) {
    item = vecIter->second;
    vecIter++;
  }

  cout << "\n" << item->fullName() << " (Card ID " << item->getId() <<
          ") is now active";

  return;
}

// 7
void deactivateCard(Person * tmpPerson) {

  char response;

  if(tmpPerson->isActive()) {
    cout << "Are you sure you want to deactivate card (y/n)? ";
    cin >> response;

    switch(response) {
      case 'y':
          tmpPerson->setActive(false);
          cout << tmpPerson->fullName() <<  " (Card ID: "
               << tmpPerson->getId() << ") deactivated.";
          break;
      case 'n':
          cout << tmpPerson->fullName() << "\'s account will remain active.";
          break;
      default:
          cout << "Please enter \'y\' or \'n\'\n";
    }
  } else {
    cout << "ERROR: ";
    cout << tmpPerson->fullName() << "\'s account is already inactive!";
  }

}

// 8
void update(multimap<int, Person *> myCardholders, multimap<int, Book *> myBooks) {

  // Writing to persons.txt file
  ofstream myPFile("persons.txt");

  for(int i = 0; i < HASH_SIZE; ++i) {
    auto mapIter = myCardholders.equal_range(i);
    for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
      auto const& item = vecIter->second;
      myPFile << item->getId() << " "
              << item->isActive() << " "
              << item->fullName() << endl;
    }
  }

  myPFile.close();

  // Writing to rentals.txt file
  ofstream myRFile("rentals.txt");

  for(int i = 0; i < HASH_SIZE; ++i) {
    auto mapIter = myBooks.equal_range(i);
    for(auto vecIter = mapIter.first; vecIter != mapIter.second; ++vecIter) {
      auto const& item = vecIter->second;
      if(item->getPersonPtr() != nullptr) {
        myRFile << item->getId() << " "
                << item->getPersonPtr()->getId() << endl;
      }
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
    cout << "7.  Deactive library card" << endl;
    cout << "8.  Exit system\n\n";
    cout << "Please enter a choice: ";
}

void readBooks(multimap<int, Book *> & myBooks) {

    string strBookID, title, author, category;

    ifstream myFile("books.txt");

    while(myFile.good()) {
      getline(myFile, strBookID);
      getline(myFile, title);
      getline(myFile, author);
      getline(myFile, category);
      myFile >> ws;

      int intBookID = stoi(strBookID);
      int mapKey = intBookID % HASH_SIZE;

      Book * bookPtr = new Book(intBookID, title, author, category);
      myBooks.insert(pair<int,Book *>(mapKey, bookPtr));
    }
    myFile.close();
    return;
}

int readPersons(multimap<int, Person *> & myCardholders) {

    string fName, lName;
    int cardNum, act, mapKey;
    int nextID = ID_MIN;


    ifstream myFile("persons.txt");

    if(!myFile) {
      cout << "Unable to open file";
      exit(1);
    }

    while(myFile >> cardNum >> act >> fName >> lName) {
      Person * personPtr = new Person(fName, lName, cardNum, act);
      mapKey = cardNum % HASH_SIZE;
      myCardholders.insert(pair<int,Person *>(mapKey, personPtr));
      nextID++;
    }

    myFile.close();
    return nextID;
}

void readRentals(multimap<int, Book *> myBooks, multimap<int, Person *> myCardholders) {

  ifstream myFile;
  int bookID, cardID;

  myFile.open("rentals.txt");
  if(!myFile) {
    cout << "Unable to open file";
    exit(1);
  }

  while(myFile >> bookID >> cardID) {
    askForIdRetBookPtr(myBooks, bookID)->setPersonPtr(askForIdRetPersonPtr(myCardholders, cardID));
  }
  myFile.close();
}

/******************************************************************************/

int main() {

    multimap<int, Book *> mmapBooks;
    multimap<int, Person *> mmapCardholders;

    int nextID = readPersons(mmapCardholders);
    readBooks(mmapBooks);
    readRentals(mmapBooks, mmapCardholders);

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
                checkoutBook(askForIdRetPersonPtr(mmapCardholders),
                             askForIdRetBookPtr(mmapBooks));
                break;

            case 2:
                // Book return
                returnBook(askForIdRetBookPtr(mmapBooks));
                break;

            case 3:
                // View all books available for checkout
                printAllAvailableBooks(mmapBooks);
                break;

            case 4:
                // View all outstanding rentals
                printAllRentedBooks(mmapBooks);
                break;

            case 5:
                // View outstanding rentals for a single cardholder
                printPersonsRentals(askForIdRetPersonPtr(mmapCardholders), mmapBooks);
                break;

            case 6:
                // Open new library card
                openCard(mmapCardholders, nextID);
                nextID++;
                break;

            case 7:
                // Deactivate library card
                deactivateCard(askForIdRetPersonPtr(mmapCardholders));
                break;

            case 8:
                // Must update records in files here before exiting the program
                update(mmapCardholders, mmapBooks);
                break;

            default:
                cout << "Invalid entry! Pleae select 1-8..." << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
