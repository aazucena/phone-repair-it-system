/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly:
*/

#include "Exceptions.h"
#include "Issue.h"
#include "IssueManager.h"
#include <string>
#include <iostream>
#include <vector>

IssueManager::~IssueManager() {
  for (Issue* issue : issues) {
    delete issue;
  }
}

void IssueManager::createIssue(std::string title, char brand, char component) {
  int id;

  id = nextID;

  Issue* issue = new Issue(id, title);
  issue->setBrand(brand);
  issue->setComponent(component);

  issues.push_back(issue);
  nextID++;
}

Issue* IssueManager::getIssue(int id) {
  if (issues.empty()) {
    throw cannot_find_issue_error("There are no issues at present");
  }

  for (Issue* issue : issues) {
    if (issue->getID() == id) {
      return issue;
    }
  }

  throw cannot_find_issue_error("Issue ID not found");
}

std::vector<Issue*> IssueManager::listIssues() {
  if (issues.empty()) {
    throw cannot_find_issue_error("There are no issues at present");
  }
  return issues;
}

void IssueManager::deleteIssue(int id) {
  if (issues.empty()) {
    throw cannot_find_issue_error("There are no issues to delete at present");
  }

  bool deleted = false;

  for (int i = 0; i < issues.size(); i++) {
    if (issues.at(i)->getID() == id) {
      Issue* issue = issues.at(i);
      issues.erase(issues.begin() + i);
      delete issue;
      deleted = true;
    }
  }

  if (deleted == false) {
    throw cannot_find_issue_error("No such issue exists");
  }
}

void IssueManager::addIssue(Issue* is) {
  issues.push_back(is);
}

void IssueManager::setIssueTitle(int id, std::string newTitle) {
  Issue* issue = getIssue(id);
  issue->setTitle(newTitle);
}
