/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "UserUI.h"
#include <tuple>
#include <list>
#include <vector>

class UserManager {
public:
   UserManager() {}
   virtual ~UserManager();

   /**
   * Creates the user with the data
   * @param char type, tuple<string, string> name, string ml, string data
   * @return data from string input
   */
   void createUser(char type, std::tuple<std::string, std::string> name,
                                              std::string ml,
                                              std::string data);

   /**
   * Add the user
   * @param User* user for getting the class of the user
   * @return void
   */
   void addUser(User* user);

   /**
   * Deletes the user
   * @param User* user for getting the class of the user
   * @return void
   */
   void deleteUser(User* user);

   /**
   * Request the list of data
   * @param unused
   * @return the list of users
   */
   std::list<User*> listAllUsers();

   /**
   * Get the user from the list
   * @param integer UserID for getting id from user
   * @return data from string input
   */
   User* getUser(int userID);

   /**
   * Initialize the User List
   * @param unused
   * @return void
   */
   int getUniqueID();

   /**
   * Stores Current ID
   */
   static unsigned int curr_id;

 private:
   std::list<User*> users;

};
#endif // USERMANAGER_H
