/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "UserManager.h"
#include "Exceptions.h"
#include "Admin.h"
#include "Client.h"
#include "AdminUI.h"
#include "ClientUI.h"
#include <list>
#include <tuple>
#include <string>
#include <algorithm>

unsigned int UserManager::curr_id = 1;

UserManager::~UserManager() {
  for (User* user : users)
    delete user;
  users.clear();
}

void UserManager::createUser(char type, std::tuple<std::string,
                                                      std::string> name,
                                                      std::string ml,
                                                      std::string data) {
    int id = getUniqueID();
    std::string fn, ln;
    std::tie(fn, ln) = name;
    switch (type) {
      case 'A': {
        Admin* adm = new Admin(id, fn, ln);
        adm->setEmail(ml);
        adm->setPosition(data);
        addUser(adm);
        break;
      }
      case 'C': {
        Client* cli = new Client(id, fn, ln);
        cli->setEmail(ml);
        cli->setPostalCode(data);
        addUser(cli);
        break;
      }
    }
}

void UserManager::addUser(User* user) {
    users.push_back(user);
}

void UserManager::deleteUser(User* user) {
    bool found = false;
    if (users.empty())
      throw cannot_find_user_error("There are no users at present");
    std::list<User*>::iterator it = users.begin();
    while (it != users.end()) {
      if ((*it) == user) {
        found = true;
        it = users.erase(it);
      } else {
        ++it;
      }
    }
    if (found == false)
      throw cannot_find_user_error("The user you're deleting doesn't exist");
    delete user;
}

std::list<User*> UserManager::listAllUsers() {
  if (users.empty())
    throw cannot_find_user_error("There are no users at present");

    return users;
}

User* UserManager::getUser(int id) {
    if (users.empty())
      throw cannot_find_user_error("There are no users at present");

    auto num = std::find_if(users.begin(), users.end(),
      [id](User* lhs) {
        return lhs->getID() == id;
      });

    return *num;
}

int UserManager::getUniqueID() {
    if (users.empty())
      return curr_id;
    int uid = listAllUsers().back()->getID();
    while (curr_id <= uid) {
      curr_id++;
    }
    return curr_id;
}
