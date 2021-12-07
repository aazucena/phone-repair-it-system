/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly:
*/

#include "Issue.h"
#include "Comment.h"
#include "Exceptions.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>

Issue::~Issue() {
  for (Comment* comment : comments) {
    delete comment;
  }
}

Issue::Issue(int id, std::string title): id(id), title(title) {
  setStatus('n');
  setComponent('n');
  setBrand('n');
  setSerialNum("n");
}

void Issue::setTitle(std::string title) {
  Issue::title = title;
}

int Issue::getID() {
  return id;
}

std::string Issue::getTitle() {
  return title;
}

void Issue::setStatus(char s) {
  switch (s) {
    case 'r':
      status = RESOLVED;
      break;
    default:
      status = UNRESOLVED;
      break;
  }
}

// Using 'n' as default char for consistency
char Issue::getStatus() {
  char s;

  switch (status) {
    case RESOLVED:
      s = 'r';
      break;
    default:
      s = 'n';
      break;
  }

  return s;
}

std::string  Issue::getStatusString() {
  std::string s;

  switch (status) {
    case RESOLVED:
      s = "Resolved";
      break;
    default:
      s = "Unresolved";
      break;
  }

  return s;
}

void Issue::setComponent(char c) {
  mobile.setComponent(c);
}

void Issue::setBrand(char b) {
  mobile.setBrand(b);
}

char Issue::getComponent() {
  return mobile.getComponent();
}

char Issue::getBrand() {
  return mobile.getBrand();
}

std::string Issue::getComponentString() {
  return mobile.getComponentString();
}

std::string Issue::getBrandString() {
  return mobile.getBrandString();
}

void Issue::setSerialNum(std::string serial) {
  mobile.setSerialNum(serial);
}

std::string Issue::getSerialNum() {
  return mobile.getSerialNum();
}

void Issue::addComment(std::string s) {
  int cid;

  if (comments.empty()) {
    cid = 1;
  } else {
    cid = comments.back()->getCommentID() + 1;
  }

  Comment* c = new Comment(cid, s);
  comments.push_back(c);
}

void Issue::updateComment(int cid, std::string newComment) {
  Comment* c = comments.at(cid);
  c->updateDescription(newComment);
}

std::vector<Comment*> Issue::listComments() {
  if (comments.empty())
    throw cannot_find_issue_error("No comments added to this issue");
  return comments;
}

Comment* Issue::getComment(int id) {
  if (comments.empty())
    throw cannot_find_issue_error("No comments added to this issue");

  if (id > comments.size() || id < 1)
    throw cannot_find_issue_error("Please choose a valid comment id");

  return comments.at(id-1);
}
