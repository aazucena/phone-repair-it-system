/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef ADMINUI_H
#define ADMINUI_H

#include "UserUI.h"
#include "Admin.h"
#include <vector>
#include <string>

class AdminUI : public UserUI {
 public:
    AdminUI() {}
    ~AdminUI() {}

    std::string requestUserData();

 private:

};
#endif // ADMINUI_H
