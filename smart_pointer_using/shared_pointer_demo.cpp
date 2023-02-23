/*
 * @Author: fenggaochao
 * @Date: 2022-11-02 13:17:04
 * @LastEditTime: 2022-11-02 13:19:54
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/smart_pointer_using/shared_pointer_demo.cpp
 */
#include <iostream>
#include <memory>

int main()
{
  int *ptr = new int(10);
  std::shared_ptr<int> sp_1(ptr);
  std::shared_ptr<int> sp_2(ptr);
  std::cout << "*sp_1 = " << *sp_1 << std::endl;
  std::cout << "*sp_2 = " << *sp_2  << std::endl;
  return 0;

  
  std::unique_ptr<int> p1(new int);
  *p1 = 10;
  std::cout << "*p1 = " << *p1 << std::endl;
  //p 接收p1 释放的堆内存
  int *p = p1.release();
  std::cout << "*p = " << *p << std::endl;
  if (p1)
  {
    std::cout << "p1 is not nullptr" << std::endl;
  }
  else {
    std::cout << "p1 is nullptr" << std::endl;
  }
  std::unique_ptr<int> p2;
  if (p2)
  {
    std::cout << "p2 is not nullptr, *p2 = " << *p2 << std::endl;
  }
  else {
    std::cout << "p2 is nullptr" << std::endl;
  }
  p2.reset(p);
  std::cout << "*p2 = " << *p2 << std::endl;
  if (p)
  {
    std::cout << "*p = " << *p << std::endl;
  }
  else
  {
    std::cout << "p is nullptr" << std::endl;
  }
  return 0;
}