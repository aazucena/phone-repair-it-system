/*
* CPSC 3720 Fall 2020
* Copyright 2020
* Team Gnarly:
*/

#include "Mobile.h"
#include <string>
#include <vector>

void Mobile::setBrand(char b) {
  switch (b) {
    case 'a':
      brand = APPLE;
      break;

    case 's':
      brand = ANDROID;
      break;

    default:
      brand = OTHER;
      break;
  }
}

void Mobile::setComponent(char c) {
  switch (c) {
    case 's':
      component = SCREEN;
      break;

    case 'c':
      component = CAMERA;
      break;

    case 'b':
      component = BATTERY;
      break;

    case 'p':
      component = CHARGE_PORT;
      break;

    case 't':
      component = TOUCH_SCREEN;
      break;

    default:
      component = NONE;
      break;
  }
}

void Mobile::setSerialNum(std::string serial) {
  serialNum = serial;
}

char Mobile::getBrand() {
  char b;

  switch (brand) {
    case APPLE:
      b = 'a';
      break;

    case ANDROID:
      b = 's';
      break;

    default:
      b = 'n';
      break;
  }

  return b;
}

char Mobile::getComponent() {
  char c;

  switch (component) {
    case SCREEN:
      c = 's';
      break;

    case CAMERA:
      c = 'c';
      break;

    case BATTERY:
      c = 'b';
      break;

    case CHARGE_PORT:
      c = 'p';
      break;

    case TOUCH_SCREEN:
      c = 't';
      break;

    default:
      c = 'n';
      break;
  }

  return c;
}

std::string Mobile::getSerialNum() {
  return serialNum;
}

std::string Mobile::getBrandString() {
  std::string b;

  switch (brand) {
    case APPLE:
      b = "Apple";
      break;

    case ANDROID:
      b = "Android";
      break;

    default:
      b = "Other";
      break;
  }

  return b;
}

std::string Mobile::getComponentString() {
  std::string c;

  switch (component) {
    case SCREEN:
      c = "Screen";
      break;

    case CAMERA:
      c = "Camera";
      break;

    case BATTERY:
      c = "Battery";
      break;

    case CHARGE_PORT:
      c = "Charge port";
      break;

    case TOUCH_SCREEN:
      c = "Touch screen";
      break;

    default:
      c = "None";
      break;
  }

  return c;
}
