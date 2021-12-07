#ifndef ISSUEMANAGER_H
#define ISSUEMANAGER_H

#include "Issue.h"
#include "Comment.h"
#include <string>
#include <vector>

/**
* Class that manages all Issues for the system
*/
class IssueManager {
 public:
    IssueManager() {}
    virtual ~IssueManager();

    /**
    * Creates and adds an Issue to a list of issues
    * @param string representing the title of the Issue
    * @param char that represents a brand for a mobile device
    * @param char that represents the component the issue focuses on
    */
    void createIssue(std::string title, char brand, char component);

    /**
    * Get an issue based on specified ID
    * @param int ID to get
    * @return The Issue requested
    */
    Issue* getIssue(int id);

    /**
    * @return a vector of issues
    */
    std::vector<Issue*> listIssues();

    /**
    * Deletes an issue based on ID
    * @param int ID of an issue
    */
    void deleteIssue(int id);

    /**
    * Adds an issue to a vector of issues
    * @param Issue object
    */
    void addIssue(Issue* is);

    /**
    * @param int ID of an Issue to be updated
    * @param string representing the new title for an issue
    */
    void setIssueTitle(int id, std::string newTitle);

    // void addComment(int iid, Comment c);
    // Comment getComment(int iid, int cid);
    // void updateComment(int iid,Comment c, std::string s); // Update content of a comment
    // // bool deleteComment(Comment*); // returns true if comment has been deleted
    // // std::string findComment(Comment*); // Get content of a comment
    // std::vector<Comment> listComments(); // List description of all comments in an issue

 private:
    int nextID = 1;
    std::vector<Issue*> issues;
};

#endif
