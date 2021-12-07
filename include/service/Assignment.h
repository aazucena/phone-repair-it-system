#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

/**
* A class that holds the relationship between an Admin and User
*/
class Assignment {
 public:
    Assignment(int isID, int adID) : issueID(isID), adminID(adID) {}
    virtual ~Assignment() {}

    void setAdmin(int admnID);

    int getIssueID();
    int getAdminID();

 private:
    int issueID;
    int adminID;
};

#endif
