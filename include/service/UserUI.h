/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#ifndef USERUI_H
#define USERUI_H

#include <tuple>

class UserUI {
 public:
    UserUI() {}
    ~UserUI() {}

    /**
    * Request Data Exclusive to Client and Admin
    * @param unused
    * @return data from string input
    */
    virtual std::string requestUserData() = 0;

    /**
    * Request Tuple Data for getting full name
    * @param unused
    * @return tuple data that includes first and last name
    */
    std::tuple<std::string, std::string> requestName();

    /**
    * Request user
    * @param unused
    * @return user id
    */
    unsigned int requestUser();

    /**
    * Request User Type
    * @param unused
    * @return char for the User Type
    */
    char chooseUserType();

    /**
    * Request user email
    * @param unused
    * @return email from string input
    */
    std::string requestEmail();

 protected:
    const int MAX_EMAIL_LENGTH = 7; //d@b.ca (6 char) -- shortest email

 private:

    /**
    * Check if it is an email
    * @param unused
    * @return true if the string contains email elements and is vaild
    */
    bool isEmail(const std::string& mail);

};
#endif // USERUI_H
