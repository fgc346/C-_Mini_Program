#include <iostream>
#include <stdio.h>

using namespace std;
//
// 抽象工厂模式和工厂方法模式类似
// 有四个大的类：
// 1 抽象产品类
// 2 具体产品类
// 3 抽象工厂类
// 4 具体工厂类

// 抽象工厂模式中 抽象工厂类不只提供创建单一的抽象产品类，具体工厂类同样不再提供创建单一的抽象产品类，而是可以创建多个。

//抽象产品类1
class Phone {
public:
    virtual ~Phone() {}
    virtual void show() = 0;
};

//具体产品类11
class iPhone : public Phone {
public:
    void show() override {
        std::cout << "I'm iPhone" << std::endl;
    }
};
// 具体产品类12
class HuaweiPhone : public Phone {
public:
    void show() override {
        std::cout << "I'm Huawei phone" << std::endl;
    }
};


//抽象产品类2
class Pad {
public:
    virtual void show() = 0;
    virtual ~Pad() {}
};

//具体产品类21
class HuaweiPad : public Pad {
public:
    void show() override {
        std::cout << "I'm Huawei Pad" << std::endl;
    }
};

// 具体产品类22
class iPad : public Pad {
public:
    void show() {
        std::cout << "I'm iPad" << std::endl;
    }
};

//抽象工厂
class DigitalFactory {
public:
    virtual Phone* createPhone() = 0;
    virtual Pad* createPad() = 0;
};

// 具体工厂1
class HuaweiFactory : public DigitalFactory {
public:
    Phone* createPhone() override {
        return new HuaweiPhone();
    }
    Pad* createPad() override {
        return new HuaweiPad();
    }
};

// 具体工厂2
class AppleFactory : public DigitalFactory {
public:
    Phone* createPhone() override {
        return new iPhone();
    }
    Pad* createPad() override {
        return new iPad();
    }
};





int main()
{
    HuaweiFactory huawei_factroy;
    Phone* huawei_phone = huawei_factroy.createPhone();
    huawei_phone->show();
    delete huawei_phone;
    huawei_phone = nullptr;
    Pad* huawei_pad = huawei_factroy.createPad();
    huawei_pad->show();
    delete huawei_pad;
    AppleFactory iphone_factory;
    Phone* apple_phone = iphone_factory.createPhone();
    apple_phone->show();
    delete apple_phone;
    apple_phone = nullptr;
    Pad* apple_pad = iphone_factory.createPad();
    apple_pad->show();
    delete apple_pad;
    apple_pad = nullptr;
    return 0;
}