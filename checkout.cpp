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
    cout << myCardholders.at(0) << endl;
    cout << myCardholders.at(1) << endl;

    myFile.close();
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}


void askCardID(vector<Person *> cardholders) {
  int cardID;
  cout << "Please enter the card ID: ";
  cin >> setw(4) >> cardID;

  for(int i=0; i<cardholders.size(); i++) {
    if(cardholders[i]->getId() == cardID) {
      cout << "Cardholder: " << cardholders[i]->fullName() << endl;
      return;
    }
  }
  cout << "Card ID not found" << endl;
}

void askBookID(vector<Book *> books) {
  int bookID;
  cout << "Please enter the book ID: ";
  cin >> setw(5) >> bookID;

  for(int i=0; i<books.size(); i++) {
    if(books[i]->getId() == bookID) {
      cout << "Title: " << books[i]->getTitle() << endl;
      return;
    }
  }
  cout << "Book ID not found" << endl;
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

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
                askCardID(cardholders);
                askBookID(books);
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
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
