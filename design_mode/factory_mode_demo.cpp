#include <iostream>
#include <stdio.h>

using namespace std;

//抽象产品类
class Phone {
public:
    virtual ~Phone() {}
    virtual void show() = 0;
};

//具体产品类
class iPhone : public Phone {
public:
    void show() override {
        std::cout << "I'm Apple" << std::endl;
    }
};

class Huawei : public Phone {
public:
    void show() override {
        std::cout << "I'm Huawei" << std::endl;
    }
};

enum class  PhoneType {
    IPHONE, HUAWEI
};

//工厂类
class PhoneFactory {
public:
    Phone* createPhone(PhoneType kType) {
        switch (kType)
        {
        case PhoneType::IPHONE:
        {
            return new iPhone();
            break;
        }
        case PhoneType::HUAWEI:
        {
            return new Huawei();
            break;
        }   
        
        default:
            break;
        }
    }
};



int main()
{
    PhoneFactory phone_factory;
    Phone* huawei = phone_factory.createPhone(PhoneType::HUAWEI);
    if (huawei)
    {
        huawei->show();
        delete huawei;
        huawei = nullptr;
    }
    Phone* apple = phone_factory.createPhone(PhoneType::IPHONE);
    if (apple)
    {
        apple->show();
        delete apple;
        apple = nullptr;
    }
    return 0;
}