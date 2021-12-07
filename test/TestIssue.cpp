#include "gtest/gtest.h"
#include "Issue.h"

TEST(IssueTest, Constructor) {
  Issue* i = new Issue(1, "Title i");

  EXPECT_EQ(1, i->getID());
  EXPECT_EQ("Title i", i->getTitle());

  delete i;
}

TEST(IssueTest, StatusSet) {
  Issue* i = new Issue(1, "Title i");
  EXPECT_EQ('n', i->getStatus());
  EXPECT_EQ("Unresolved", i->getStatusString());

  i->setStatus('r');

  EXPECT_EQ('r', i->getStatus());
  EXPECT_EQ("Resolved", i->getStatusString());

  delete i;
}

TEST(IssueTest, ComponentSet) {
  Issue* i = new Issue(1, "Title i");
  EXPECT_EQ('n', i->getComponent());
  EXPECT_EQ("None", i->getComponentString());

  i->setComponent('t');

  EXPECT_EQ('t', i->getComponent());
  EXPECT_EQ("Touch screen", i->getComponentString());

  delete i;
}

TEST(IssueTest, BrandSet) {
  Issue* i = new Issue(1, "Title i");
  EXPECT_EQ('n', i->getBrand());
  EXPECT_EQ("Other", i->getBrandString());

  i->setBrand('s');

  EXPECT_EQ('s', i->getBrand());
  EXPECT_EQ("Android", i->getBrandString());

  delete i;
}

TEST(IssueTest, SerialNumTest) {
  Issue* i = new Issue(1, "Title i");

  i->setSerialNum("1234567890abc");
  EXPECT_EQ("1234567890abc", i->getSerialNum());

  i->setSerialNum("serialnumber123");
  EXPECT_EQ("serialnumber123", i->getSerialNum());

  delete i;
}

TEST(IssueTest, createComment) {
  Issue* i = new Issue(1, "Title a");
  i->addComment("C la vie");
  i->addComment("la vie");
  int size = i->listComments().size();

  EXPECT_EQ(2, size);
  EXPECT_EQ("C la vie", i->getComment(1)->getDescription());
  EXPECT_EQ("la vie", i->listComments().back()->getDescription());
  
  delete i;
}
