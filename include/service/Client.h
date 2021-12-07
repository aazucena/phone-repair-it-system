/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"
#include <iostream>
#include <string>
#include <list>

// Owns a mobile device (Mobile.h)

class Client : public User {
 public:
     Client(int cid, std::string first, std::string last) :
     User(cid, first, last)  {}
     virtual ~Client() {}

     char getUserType() { return 'C'; }
     std::string getPostalCode() { return postal; }

     void setPostalCode(std::string post);

 private:
     std::string postal;
};

#endif // CLIENT_H
