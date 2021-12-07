#include "gtest/gtest.h"

#include "MockUserUI.h"

#include "UserManager.h"
#include "Admin.h"
#include "Client.h"
#include <iostream>
#include <tuple>
#include <list>

using ::testing::Return;
using ::testing::_;
using ::testing::Expectation;

TEST(TestUserUI, AdminInputTest) {
  MockUserUI ui;

  EXPECT_CALL(ui, requestName())
  .Times(1)
  .WillOnce(Return(std::make_tuple("Admin", "Test")));

  EXPECT_CALL(ui, requestEmail())
  .Times(1)
  .WillOnce(Return("admin@test.com"));

  EXPECT_CALL(ui, requestUserData())
  .Times(1)
  .WillOnce(Return("Reporter"));

  EXPECT_CALL(ui, chooseUserType())
  .Times(1)
  .WillOnce(Return('A'));

  EXPECT_CALL(ui, requestUser())
  .Times(1)
  .WillOnce(Return(2));

  UserManager um;

  um.createUser(ui.chooseUserType(),
                    ui.requestName(),
                    ui.requestEmail(),
                    ui.requestUserData());
                    
  User* admin = um.getUser(ui.requestUser());

  //EXPECT_EQ(admin->getUserType(), 'A');
  EXPECT_EQ(admin->getID(), 2);
  EXPECT_EQ(admin->getFirstName(), "Admin");
  EXPECT_EQ(admin->getLastName(), "Test");
  EXPECT_EQ(admin->getEmail(), "admin@test.com");
  //EXPECT_EQ(admin->getPosition(), "Reporter");
}

TEST(TestUserUI, ClientInputTest) {
  MockUserUI ui;

  EXPECT_CALL(ui, requestName())
  .Times(1)
  .WillOnce(Return(std::make_tuple("Client", "Test")));

  EXPECT_CALL(ui, requestEmail())
  .Times(1)
  .WillOnce(Return("client@test.com"));

  EXPECT_CALL(ui, requestUserData())
  .Times(1)
  .WillOnce(Return("A0A0A0"));

  EXPECT_CALL(ui, chooseUserType())
  .Times(1)
  .WillOnce(Return('C'));

  EXPECT_CALL(ui, requestUser())
  .Times(1)
  .WillOnce(Return(2));

  UserManager um;

  um.createUser(ui.chooseUserType(),
                    ui.requestName(),
                    ui.requestEmail(),
                    ui.requestUserData());

  User* client = um.getUser(ui.requestUser());

  //EXPECT_EQ(admin->getUserType(), 'A');
  EXPECT_EQ(client->getID(), 2);
  EXPECT_EQ(client->getFirstName(), "Client");
  EXPECT_EQ(client->getLastName(), "Test");
  EXPECT_EQ(client->getEmail(), "client@test.com");
  //EXPECT_EQ(admin->getPostalCode(), "A0A0A0");

}
