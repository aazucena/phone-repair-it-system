/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "User.h"
#include <string>
#include <list>

void User::setEmail(std::string mail) {
    email = mail;
}

std::ostream& operator<<(std::ostream& os, User& u) {
    os << u.getUserType() << u.getID() << ": "
       << u.getFirstName() << " " << u.getLastName();
    return os;
}

bool operator==(const User& lhs, const User& rhs) {
  return (lhs.id == rhs.id) && (lhs.fname == rhs.fname)
                            && (lhs.lname == rhs.lname);
}
