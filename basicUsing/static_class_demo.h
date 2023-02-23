#pragma once
#include <stdio.h>
#include <vector>
#include <string>
class Test {
public:
	int value;
	Test(int x) :value(x) {};
	static const int num = 3;//声明
    static const int age = 10;
	void print() {
		//对静态成员进行取地址操作
		const int* p = &Test::num;
		printf("value : %d\n", *p);
	}
};

const int Test::num;  //静态成员变量在类外定义
const int Test::age;

void printAge(const int &age)
{
    printf("printAge, the age = %d\n", age);
}

// Data类是聚合类，所有的变量都是字面值类型，所以是字面值常量类型
struct Data{
    int ival;
    // std::string s;
    bool bval;
};

//Data_1 不是字面值常量类型
struct Data_1{
    int ival;
    std::string str;
};

// Debug 是字面值常量类型
class Debug{
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b){}
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
    constexpr bool any()
    {
        return hw || io || other;
    }
    void set_io(bool b) {
        io = b;
    }
    void set_hw(bool b)
    {
        hw = b;
    }
    void set_other(bool b)
    {
        other = b;
    }

private:
    bool hw;
    bool io;
    bool other;
};

//全面梳理static const与static constexpr的类内数据成员初始化
//梳理静态成员变量的各种场景的类内初始化

class Example {
public:
    // 整型的静态成员的声明
    static bool b_1;
    static char c_1;
    static int i_1;

    //浮点型的数据成员
    static float f_1;
    static double d_1;

    // static int i_2 = 1;     //错误：带有类内初始值设定项的成员必须为常量
    // static double d_2 = 3.14;   //错误：带有类内初始值设定项的成员必须为常量


    //整型的静态成员 const
    static const bool cb1;
    static const char cc1;
    static const int  ci1;

    // 浮点型的数据成员
    static const float cf1;
    static const double cd1;

    //整型的静态成员变量  类内初始化
    static const bool cb2 = false;
    static const char cc2 = 'b';
    static const int ci2 = 2;

    //浮点型的数据成员
    //错误："const float" 类型的成员不能包含类内初始值的设定项
    // static const float cf2 = 3.5;
    //错误：“const doule" 类型的成员不能包含类内初始值设定项
    // static const double cd2 = 4.5;


    // char m1[ci1]; //错误：i1的常量还未初始化
    char m2[ci2];


    //static constexpr 数据成员,必须类内初始化,类型为字面值常量类型
    // 整型的静态成员
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    // static constexpr bool cexprb1;
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    // static constexpr char cexprc1;
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    // static constexpr int cexpri1;

    //浮点型的数据成员
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    // static constexpr float cexprf1;
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    // static constexpr double cexprd1;

    //整型的静态成员变量
    static constexpr bool cexprb2 = false;
    static constexpr char cexprc2 = 'd';
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    static constexpr int cexpri2 = 20;

    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    static constexpr float cexprf2 = 1.85;
    // 错误：constexpr 静态数据成员声明需要类内初始值设定项
    static constexpr double cexprd2 = 2.85;



//   static double rate = 6.5;
  static constexpr double rate = 6.5;
  static const int vecSize = 20;
//   static std::vector<double> vec1(100);  //
//   static std::string  str("aaaa");
  static std::vector<double> vec;
  static double arr[vecSize];
//   static constexpr Data data = {0, "Anna"};

  static constexpr Debug debug = Debug();
  static constexpr Data data = {100, true};
};

const int Example::vecSize;
std::vector<double> vec(Example::vecSize);

//整型的静态成员变量的定义
bool Example::b_1 = true;
char Example::c_1 = 'a';
int Example::i_1 = 1;

//浮点型静态成员变量的定义
float Example::f_1 = 1.5;
double Example::d_1 = 2.5;

//const 整型 静态成员变量的定义，并初始化
const bool Example::cb1 = false;
const char Example::cc1 = 'c';
const int Example::ci1 = 10;

//const 整型静态成员变量的定义，已提供类内初始化，无需初始化
const bool Example::cb2;
const char Example::cc2;
const int Example::ci2;

//constexpr  类型的静态成员变量在类内初始化
constexpr bool Example::cexprb2;
constexpr char Example::cexprc2;
constexpr int Example::cexpri2;
constexpr float Example::cexprf2;
constexpr double Example::cexprd2;