#ifndef MOCKISSUE_H_INCLUDED
#define MOCKISSUE_H_INCLUDED

#include "gmock/gmock.h"
#include "Issue.h"
#include <string>

class MockIssue : public Issue {
 public:
    MockIssue(int id, std::string title) : Issue(id, title) {}
    virtual ~MockIssue() {}

    MOCK_METHOD0(getID, int());
    MOCK_METHOD1(setTitle, void(std::string title));
};

#endif
