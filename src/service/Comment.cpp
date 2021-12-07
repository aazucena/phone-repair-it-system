/*
* CPSC 3720 Fall 2020
* Copyright 2020, Team Gnarly: Kevin Baffo <k.baffo@uleth.ca>
*/

#include "Comment.h"
#include <string>

Comment::Comment(int cid, std::string comment): commentID(cid), cmt(comment) {}

int Comment::getCommentID() {
  return commentID;
}

std::string Comment::getDescription() {
  return cmt;
}

void Comment::updateDescription(std::string newCom) {
  cmt.clear();
  cmt = newCom;
}
