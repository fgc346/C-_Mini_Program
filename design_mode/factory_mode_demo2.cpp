#include <iostream>
#include <stdio.h>

#include "factory.h"

using namespace std;
using namespace apollo::common::util;

//抽象产品类
class Phone {
public:
    virtual ~Phone() {}
    virtual void show() = 0;
};

//具体产品类1
class iPhone : public Phone {
public:
    void show() override {
        std::cout << "I'm Apple" << std::endl;
    }
};

// 具体产品类2
class Huawei : public Phone {
public:
    void show() override {
        std::cout << "I'm Huawei" << std::endl;
    }
};

//抽象工厂类
class PhoneFactory {
public:
    virtual Phone* createPhone()  = 0;
    virtual ~PhoneFactory() {}
};

// 具体工厂类1
class iPhoneFactory : public PhoneFactory {
public:
    Phone* createPhone() override {
        return new iPhone();
    }
};

// 具体工厂类2
class HuaweiFactory : public PhoneFactory {
public:
    Phone* createPhone() override {
        return new Huawei();
    }
};


int main()
{
    HuaweiFactory huawei_factroy;
    Phone* huawei = huawei_factroy.createPhone();
    huawei->show();
    delete huawei;
    huawei = nullptr;
    iPhoneFactory iphone_factory;
    Phone* apple = iphone_factory.createPhone();
    apple->show();
    delete apple;
    apple = nullptr;
    return 0;
}