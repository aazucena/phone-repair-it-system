#ifndef MOCKUSERUI_H_INCLUDED
#define MOCKUSERUI_H_INCLUDED

#include "gmock/gmock.h"
#include "UserUI.h"
#include <string>
#include <tuple>

class MockUserUI : public UserUI {
 public:
    MockUserUI() {}
    virtual ~MockUserUI() {}

    MOCK_METHOD0(requestUserData, std::string());
    MOCK_METHOD0(requestName, std::tuple<std::string, std::string>());
    MOCK_METHOD0(requestUser, unsigned int());
    MOCK_METHOD0(chooseUserType, char());
    MOCK_METHOD0(requestEmail, std::string());
};

#endif
