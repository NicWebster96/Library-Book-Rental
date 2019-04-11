// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "person.cpp"
#include "book.cpp"

using namespace std;

Book * searchBook(vector<Book *> myBooks, int id);
Person * searchPerson(vector<Person *> myCardholders, int id);

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

//You are not obligated to use these function declarations -
// they're just given as examples

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

void readPersons(vector<Person *> & myCardholders) {

    Person * personPtr;

    ifstream myFile("persons.txt");

    string fName, lName;
    int cardNum, act;

    while(myFile >> cardNum >> act >> fName >> lName) {
      personPtr = new Person(cardNum, act, fName, lName);
      myCardholders.push_back(personPtr);
    }
    delete personPtr;
    myFile.close();
    return;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
  ifstream myFile("rentals.txt");

  int bookID, cardID;

  while(myFile >> bookID >> cardID) {
    cout << "Book ID: " << bookID << endl;
    cout << "Title: " << searchBook(myBooks, bookID)->getTitle() << endl;
    cout << "Author: " << searchBook(myBooks, bookID)->getAuthor() << endl;

    cout << "Cardholder: " << searchPerson(myCardholders, cardID)->fullName() << endl;
    cout << "Card ID: " << cardID << endl << endl;
  }
  myFile.close();
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks[i]->getId() == id) {
      return myBooks[i];
    }
  }
  cout << "Book ID not found" << endl;
}

Person * searchPerson(vector<Person *> myCardholders, int id) {
  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders[i]->getId() == id) {
      return myCardholders[i];
    }
  }
  cout << "Person not found" << endl;
}

int askCardID(vector<Person *> myCardholders) {
  int cardID;
  cout << "Please enter the card ID: ";
  cin >> setw(4) >> cardID;

  for(int i=0; i<myCardholders.size(); i++) {
    if(myCardholders[i]->getId() == cardID) {
      return cardID;
    }
  }
  cout << "Card ID not found" << endl;
}

int askBookID(vector<Book *> myBooks) {
  int bookID;
  cout << "Please enter the book ID: ";
  cin >> setw(5) >> bookID;

  for(int i=0; i<myBooks.size(); i++) {
    if(myBooks[i]->getId() == bookID) {
      return bookID;
    }
  }
  cout << "Book ID not found" << endl;
}

void checkRental(vector<Book*> myBooks, int id) {
  ifstream myFile("rentals.txt");

  int bookID, cardID;
  int count = 0;

  while(myFile >> bookID >> cardID){
    if(cardID == id) {
      cout << endl << "Book ID: " << bookID << endl;
      cout << "Title: " << searchBook(myBooks, bookID)->getTitle() << endl;
      cout << "Author: " << searchBook(myBooks, bookID)->getAuthor() << endl << endl;
      count++;
    }
  }
  if(count == 0) {
    cout << "No books currently checked out" << endl;
  }
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int tmpBID;
    int tmpPID;

    readPersons(cardholders);
    readBooks(books);

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle
        // the <ENTER> key that the user pressed when entering a menu option.
        // This is still in the input stream.
        printMenu();
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                // Book checkout
                tmpPID = askCardID(cardholders);
                cout << "Cardholder: "
                     << searchPerson(cardholders, tmpPID)->fullName() << endl;


                tmpBID = askBookID(books);
                cout << "Title: "
                     << searchBook(books,tmpBID)->getTitle() << endl;

                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                readRentals(books, cardholders);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                tmpPID = askCardID(cardholders);
                cout << "Cardholder: "
                     << searchPerson(cardholders, tmpPID)->fullName() << endl;

                checkRental(books, tmpPID);

                break;

            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
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
