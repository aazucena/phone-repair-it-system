/*
* CPSC 3720 Fall 2020
* Copyright 2020, Team Gnarly: Kevin Baffo <k.baffo@uleth.ca>
*/
#include <iostream>
#include <vector>
#include <string>
#include "IssueUI.h"

unsigned int actionChecker(unsigned int action, std::vector<std::string> alist);

unsigned int actionChecker(unsigned int action, std::vector<std::string>
   alist) {
  int count = 0;
  for (std::string s : alist) {
    std::cout << "\nChoice "  << ++count << ": " << s;
  }
  std::cout << std::endl;
  std::cout << "\nPlease choose an action: (0 to Exit) :";
  while (action > alist.size() || action < 0) {
    while (!(std::cin >> action)) {
      std::cout << "This is not a number, Please enter a number: "
      << std::endl;
      std::cin.clear();
      std::cin.ignore(123, '\n');
    }
    if (action > alist.size() || action < 0) {
      std::cout << "Please Enter a number listed above!" << std::endl;
      std::cin.clear();
      std::cin.ignore(123, '\n');
    }
  }
  return action;
}

char IssueUI::requestMobileBrand() {
  std::vector<std::string> actionList;
  unsigned int action = -1;
  char act;
  actionList.push_back("Apple");
  actionList.push_back("Android");
  actionList.push_back("Other");

  action = actionChecker(action, actionList);
  switch (action) {
    case 1:
      act = 'a';
      break;
    case 2:
      act = 's';
      break;
    default:
      act = 'n';
      break;
  }
  return act;
}

char IssueUI::requestBrandNewComponent() {
  std::vector<std::string> actionList;
  unsigned int action = -1;
  char act;
  actionList.push_back("Screen");
  actionList.push_back("Camera");
  actionList.push_back("Battery");
  actionList.push_back("Charger Port");
  actionList.push_back("Touch Screen");

  action = actionChecker(action, actionList);
  switch (action) {
    case 1:
      act = 's';
      break;
    case 2:
      act = 'c';
      break;
    case 3:
      act = 'b';
      break;
    case 4:
      act = 'p';
      break;
    case 5:
      act = 't';
      break;
    default:
      act = 'n';
      break;
  }
  return act;
}

std::string IssueUI::pickIssue() {
  std::vector<std::string> actionList;
  unsigned int action = -1;
  std::string title;
  actionList.push_back("I do not know / Other");
  actionList.push_back("Back Housing or cover");
  actionList.push_back("Broken Screen");
  actionList.push_back("Water Damage");
  actionList.push_back("Short Battery life");
  actionList.push_back("Cannot charge");

  action = actionChecker(action, actionList);
  if (action == 1) {
    title = requestNewComment();
  } else {
    title = actionList.at(action-1);
  }
  return title;
}

unsigned int IssueUI::issuesAction() {
  std::vector<std::string> issueActions;
  unsigned int action = -1;
  issueActions.push_back("Create issue");  // 1
  issueActions.push_back("Get issue");  // 2
  issueActions.push_back("List all issues");  // 3
  issueActions.push_back("Assign issue");  // 4
  issueActions.push_back("Update issue title");  // 5
  issueActions.push_back("Delete issue");  // 6

  action = actionChecker(action, issueActions);
  return action;
}

unsigned int IssueUI::cmtsAction() {
  std::vector<std::string> actionList;
  unsigned int action = -1;
  actionList.push_back("Add comment");  // 11
  actionList.push_back("Get comment");  // 12
  actionList.push_back("Get all comments");
  actionList.push_back("Update comment");  // Not necessary

  action = actionChecker(action, actionList);
  return action;
}

unsigned int IssueUI::userAction() {
  std::vector<std::string> actionList;
  unsigned int action = -1;
  actionList.push_back("Add user");
  actionList.push_back("List all users");
  actionList.push_back("Remove user");
  action = actionChecker(action, actionList);
  return action;
}

unsigned int IssueUI::chooseAction() {
  unsigned int action = -1;
  std::vector<std::string> actionList;
  actionList.push_back("ISSUES");
  actionList.push_back("COMMENTS");
  actionList.push_back("USERS");

  action = actionChecker(action, actionList);
  return action;
}

unsigned int IssueUI::requestIssue() {
  unsigned int issue = -1;
  std::cout << "Enter Issue id: ";
  while (!(std::cin >> issue)) {
    std::cout << "This is not a number, Please enter a number: "
    << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
  }
  return issue;
}

std::string IssueUI::requestNewComment() {
  std::string issue, line;
  issue.clear();
  std::cout << "Enter description:";
  // << "(Please use Unsercore(_) instead of whitespace ( )) ";
  // std::cin >> issue;
  std::getline(std::cin, issue);
  while (!(getline(std::cin, issue))) {
    std::cout << "This input is not a string. "
              << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
  }

  return issue;
}

unsigned int IssueUI::requestComment() {
  unsigned int cmt = -1;
  std::cout << "Enter Comment id: ";
  while (!(std::cin >> cmt)) {
    std::cout << "This is not a number, Please enter a number: "
    << std::endl;
    std::cin.clear();
    std::cin.ignore(123, '\n');
  }
  return cmt;
}
