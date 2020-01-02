#include "book.h"

Book::Book(int id, string bookTitle, string bookAuth, string bookCat) {
    title = bookTitle;
    author = bookAuth;
    category = bookCat;
    bookID = id;
}

string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

string Book::getCategory() {
    return category;
}

int Book::getId() {
    return bookID;
}
void Book::setPersonPtr(Person * ptr) {
  personPtr = ptr;
}

Person * Book::getPersonPtr() {
    return personPtr;
}
