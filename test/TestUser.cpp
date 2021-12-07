/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly: Aldrin Azucena <a.azucena@uleth.ca>
*/

#include "Client.h"
#include "Admin.h"
#include "gtest/gtest.h"
#include <iostream>

TEST (TestUser, getTest) {
  Client cli(0, "Bob", "Jones");
  EXPECT_EQ(cli.getID(), 0);
  EXPECT_EQ(cli.getFirstName(), "Bob");
  EXPECT_EQ(cli.getLastName(), "Jones");
}

TEST (TestUser, setTest) {
  Client cli(0, "Bob", "Jones");
  cli.setEmail("test@gmail.com");
  cli.setPostalCode("A1B2C3");
  EXPECT_EQ(cli.getEmail(), "test@gmail.com");
  EXPECT_EQ(cli.getPostalCode(), "A1B2C3");

  Admin adm(1, "James", "Jones");
  adm.setEmail("cool@gmail.com");
  adm.setPosition("Dummy");
  EXPECT_EQ(adm.getEmail(), "cool@gmail.com");
  EXPECT_EQ(adm.getPosition(), "Dummy");
}

TEST (TestUser, operatorTests) {
  Admin adm1(0, "Bob", "Jones");
  Admin adm2(1, "James", "Jones");

  EXPECT_FALSE((adm1 == adm2));
  EXPECT_NO_THROW({
    std::cout << adm1 << std::endl;
  });
}
