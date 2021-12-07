/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly:
*/

#include "Assignment.h"
#include "AssignManager.h"
#include "Exceptions.h"
#include <vector>

void AssignManager::assignIssue(int iid, int aid) {
  // Makes sure there is only 1 admin assigned in an issue
  for (Assignment* assignment : assignments) {
    int issID = assignment->getIssueID();

    if (issID == iid) {
      assignment->setAdmin(aid);
      return;
    }
  }

  // else
  Assignment* assign = new Assignment(iid, aid);
  assignments.push_back(assign);
}

int AssignManager::getAssigned(int iid) {
  for (Assignment* assignment : assignments) {
    int issID = assignment->getIssueID();

    if (iid == issID) {
      return assignment->getAdminID();
    }
  }

  return 0;
}
