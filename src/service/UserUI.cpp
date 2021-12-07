/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "UserUI.h"
#include <tuple>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

std::tuple<std::string, std::string> UserUI::requestName() {
  std::string fn, ln;
  std::cout << "What is your first name? ";
  while (!(std::cin >> fn)) {
    std::cout << "This is not a string! " << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
    std::cout << "What is your first name? ";
  }
  std::cout << std::endl;

  std::cout << "What is your last name? ";
  while (!(std::cin >> ln)) {
    std::cout << "This is not a string! " << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
    std::cout << "What is your last name? ";
  }
  std::cout << std::endl;

  return std::make_tuple(fn, ln);
}

char UserUI::chooseUserType() {
  char uType;
  bool isInput = false;
  while (isInput == false) {
    std::cout << "What is the User Type?" << std::endl;
    std::cout << "\t - Admin [A]" << std::endl;
    std::cout << "\t - Client [C]" << std::endl;
    while (!(std::cin >> uType)) {
      std::cout << "This is not a character! " << std::endl;
      std::cin.clear();
      std::cin.ignore(123, '\n');
    }
    std::cout << std::endl;
    uType = std::toupper(uType);
    switch (uType) {
      case 'A':
      case 'C':
        isInput = true;
        break;
      default:
        std::cout << "The character you've chosen is not a User Type! "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
    }
  }
  return uType;
}

unsigned int UserUI::requestUser() {
  unsigned int user = -1;
  std::cout << "Enter User id: ";
  while (!(std::cin >> user)) {
    std::cout << "This is not a number, Please enter a number: " << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
  }
  return user;
}

std::string UserUI::requestEmail() {
  std::string email;
  do {
      std::cout << "Enter User Email: ";
      // check if input is string
      while (!(std::cin >> email))  {
        std::cout << "This input is not a string. "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
      }
      std::cout << std::endl;
  } while (!isEmail(email));
  return email;
}

bool UserUI::isEmail(const std::string& mail) {
    int faults = 0;
    auto at = mail.find('@');
    auto period = mail.find('.');

    // check if input has '@'
    if (at == std::string::npos) {
      std::cout << "This is input doesnt have '@'. " << std::endl;
      faults++;
    }
    // check if input has '.'
    if (period == std::string::npos) {
      std::cout << "This is input doesnt have '.'. " << std::endl;
      faults++;
    }
    // check if input length < 7
    if (mail.length() < MAX_EMAIL_LENGTH) {
      std::cout << "The input atleast needs 7 characters. " << std::endl;
      faults++;
    }
    return (faults == 0);
}
