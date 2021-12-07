#ifndef INCLUDE_ISSUE_H_
#define INCLUDE_ISSUE_H_

#include <string>
#include <vector>
#include "Mobile.h"
#include "Admin.h"
#include "Comment.h"

/**
* Class that represents an Issue
* Holds information such as Issue ID, title, and Status
* Also has information on what the issue about a mobile device has such as
* what brand it is and what Component the issue focuses on
* Can add comments and set Assignee
*/
class Issue {
 public:
    enum Status {UNRESOLVED, RESOLVED};

    Issue(int id, std::string title);
    virtual ~Issue();

    /**
    * @param string title of the issue
    */
    void setTitle(std::string title);

    /**
    * @return int ID of the issue
    */
    int getID();

    /**
    * @return string title of the issue
    */
    std::string getTitle();

    /**
    * chars are: 'r' for Resolved, 'n' for Unresolved
    * @param char that represents the status of the issue
    */
    void setStatus(char s);

    /**
    * chars are: 'a' for Apple, 's' for Android, 'n' for Other
    * @param char that represents the brand of a mobile device
    */
    void setBrand(char b);

    /**
    * chars are: 's' for Screen, 'c' for Camera, 'b' for Battery,
    * 'p' for Charge Port, 't' for Touch Screen, 'n' for None
    * @param char representing the compnenet of the issue that is affected
    */
    void setComponent(char c);

    /**
    * chars are: 'r' for Resolved, 'n' for Unresolved
    * @return char that represents the status of the issue
    */
    char getStatus();

    /**
    * chars are: 's' for Screen, 'c' for Camera, 'b' for Battery,
    * 'p' for Charge Port, 't' for Touch Screen, 'n' for None
    * @return char representing the compnenet of the issue that is affected
    */
    char getComponent();

    /**
    * chars are: 'a' for Apple, 's' for Android, 'n' for Other
    * @return char that represents the brand of a mobile device
    */
    char getBrand();

    /**
    * @return string that represents the status of the issue
    */
    std::string getStatusString();

    /**
    * @return string representing the compnenet of the issue that is affected
    */
    std::string getComponentString();

    /**
    * @return string that represents the brand of a mobile device
    */
    std::string getBrandString();

    /**
    * @param string representing the Serial Number of a mobile device
    */
    void setSerialNum(std::string serial);

    /**
    * @return string representing the Serial Number of a mobile device
    */
    std::string getSerialNum();

    /**
    * @brief Adds a comment to an issue
    * @param comment description
    */
    void addComment(std::string s);

    /**
    *@return Comment object based on comment id
    */
    Comment* getComment(int id);

    /**
    * @brief updates a comment description
    * @param comment description and comment id
    */
    void updateComment(int cid, std::string cmt);

    /**
    *@return vector of comments added to issue
    */
    std::vector<Comment*> listComments();

 private:
    int id;
    std::string title;
    Status status;

    Mobile mobile;
    std::vector<Comment*> comments;
};

#endif
