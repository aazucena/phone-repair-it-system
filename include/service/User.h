/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
 public:
   User(int uid, std::string first, std::string last) : id(uid), fname(first),
    lname(last) {}
   virtual ~User() {}

   /**
   * virtual function for getting user type
   * @param unused
   * @return user type character
   */
   virtual char getUserType() = 0;

   /**
   * Get ID of User
   * @param unused
   * @return return the integer for id
   */
   int getID() { return id; }

   /**
   * Get firstname of User
   * @param unused
   * @return return the string for firstname
   */
   std::string getFirstName() { return fname; }

   /**
   * Get lastname of User
   * @param unused
   * @return return the string for lastname
   */
   std::string getLastName() { return lname; }

   /**
   * Get email of User
   * @param unused
   * @return return the string for email
   */
   std::string getEmail() { return email; }

   /**
   * Set email for user
   * @param string mail
   * @return void
   */
   void setEmail(std::string mail);

   /**
   * Get output for the user
   * @param ostream& os, User& u
   * @return return the output ostream for user
   */
   friend std::ostream& operator<<(std::ostream& os, User& u);

   /**
   * Boolean == for User
   * @param User& lhs, User& rhs
   * @return return true if lhs' data == rhs' data
   */
   friend bool operator==(const User& lhs, const User& rhs);


 protected:
   int id;
   std::string fname;
   std::string lname;
   std::string email;
};

#endif // USER_H
