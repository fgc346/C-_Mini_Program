/*
 * @Author: fenggaochao
 * @Date: 2022-08-05 19:28:04
 * @LastEditTime: 2022-08-05 19:57:56
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/base/declare_implace_demo.cpp
 */
#include "stdio.h"

// int f(int a)
// {
//   printf("[int], a = %d\n",a);
// }
int f (int a);


int main()
{
  f(10);
  return 0;
}

int f(const int a)
{
  printf("a = %d\n", a);
}