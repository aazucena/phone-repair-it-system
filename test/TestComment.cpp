#include "gtest/gtest.h"
#include "Comment.h"

TEST(CommentTest, Constructor) {
  Comment* c = new Comment(3, "Hello issue");

  EXPECT_EQ(3, c->getCommentID());
  EXPECT_EQ("Hello issue", c->getDescription());

  delete c;
}

TEST(CommentTest, UpdateComment) {
  Comment* c = new Comment(1, "Hello issue");
  c->updateDescription("New issue");

  EXPECT_EQ("New issue", c->getDescription());

  delete c;
}
