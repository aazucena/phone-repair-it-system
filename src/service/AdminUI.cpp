/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "AdminUI.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string AdminUI::requestUserData() {
  bool isJob = false;
  int choice = -1;
  std::string position;
  std::cout << "Choose your Mobile Repair Company's Job Title: " << std::endl;
  std::cout << "1. Reporter" << std::endl;
  std::cout << "2. Technician" << std::endl;
  std::cout << "3. Manager" << std::endl;
  std::cout << "4. Owner" << std::endl;

  while (isJob == false) {
    while (!(std::cin >> choice)) {
      std::cout << "This input is not an integer. "
                << std::endl;
      std::cin.clear();
      std::cin.ignore(123, '\n');
    }
    switch (choice) {
      case 1:
        isJob = true;
        position = "Reporter";
        break;
      case 2:
        isJob = true;
        position = "Technician";
        break;
      case 3:
        isJob = true;
        position = "Manager";
        break;
      case 4:
        isJob = true;
        position = "Owner";
        break;
      default:
        std::cout << "Your input can't get your Job Title! "
                  << std::endl;
        std::cin.clear();
        std::cin.ignore(123, '\n');
    }
  }
  return position;
}
