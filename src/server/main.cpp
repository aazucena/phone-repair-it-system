/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Kevin Baffo <k.baffo@uleth.ca>
*/

#include "IssueManager.h"
#include "UserManager.h"
#include "AssignManager.h"

#include <restbed>
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <tuple>


enum OPERATION {UNKNOWN, GET_ISSUE, GET_COMMENT, ADD_COMMENT, ADD_ISSUE,
  LIST_ISSUES, LIST_COMMENTS, UPDATE_COMMENT, SET_ISSUE_TITLE, DELETE_ISSUE,
  ADD_USER, LIST_USERS, DELETE_USER, ASSIGN_ISSUE};

struct expression {
    OPERATION op;
    int id;
    int cid;
    int uid;
    char status;
    char brand;
    char comp;
    char uType;
    std::string search;
    std::string title;
    std::string cmt;
    std::string firstName;
    std::string lastName;
    std::string uEmail;
    std::string uData;
};

IssueManager is;
UserManager um;
AssignManager am;

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

void set_operation(expression* expr, const char* operation) {
    if (strcmp("Get issue", operation) == 0)
        expr->op = GET_ISSUE;
    else if (strcmp("Set title", operation) == 0)
        expr->op = SET_ISSUE_TITLE;
    else if (strcmp("Delete title", operation) == 0)
        expr->op = DELETE_ISSUE;
    else if (strcmp("Delete user", operation) == 0)
        expr->op = DELETE_USER;
    else if (strcmp("Get comment", operation) == 0)
        expr->op = GET_COMMENT;
    else if (strcmp("Add issue", operation) == 0)
        expr->op = ADD_ISSUE;
    else if (strcmp("Assign issue", operation) == 0)
        expr->op = ASSIGN_ISSUE;
    else if (strcmp("Add comment", operation) == 0)
        expr->op = ADD_COMMENT;
    else if (strcmp("Add user", operation) == 0)
        expr->op = ADD_USER;
    else if (strcmp("Update comment", operation) == 0)
        expr->op = UPDATE_COMMENT;
    else if (strcmp("List all issues", operation) == 0)
        expr->op = LIST_ISSUES;
    else if (strcmp("List users", operation) == 0)
        expr->op = LIST_USERS;
    else if (strcmp("Get all comments", operation) == 0)
        expr->op = LIST_COMMENTS;
    else
        expr->op = UNKNOWN;
}

// for post request
void parse(const char* data, expression* expr) {
    char* data_mutable = const_cast<char*>(data);
    char* operation = strtok_r(data_mutable, ",", &data_mutable);
    set_operation(expr, operation);

    if (expr->op == ADD_ISSUE) {
      char* title = strtok_r(nullptr, ",", &data_mutable);
      char* brand = strtok_r(nullptr, ",", &data_mutable);
      char* comp = strtok_r(nullptr, ",", &data_mutable);

      expr->title = title;
      expr->brand = *brand;
      expr->comp = *comp;
    }
    if (expr->op == ADD_COMMENT) {
      char* iid = strtok_r(nullptr, ",", &data_mutable);
      char* comment = strtok_r(nullptr, ",", &data_mutable);

      expr->cmt = comment;
      expr->id = std::stod((std::string)iid);
    }
    if (expr->op == UPDATE_COMMENT) {
      char* iid = strtok_r(nullptr, ",", &data_mutable);
      char* cid = strtok_r(nullptr, ",", &data_mutable);
      char* comment = strtok_r(nullptr, ",", &data_mutable);

      expr->cmt = comment;
      expr->id = std::stod((std::string)iid);
      expr->cid = std::stod((std::string)cid);
    }
    if (expr->op == SET_ISSUE_TITLE) {
      char* iid = strtok_r(nullptr, ",", &data_mutable);
      char* title = strtok_r(nullptr, ",", &data_mutable);

      expr->title = title;
      expr->id = std::stod((std::string)iid);
    }
    if (expr->op == DELETE_ISSUE) {
      char* id = strtok_r(nullptr, ",", &data_mutable);

      expr->id = std::stod((std::string)id);
    }
    if (expr->op == DELETE_USER) {
      char* id = strtok_r(nullptr, ",", &data_mutable);

      expr->uid = std::stod((std::string)id);
    }
    if (expr->op == ADD_USER) {
      char* type = strtok_r(nullptr, ",", &data_mutable);
      char* fname = strtok_r(nullptr, ",", &data_mutable);
      char* lname = strtok_r(nullptr, ",", &data_mutable);
      char* email = strtok_r(nullptr, ",", &data_mutable);
      char* data = strtok_r(nullptr, ",", &data_mutable);

      expr->uType = *type;
      expr->firstName = fname;
      expr->lastName = lname;
      expr->uEmail = email;
      expr->uData = data;
    }
    if (expr->op == ASSIGN_ISSUE) {
      char* iid = strtok_r(nullptr, ",", &data_mutable);
      char* uid = strtok_r(nullptr, ",", &data_mutable);

      expr->id = std::stod((std::string)iid);
      expr->uid = std::stod((std::string)uid);
    }
}

void handleIssues(expression exp,
                  const std::shared_ptr<restbed::Session>& session) {
  nlohmann::json resultJSON;
  Issue* i;
  std::string result;
  std::vector<std::string> issues, users, comments, search;
  std::tuple<std::string, std::string> name;
  int type, count = 0;

  switch (exp.op) {
    case ADD_ISSUE:
        is.createIssue(exp.title, exp.brand, exp.comp);
        resultJSON["title"] = is.listIssues().back()->getTitle();
        resultJSON["brand"] = is.listIssues().back()->getBrandString();
        resultJSON["comp"] = is.listIssues().back()->getComponentString();
        if (am.getAssigned(exp.id) == 0) {
          result = "N/A";
        } else {
        result = um.getUser(am.getAssigned(exp.id))->getLastName();
        result.append(", ");
        result.append(um.getUser(am.getAssigned(exp.id))->getFirstName());
        result.append(" ID = ");
        result.append(std::to_string(um.getUser(am.getAssigned(exp.id))
        ->getID()));
        }

        resultJSON["assigned"] = result;
        type = 1;
        break;
    case GET_ISSUE:
        if (am.getAssigned(exp.id) == 0) {
          result = "N/A";
        } else {
        result = um.getUser(am.getAssigned(exp.id))->getLastName();
        result.append(", ");
        result.append(um.getUser(am.getAssigned(exp.id))->getFirstName());
        result.append(" ID = ");
        result.append(std::to_string(um.getUser(am.getAssigned(exp.id))
        ->getID()));
        }

        resultJSON["assigned"] = result;
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["brand"] = is.getIssue(exp.id)->getBrandString();
        resultJSON["comp"] = is.getIssue(exp.id)->getComponentString();
        type = 2;
        break;
    case SET_ISSUE_TITLE:
        is.getIssue(exp.id)->setTitle(exp.title);
        if (am.getAssigned(exp.id) == 0) {
          result = "N/A";
        } else {
        result = um.getUser(am.getAssigned(exp.id))->getLastName();
        result.append(", ");
        result.append(um.getUser(am.getAssigned(exp.id))->getFirstName());
        result.append(" ID = ");
        result.append(std::to_string(um.getUser(am.getAssigned(exp.id))
        ->getID()));
        }
        resultJSON["assigned"] = result;
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["brand"] = is.getIssue(exp.id)->getBrandString();
        resultJSON["comp"] = is.getIssue(exp.id)->getComponentString();
        type = 5;
        break;
    case ASSIGN_ISSUE:
        am.assignIssue(exp.id, exp.uid);
        result.append("Issue (");
        result.append(std::to_string(is.getIssue(exp.id)->getID()));
        result.append(": ");
        result.append(is.getIssue(exp.id)->getTitle());
        result.append(") has been assigned to User (");
        result.append(std::to_string(um.getUser(exp.uid)->getID()));
        result.append(": ");
        result.append(um.getUser(exp.uid)->getLastName());
        result.append(", ");
        result.append(um.getUser(exp.uid)->getFirstName());
        result.append(")");
        resultJSON["result"] = result;
        type = 4;
        break;
    case LIST_ISSUES:
        issues.clear();
        for (Issue* i : is.listIssues()) {
          issues.push_back(std::to_string(i->getID()));
          issues.back().append(" : ");
          issues.back().append(i->getTitle());
        }
        resultJSON["issues"] = issues;
        type = 3;
        break;
    case DELETE_ISSUE:
        issues.clear();
        is.deleteIssue(exp.id);
        for (Issue* i : is.listIssues()) {
          issues.push_back(std::to_string(i->getID()));
          issues.back().append(" : ");
          issues.back().append(i->getTitle());
        }
        resultJSON["issues"] = issues;
        type = 6;
        break;
    case ADD_COMMENT:
        is.getIssue(exp.id)->addComment(exp.cmt);
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["comment"] = is.getIssue(exp.id)->listComments().back()
        ->getDescription();
        type = 11;
        break;
    case GET_COMMENT:
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["comment"] = is.getIssue(exp.id)->getComment(exp.cid)
        ->getDescription();
        type = 12;
        break;
    case UPDATE_COMMENT:
        is.getIssue(exp.id)->getComment(exp.cid)->updateDescription(exp.cmt);
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["comment"] = is.getIssue(exp.id)->getComment(exp.cid)
        ->getDescription();
        type = 14;
        break;
    case LIST_COMMENTS:
        comments.clear();
        for (Comment* c : is.getIssue(exp.id)->listComments()) {
          comments.push_back(std::to_string(c->getCommentID()));
          comments.back().append(" : ");
          comments.back().append(c->getDescription());
        }
        resultJSON["title"] = is.getIssue(exp.id)->getTitle();
        resultJSON["comments"] = comments;
        type = 13;
        break;
    case ADD_USER:
        users.clear();
        name = std::tie(exp.firstName, exp.lastName);
        um.createUser(exp.uType, std::make_tuple(exp.firstName, exp.lastName),
        exp.uEmail, exp.uData);
        for (User* u : um.listAllUsers()) {
          users.push_back(std::to_string(u->getID()));
          users.back().append(" : ");
          users.back().append(u->getLastName());
          users.back().append(", ");
          users.back().append(u->getFirstName());
        }
        resultJSON["users"] = users;
        type = 21;
        break;
    case LIST_USERS:
        users.clear();
        for (User* u : um.listAllUsers()) {
          users.push_back(std::to_string(u->getID()));
          users.back().append(" : Name:");
          users.back().append(u->getLastName());
          users.back().append(", ");
          users.back().append(u->getFirstName());
          users.back().append(" / ");
          // users.back().append("Access Level: ");
          // users.back().append(u->getUserType());
          users.back().append("Email: ");
          users.back().append(u->getEmail());
        }

        resultJSON["users"] = users;
        type = 22;
        break;
    case DELETE_USER:
        users.clear();
        users.push_back(um.getUser(exp.uid)->getLastName());
        users.back().append(", ");
        users.back().append(um.getUser(exp.uid)->getFirstName());
        um.deleteUser(um.getUser(exp.uid));
        resultJSON["users"] = users;
        type = 23;
        break;
  }

  resultJSON["type"] = type;
  std::string response = resultJSON.dump();

  session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length",
  std::to_string(response.length()) }, CLOSE_CONNECTION });
}

void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
    expression exp;
    const char* data = reinterpret_cast<const char*>(body.data());
    parse(data, &exp);
    handleIssues(exp, session);
}

void post_method_handler(const std::shared_ptr<restbed::Session>&
  session) {
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_request);
}

void get_method_handler(const std::shared_ptr<restbed::Session>& session) {
  const auto request = session->get_request();

  expression exp;
  exp.op = UNKNOWN;
  exp.id = 0;
  exp.cid = 0;
  // exp.search = '\0';

  if (request->has_query_parameter("op")) {
      set_operation(&exp, request->get_query_parameter("op").c_str());
      if (request->has_query_parameter("id")) {
          exp.id = stod(request->get_query_parameter("id"));
      }
      if (request->has_query_parameter("cid")) {
          exp.cid = stod(request->get_query_parameter("cid"));
      }
      if (request->has_query_parameter("search")) {
          exp.search = request->get_query_parameter("search");
      }
  }
  handleIssues(exp, session);
}

int main(const int, const char**) {
  auto resource_issue = std::make_shared<restbed::Resource>();
  resource_issue->set_path("/issue");
  resource_issue->set_method_handler("GET", get_method_handler);
  resource_issue->set_method_handler("POST", post_method_handler);
  resource_issue->set_method_handler("PUT", post_method_handler);
  resource_issue->set_method_handler("DELETE", post_method_handler);

  auto resource_user = std::make_shared<restbed::Resource>();
  resource_user->set_path("/user");
  resource_user->set_method_handler("GET", get_method_handler);
  resource_user->set_method_handler("POST", post_method_handler);
  resource_user->set_method_handler("PUT", post_method_handler);

  auto settings = std::make_shared<restbed::Settings>();
  settings->set_port(7007);

  restbed::Service service;
  service.publish(resource_issue);
  // service.publish(resource_user);

  service.start(settings);
  return EXIT_SUCCESS;
}
