#ifndef ISSUEUI_H
#define ISSUEUI_H

#include <string>

class IssueUI {
public:
   IssueUI() {}
   ~IssueUI() {}

   /**
   * Request an action
   * @return Action chosen
   */
   unsigned int chooseAction();

   /**
   * Request an action
   * @return Action chosen
   */
   unsigned int issuesAction();
   /**
   * Request an action
   * @return Action chosen
   */
   unsigned int userAction();

   /**
   * Request an action
   * @return Action chosen
   */
   unsigned int cmtsAction();

   /**
   * Request an issue id
   * @return issue id
   */
   unsigned int requestIssue();

   /**
   * Request a comment description
   * @return the new description
   */
   std::string requestNewComment();

   /**
   * Request a comment id
   * @return comment id
   */
   unsigned int requestComment();

   /**
   * Request brand of Mobile
   * @return 'A' for android and 'S' for android and 'N' for other brands
   */
   char requestMobileBrand();

   /**
   * Request a mobile component to be replaced
   * @return Screen('s'), Camera('c'), Battery('b')
   * Charger Port('p'), Touch Screen('t')
   */
   char requestBrandNewComponent();

   /**
   * Request an issue title
   * @return predefine title or entered title
   */
   std::string pickIssue();
};

#endif // ISSUEUI_H
