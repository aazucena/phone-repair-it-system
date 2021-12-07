#include "gtest/gtest.h"

#include "Exceptions.h"
#include "Issue.h"
#include "IssueManager.h"

#include <string>

TEST(IssueManagerTest, GetIssueByID) {
  IssueManager im;

  im.createIssue("I think my phone is broken!?", 'n', 'n');
  im.createIssue("Battery runs low fast", 'n', 'n');
  im.createIssue("Screen isn't responsive", 'n', 'n');

  // Get 1st issue
  Issue* issue1 = im.getIssue(1);

  EXPECT_EQ(1, issue1->getID());
  EXPECT_EQ("I think my phone is broken!?", issue1->getTitle());

  // Get 3rd issue
  Issue* issue3 = im.getIssue(3);

  EXPECT_EQ(3, issue3->getID());
  EXPECT_EQ("Screen isn't responsive", issue3->getTitle());

  // Testing Exceptions
  EXPECT_THROW(im.getIssue(-1), cannot_find_issue_error);
  EXPECT_THROW(im.getIssue(4), cannot_find_issue_error);
}

TEST(IssueManagerTest, CreateIssue) {
  IssueManager im;

  std::string title = "I want to upgrade the battery";
  im.createIssue(title, 'n', 'n');

  Issue* issue = im.getIssue(1);
  EXPECT_EQ(1, issue->getID());
  EXPECT_EQ(1, im.listIssues().back()->getID());
  EXPECT_EQ("I want to upgrade the battery", issue->getTitle());

  // Should be the 2nd issue
  title = "My IPhone is wet...";
  im.createIssue(title, 'n', 'n');

  issue = im.getIssue(2);
  EXPECT_EQ(2, issue->getID());
  EXPECT_EQ("My IPhone is wet...", issue->getTitle());
}

TEST(IssueManagerTest, DeleteIssue) {
  IssueManager im;

  im.createIssue("I think my phone is broken!?", 'n', 'n');
  im.createIssue("Battery runs low fast", 'n', 'n');
  im.createIssue("Screen isn't responsive", 'n', 'n');
  EXPECT_EQ(3, im.listIssues().size());

  // delete Issue with ID 2
  im.deleteIssue(2);
  EXPECT_THROW(im.getIssue(2), cannot_find_issue_error);
  EXPECT_EQ(2, im.listIssues().size());

  // Should have ID 4
  im.createIssue("4th issue with ID 4", 'n', 'n');
  Issue* issue4 = im.getIssue(4);

  EXPECT_EQ(4, issue4->getID());
  EXPECT_EQ("4th issue with ID 4", issue4->getTitle());
  EXPECT_EQ(3, im.listIssues().size());

  // Non-existant error
  EXPECT_THROW(im.getIssue(5), cannot_find_issue_error);
}
