#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>
#include <string>

class cannot_find_issue_error: public std::runtime_error {
 public:
    explicit cannot_find_issue_error(const std::string& errMessage) :
      std::runtime_error(errMessage) {}
};

class cannot_find_user_error: public std::runtime_error {
 public:
    explicit cannot_find_user_error(const std::string& errMessage) :
      std::runtime_error(errMessage) {}
};

class no_assigned_admin_error: public std::runtime_error {
 public:
    explicit no_assigned_admin_error(const std::string& errMessage) :
      std::runtime_error(errMessage) {}
};

#endif
