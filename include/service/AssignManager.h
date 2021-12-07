#ifndef INCLUDE_ASSIGNMANAGER_H_
#define INCLUDE_ASSIGNMANAGER_H_

#include "Issue.h"
#include "IssueManager.h"
#include "UserManager.h"
#include "Assignment.h"
#include <vector>

/**
* Class that manages operations beteen Admins and Issues
*/
class AssignManager {
 public:
    AssignManager() {}
    virtual ~AssignManager() {}

    /**
    * Assign an issue to an admin
    * @param an issue's ID as an int
    * @param an admin's ID as an int
    */
    void assignIssue(int issueID, int adminID);

    /**
    * Get the admin assigned to an issue
    * @param issue ID
    * @return admin ID
    */
    int getAssigned(int iid);

    /**
    * Finds all issues an admin is assigned
    * @param an admin's ID as an int
    * @param an object of IssueManager
    * @return a list of issues
    */
    // std::vector<int> getAdminAssignments(int adminID, IssueManager* is);

 private:
    std::vector<Assignment*> assignments;
};

#endif
