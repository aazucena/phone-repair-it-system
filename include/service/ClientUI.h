/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef CLIENTUI_H
#define CLIENTUI_H

#include "UserUI.h"
#include "Client.h"

class ClientUI : public UserUI {
 public:
    ClientUI() {}
    ~ClientUI() {}

    std::string requestUserData();

 protected:
    const int POSTAL_LENGTH = 6; // eg. G2D7V6 -- no spaces added

  private:
    /**
    * Check if string is postal code
    * @param constant reference of the string
    * @return true if the string is valid as postal code
    */
    bool isPostalCode(const std::string& post);
};
#endif // CLIENTUI_H
