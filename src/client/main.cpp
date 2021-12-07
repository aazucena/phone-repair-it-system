/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Kevin Baffo <k.baffo@uleth.ca>
*/

#include "IssueUI.h"
#include "UserUI.h"
#include "AdminUI.h"
#include "ClientUI.h"
#include "Exceptions.h"

#include <restbed>
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>



/* Service information */
const char* HOST = "localhost";
const int PORT = 7007;

/* Server operations */
const char* ADD_ISSUE = "Add issue";
const char* GET_ISSUE = "Get issue";
const char* LIST_ISSUES = "List all issues";
const char* SET_ISSUE_TITLE = "Set title";
const char* DELETE_ISSUE = "Delete title";
const char* ADD_COMMENT = "Add comment";
const char* GET_COMMENT = "Get comment";
const char* UPDATE_COMMENT = "Update comment";
const char* LIST_COMMENTS = "Get all comments";
const char* ADD_USER = "Add user";
const char* LIST_USERS = "List users";
const char* DELETE_USER = "Delete user";
const char*  ASSIGN_ISSUE = "Assign issue";

std::shared_ptr<restbed::Request> create_post_issue_request(
                                            const std::string& operation,
                                            const std::string& title,
                                            const char& brand,
                                            const char& component) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(title);
    message.append(",");
    message.append(&brand);
    message.append(",");
    message.append(&component);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_delete_request(
                                            const std::string& operation,
                                            const int& id) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("DELETE");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(std::to_string(id));

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_put_issueTitle_request(
                                                const std::string& operation,
                                                const int& iid,
                                                const std::string& newTitle) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("PUT");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(std::to_string(iid));
    message.append(",");
    message.append(newTitle);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
  }

std::shared_ptr<restbed::Request> create_get_issue_request(
                                                          const std::string& op,
                                                          const int& id) {
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_method("GET");

    request->set_query_parameter("op", op);
    request->set_query_parameter("id", std::to_string(id));

    return request;
  }

std::shared_ptr<restbed::Request> create_post_assignIssue_request(
                                                  const std::string& operation,
                                                  const int& iid,
                                                  const int& uid) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(std::to_string(iid));
    message.append(",");
    message.append(std::to_string(uid));

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_get_all_issues_request(
                                                      const std::string& op) {
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_method("GET");

    request->set_query_parameter("op", op);

    return request;
  }

std::shared_ptr<restbed::Request> create_post_cmt_request(
                                                  const std::string& operation,
                                                  const int& iid,
                                                  const std::string& cmt) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(std::to_string(iid));
    message.append(",");
    message.append(cmt);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_put_cmt_request(
                                                  const std::string& operation,
                                                  const int& iid,
                                                  const int& cid,
                                                  const std::string& cmt) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("PUT");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(std::to_string(iid));
    message.append(",");
    message.append(std::to_string(cid));
    message.append(",");
    message.append(cmt);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
  }

std::shared_ptr<restbed::Request> create_get_all_cmt_request(
                                                    const std::string& op,
                                                    const int& id) {
  std::string uri_str;
  uri_str.append("http://");
  uri_str.append(HOST);
  uri_str.append(":");
  uri_str.append(std::to_string(PORT));
  uri_str.append("/issue");

  auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
  request->set_method("GET");

  request->set_query_parameter("op", op);
  request->set_query_parameter("id", std::to_string(id));

  return request;
}

std::shared_ptr<restbed::Request> create_get_cmt_request(const std::string& op,
                                                         const int& id,
                                                         const int& cid) {
  std::string uri_str;
  uri_str.append("http://");
  uri_str.append(HOST);
  uri_str.append(":");
  uri_str.append(std::to_string(PORT));
  uri_str.append("/issue");

  auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
  request->set_method("GET");

  request->set_query_parameter("op", op);
  request->set_query_parameter("id", std::to_string(id));
  request->set_query_parameter("cid", std::to_string(cid));

  return request;
}

std::shared_ptr<restbed::Request> create_post_addUser_request(
                                                  const std::string& operation,
                                                  const char& type,
                                                  const std::string& fname,
                                                  const std::string& lname,
                                                  const std::string& ml,
                                                  const std::string& data) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append(",");
    message.append(&type);
    message.append(",");
    message.append(fname);
    message.append(",");
    message.append(lname);
    message.append(",");
    message.append(ml);
    message.append(",");
    message.append(data);

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_get_all_users_request(
                                                      const std::string& op) {
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issue");

    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_method("GET");

    request->set_query_parameter("op", op);

    return request;
  }

void handle_response(std::shared_ptr<restbed::Response> response) {
  int status_code = response->get_status_code(), j = 0;
  auto length = response->get_header("Content-Length", 0);
  switch (status_code) {
    case 200: {
      restbed::Http::fetch(length, response);
      std::string responseStr(reinterpret_cast<char*>(
        response->get_body().data()), length);

      nlohmann::json resultJSON = nlohmann::json::parse(responseStr);
      std::string issueTitle, newIssue, newCmt, brand, comp, result, assigned;
      std::vector<std::string> issues;
      int issueType = resultJSON["type"];
      switch (issueType) {
        case 1:  // Added Issue
            std::cout << "\n\t\tNew issue added " << std::endl;
        case 2:  // Get Issue details
        case 5:  // Updated Issue Title
            issueTitle = resultJSON["title"];
            brand = resultJSON["brand"];
            comp = resultJSON["comp"];
            assigned = resultJSON["assigned"];
            std::cout << "\nTitle\t\t: " << issueTitle << std::endl;
            std::cout << "Brand\t\t: " << brand  << std::endl;
            std::cout << "Component\t: " << comp << std::endl;
            std::cout << "Assigned\t: " <<  assigned << std::endl;
            break;
        case 3:  // List all issues
        case 6:  // Delete an issue
            std::cout << "\n\t\t Printing All Issues " << std::endl;
            for (std::string issue : resultJSON["issues"]) {
              std::cout << "\nIssue\t " << issue;
            }
            std::cout << std::endl;
            break;
        case 4:
            result = resultJSON["result"];
            std::cout << result << std::endl;
            break;
        case 7:
            std::cout << "\tFound " << resultJSON["count"] << " matches";
            std::cout << " for " << resultJSON["test"];
            for (std::string s : resultJSON["search"]) {
              std::cout << "\nMatch " << ++j << " : "<< s;
            }
            std::cout << std::endl;
            break;
        case 11:  // Add comment
        case 12:  // Get comment
        case 14:  // Update comment
            issueTitle = resultJSON["title"];
            result = resultJSON["comment"];
            std::cout << "\nTitle\t: " << issueTitle << std::endl;
            std::cout << "Comment\t: " << result << std::endl;
            break;
        case 13:  // List all comments
            issueTitle = resultJSON["title"];
            std::cout << "\nTitle\t: " << issueTitle << std::endl;
            for (std::string cmt : resultJSON["comments"]) {
              std::cout << "\nComment " << cmt;
            }
            std::cout << std::endl;
            break;
        case 21:  // Adding a user
            std::cout << "\n\t\tNew user added " << std::endl;
        case 22:  // List all users
            for (std::string name : resultJSON["users"]) {
              std::cout << "\nUser " << name;
            }
            std::cout << std::endl;
            break;
        case 23:  // Delete user
            result = resultJSON["users"];
            std::cout << "User deleted is: " << result << std::endl;
            break;
        case 0:
            throw cannot_find_issue_error("Server side Error");
            break;
        default:
            throw cannot_find_issue_error("Fatal Error");
            break;
      }
      break;
    }

    case 400: {
      restbed::Http::fetch(length, response);
      fprintf(stderr, "Something went wrong here: %.*s\n", length,
               response->get_body().data());
      break;
    }

    default:
      std::string status = std::to_string(status_code);
      std::cout << "Error " << status << std::endl;

      break;
  }
}

void handle_request_issues(std::shared_ptr<restbed::Request> request,
                           std::shared_ptr<restbed::Response> response) {
  IssueUI* ui;
  UserUI* uui;
  unsigned int issID = -1, uID = -1, i_action = -1;
  std::string status, title;
  char brand, comp;
  system("clear");
  while (true) {
    // system("clear");
    i_action = ui->issuesAction();
    switch (i_action) {
    case 1: {
      title = ui->pickIssue();
      brand = ui->requestMobileBrand();
      comp = ui->requestBrandNewComponent();
      request = create_post_issue_request(ADD_ISSUE, title, brand, comp);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      break;
    }
    case 2: {
      issID = ui->requestIssue();
      request = create_get_issue_request(GET_ISSUE, issID);
      response = restbed::Http::sync(request);
      handle_response(response);
      break;
    }
    case 3: {
      request = create_get_all_issues_request(LIST_ISSUES);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      break;
    }
    case 4: {
      issID = ui->requestIssue();
      uID = uui->requestUser();
      request = create_post_assignIssue_request(ASSIGN_ISSUE, issID, uID);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      break;
    } case 6: {
      issID = ui->requestIssue();
      request = create_delete_request(DELETE_ISSUE, issID);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      break;
    } case 5: {
      issID = ui->requestIssue();
      title = ui->pickIssue();
      request = create_put_issueTitle_request(SET_ISSUE_TITLE, issID, title);
      auto response = restbed::Http::sync(request);
      handle_response(response);
      break;
    }
    default:
      break;
    }
    if (i_action == 0) {
      system("clear");
      break;
    }
  }
}

void handle_request_cmts(std::shared_ptr<restbed::Request> request,
                           std::shared_ptr<restbed::Response> response) {
  IssueUI* ui;
  unsigned int issID = -1, cmtID = -1, c_action = -1;
  std::string newCmt;
  system("clear");
  while (true) {
    c_action = ui->cmtsAction();
    switch (c_action) {
      case 1: {
        issID = ui->requestIssue();
        newCmt = ui->requestNewComment();
        request = create_post_cmt_request(ADD_COMMENT, issID, newCmt);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      case 4: {
        issID = ui->requestIssue();
        cmtID = ui->requestComment();
        newCmt = ui->requestNewComment();
        request = create_put_cmt_request(UPDATE_COMMENT, issID,
         cmtID, newCmt);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      case 2: {
        issID = ui->requestIssue();
        cmtID = ui->requestComment();
        request = create_get_cmt_request(GET_COMMENT, issID, cmtID);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      case 3: {
        issID = ui->requestIssue();
        request = create_get_all_cmt_request(LIST_COMMENTS, issID);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      default:
        break;
      }
    if (c_action == 0) {
      system("clear");
      break;
    }
  }
}

void handle_request_users(std::shared_ptr<restbed::Request> request,
                           std::shared_ptr<restbed::Response> response) {
  UserUI* ui;
  IssueUI* ii;
  unsigned int issID = -1, userID = -1, u_action = -1;
  std::string email, data, fname, lname;
  char type;
  std::tuple<std::string, std::string> name;
  system("clear");
  while (true) {
    // system("clear");
    u_action = ii->userAction();
    switch (u_action) {
      case 1: {
        type = ui->chooseUserType();
        switch (type) {
          case 'A': {
            ui = new AdminUI();
            name = ui->requestName();
            fname = std::get<0>(name);
            lname = std::get<1>(name);
            email = ui->requestEmail();
            data = ui->requestUserData();
            break;
          }
          case 'C': {
            ui = new ClientUI();
            name = ui->requestName();
            fname = std::get<0>(name);
            lname = std::get<1>(name);
            email = ui->requestEmail();
            data = ui->requestUserData();
            break;
          }
        }
        request = create_post_addUser_request(ADD_USER, type, fname, lname,
          email, data);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      case 2: {
        request = create_get_all_users_request(LIST_USERS);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      case 3: {
        userID = ui->requestUser();
        request = create_delete_request(DELETE_USER, userID);
        auto response = restbed::Http::sync(request);
        handle_response(response);
        break;
      }
      default:
        break;
      }
    if (u_action == 0) {
      system("clear");
      break;
    }
  }
}

int main(const int, const char**) {
  IssueUI* ui;
  std::shared_ptr<restbed::Request> request;
  std::shared_ptr<restbed::Response> response;
  unsigned int action = -1;
  system("clear");
  while (true) {
    action = ui->chooseAction();
    if (action == 0) {
      std::cout << "Ready to Exit ... Thank You " << std::endl;
      break;
    } else if (action == 1) {
      handle_request_issues(request, response);
    } else if (action == 2) {
      handle_request_cmts(request, response);
    } else if (action == 3) {
      handle_request_users(request, response);
    } else {
      system("clear");
      std::cout << "Function not yet implemented " << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
