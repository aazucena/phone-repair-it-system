/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "UserManager.h"
#include "Client.h"
#include "Admin.h"
#include "ClientUI.h"
#include "AdminUI.h"
#include "gtest/gtest.h"
#include <tuple>

TEST(TestUserManager, addUserTest) {
     User* u = new Client(1, "Test", "1");
     User* u1 = new Admin(2, "Client", "2");
     UserManager manager;
     manager.addUser(u);
     manager.addUser(u1);
     std::list<User*> ulist = manager.listAllUsers();
     EXPECT_EQ(ulist.front()->getID(), 1);
     EXPECT_EQ(ulist.back()->getID(), 2);
}

TEST(TestUserManager, getUserTest) {
     User* u = new Client(1, "Test", "1");
     User* u1 = new Admin(2, "Client", "2");
     UserManager manager;
     manager.addUser(u);
     manager.addUser(u1);
     EXPECT_EQ(manager.getUser(1)->getID(), 1);
     EXPECT_EQ(manager.getUser(2)->getID(), 2);
}

TEST(TestUserManager, createUserTest) {
     UserManager manager;
     manager.createUser('C', std::make_tuple("Client", "0"),
                                      "Bob@gmail.com", "A0B2C3");
     EXPECT_EQ(manager.getUser(1)->getID(), 1);
     EXPECT_EQ(manager.getUser(1)->getFirstName(), "Client");
     EXPECT_EQ(manager.getUser(1)->getLastName(), "0");
     EXPECT_EQ(manager.getUser(1)->getEmail(), "Bob@gmail.com");

     manager.createUser('A', std::make_tuple("Admin", "1"),
                                      "John@gmail.com", "Reporter");
     EXPECT_EQ(manager.getUser(2)->getID(), 2);
     EXPECT_EQ(manager.getUser(2)->getFirstName(), "Admin");
     EXPECT_EQ(manager.getUser(2)->getLastName(), "1");
     EXPECT_EQ(manager.getUser(2)->getEmail(), "John@gmail.com");
}

TEST(TestUserManager, deleteUserTest) {
     User* u = new Client(1, "Test", "1");
     User* u1 = new Admin(2, "Client", "2");
     UserManager manager;
     manager.addUser(u);
     manager.addUser(u1);
     manager.deleteUser(u);
     std::list<User*> ulist = manager.listAllUsers();
     EXPECT_EQ(ulist.size(), 1);
}

//Mock Test for this later
/*
TEST(TestUserManager, viewerTest) {
    UserManager manager;
    int choice;
    EXPECT_NO_THROW({
      choice = manager.getViewer()->requestUserViewer();
    });
    // 0 = AdminUI; 1 = ClientUI
    manager.setViewer(choice);
    EXPECT_NO_THROW({
      char type = manager.getViewer()->chooseUserType();
    });
    EXPECT_NO_THROW({
      auto fullname = manager.getViewer()->requestName();
    });
    EXPECT_NO_THROW({
      std::string email = manager.getViewer()->requestEmail();
    });
    EXPECT_NO_THROW({
      std::string data = manager.getViewer()->requestUserData();
    });
}
*/
