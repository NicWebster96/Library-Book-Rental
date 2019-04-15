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
    if(act){
      active = true;
    } else {
      active = false;
    }
}

bool Person::isActive() {
    if(active) {return true;}
}

string Person::fullName() {
    return firstName + " " + lastName;
}
