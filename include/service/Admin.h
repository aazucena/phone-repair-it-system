/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>
#include <string>
#include <list>

class Admin : public User {
 public:
    Admin(int aid, std::string first, std::string last) :
    User(aid, first, last)  {}
    virtual ~Admin() {}

    char getUserType() { return 'A'; }
    std::string getPosition() { return position; }

    void setPosition(std::string pos);

  protected:
    std::string position;
};

#endif // ADMIN_H
