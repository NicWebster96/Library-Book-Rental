#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    firstName = fName;
    lastName = lName;
    cardID = cardNo;
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
}

bool Person::isActive() {
    if(active == 1) {return true;}
    return false;
}

string Person::fullName() {
    return firstName + " " + lastName;
}
