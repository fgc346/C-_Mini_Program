#include <iostream>
#include <stdio.h>
#include <functional>

#include "factory.h"

using namespace std;
using namespace apollo::common::util;
// 抽象工厂模板

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


class Base {
public:
    Base(){
        std::cout << "the Base is contruct" << std::endl;
    }
    virtual void show(){}
    virtual ~Base(){}

};
class Derived : public Base {
public:
    Derived() {
        std::cout << "the Derived is construct" << std::endl;
    }
    virtual void show() override {
        std::cout << "the Derived is show" << std::endl;
    }
};
// using Function = []() -> Base* (){new Derived()};
// Base* (*Function)();

//函数指针的使用
using BaseCreator = Base *(*)();

Base* CreateObj()
{
    return new Derived();
}

std::unique_ptr<Base> CreateObj_New(BaseCreator function)
{
    return std::unique_ptr<Base>(function());
}

std::unique_ptr<Base> CreateObj_New2()
{
    std::cout << "CreateObj_New2 is called" << std::endl;
    Base* base_ptr = new Derived();
    return std::unique_ptr<Base>(base_ptr);
}

struct myDel
{
  void operator()(int *p)
  {
    std::cout << "call myDel that is self define function delete" << std::endl;
  }
};


int main()
{
    // int a = 3;
    // int *p_a = &a;
    // std::unique_ptr<int,std::function<void(int*)>> ptr_a(p_a, 
    // [](int* p) -> void {std::cout << "delete p_a,*p =  " << *p << std::endl;});
    // std::cout << "*ptr_a = " << *ptr_a << std::endl;
    // std::cout << "*p_a = " << *p_a << std::endl;

    int *p_b = new int(10);
    // std::unique_ptr<int, std::function<void(int*)>> ptr_b(p_b, 
    // [](int* p) -> void {std::cout << "call self define delete function" << std::endl;});
    std::unique_ptr<int,myDel> ptr_b(p_b, myDel());
    std::cout << "*ptr_b = " << *ptr_b << std::endl;
    std::cout << "*p_b = " << *p_b << std::endl;
    *p_b = 1;
    std::cout << "after new value to p_b" << std::endl;
    std::cout << "*ptr_b = " << *ptr_b << std::endl;
    std::cout << "*p_b = " << *p_b << std::endl;
    delete p_b;
    if (ptr_b)
    {
      std::cout << "*ptr_b = " << *ptr_b << std::endl;
    }
    else {
      std::cout << "ptr_b pointer object is destory" << std::endl;
    }

    return 0;

    auto base_ptr = CreateObj_New(CreateObj);
    CreateObj_New2();

    Base* base_ptr2 = new Derived();
    std::unique_ptr<Base> base_ptr_uni(base_ptr2);
    base_ptr_uni->show();

    std::cout << "the new using unique pointer" << std::endl;
    Derived Derived_1;
    Base* base_p = &Derived_1;
    std::unique_ptr<Base> base_ptr_uni2(base_p);
    base_ptr_uni2->show();
    return 0;

    Factory<std::string, Phone> phone_factory;
    phone_factory.Register("iphone", []() -> Phone* {return new iPhone();});
    phone_factory.Register("huawei", []() -> Phone* {return new HuaweiPhone();});
    auto iphone = phone_factory.CreateObject("iphone");
    iphone->show();
    auto huawei_phone = phone_factory.CreateObject("huawei");
    huawei_phone->show();

    Factory<std::string, Pad> pad_factory;
    pad_factory.Register("iphone", []() -> Pad* {return new iPad();});
    pad_factory.Register("huawei", []() -> Pad* {return new HuaweiPad();});
    auto ipad = pad_factory.CreateObject("iphone");
    auto huawei_pad = pad_factory.CreateObject("iphone");
    auto ipad_2 = pad_factory.CreateObject("iphone");
    std::cout << "sizeof iPad = " << sizeof(iPad) << std::endl;
    if (ipad == huawei_pad)
    {
        std::cout << "iphone and huawei_pad is same class" << std::endl;
    }
    else
    {
        std::cout << "iphone and huawei_pad is not same class" << std::endl;
    }
    if (ipad)
    {
        ipad->show();
    }
    if (huawei_pad)
    {
        huawei_pad->show();
    }
    return 0;
}