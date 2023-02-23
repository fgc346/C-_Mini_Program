/*
 * @Author: fenggaochao
 * @Date: 2022-06-01 16:51:32
 * @LastEditTime: 2022-06-01 17:28:46
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/basicUsing/classUsing.cpp
 */

#include "class.hpp"

int main()
{
  std::string name("fgc");
  int age = 18;
  // DriveA a(name, age);
  // a.play();
  // printf(" the a.play is called\n");
  // DriveB b(name, age);
  // b.play();
  // printf(" the b.play is called\n");
  {
    //Drive_Drive_C c(name, age);
    Base *pa = new Drive_Drive_C(name, age);
    pa->play();
    delete pa;
  }

  return 0;
}