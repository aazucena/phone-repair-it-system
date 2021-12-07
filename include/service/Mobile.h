#ifndef INCLUDE_MOBILE_H_
#define INCLUDE_MOBILE_H_

#include <string>
#include <vector>

class Mobile {
 public:
    enum Brand {APPLE, ANDROID, OTHER};
    enum Component {NONE, SCREEN, CAMERA, BATTERY, CHARGE_PORT, TOUCH_SCREEN};

    Mobile() {}
    virtual ~Mobile() {}

    void setBrand(char b);
    void setComponent(char c);
    void setSerialNum(std::string serial);

    char getBrand();
    char getComponent();
    std::string getSerialNum();

    std::string getBrandString();
    std::string getComponentString();

 private:
    Brand brand;
    Component component;
    std::string serialNum;
};

#endif
