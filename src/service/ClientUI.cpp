/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "ClientUI.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

std::string ClientUI::requestUserData() {
  std::string postal = "";
  bool isLength = false;
  getline(std::cin, postal);
  while (!isPostalCode(postal) && (isLength == false)) {
      std::cout << "Enter Client's Postal Code (A0A 0A0): ";
      // check if input is string
      while (!(getline(std::cin, postal))) {
        std::cout << "This input is not a string. "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
      }

      // remove space from string
      postal.erase(std::remove(postal.begin(), postal.end(), ' '),
                                                        postal.end());

      // check if string input is formatted right as a postal code
      if (!isPostalCode(postal)) {
        std::cout << "This input "
                  << postal
                  << " isn't valid to be a postal code. "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
      }

      // check if input length == 6
      if (postal.length() != POSTAL_LENGTH) {
        std::cout << "This input "
                  << postal
                  << " is not at the right length. "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
      } else {
        isLength = true;
      }
  }
  return postal;
}

bool ClientUI::isPostalCode(const std::string& post) {
    int digit = 0, alpha = 0, total;
    for (unsigned int i = 0; i < post.length(); ++i) {
      char alp = post.at(i);
      if (isalpha(alp) && ((alp % 2) == 0))
        alpha++;
      else
        digit++;
    }
    total = digit + alpha;  // 6 = 3 + 3 as expected
    return (total == 6);
}
