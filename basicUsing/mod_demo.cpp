/*
 * @Author: fenggaochao
 * @Date: 2022-07-05 23:09:04
 * @LastEditTime: 2022-07-05 23:12:40
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/basicUsing/mod_demo.cpp
 */

#include<stdio.h>
#include<math.h>

double NormalizeAngle(const double angle)
{
  double a = std::fmod(angle + M_PI, 2.0 * M_PI);
  if ( a < 0)
  {
    a += 2.0 * M_PI;
  }
  return a - M_PI;
}

int main()
{
  double angle = NormalizeAngle(-2.5 * M_PI);
  printf("angle = %f\n", angle);
  return angle;
}