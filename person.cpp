#include "person.h"

Person::Person(string fName, string lName, int cardNum, bool act) {
    firstName = fName;
    lastName = lName;
    cardID = cardNum;
    active = act;
}

string Person::getFirstName() {
    return firstName;
}

string Person::getLastName() {
    return lastName;
}

int Person::getId() {
    return cardID;
}

void Person::setActive(bool act) {
    if(act == 1){
      active = true;
      return;
    }
    active = false;
    return;
}

bool Person::isActive() {
    return active;
}

string Person::fullName() {
    return firstName + " " + lastName;
}
