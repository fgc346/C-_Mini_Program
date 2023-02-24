/*
 * @Author: fenggaochao
 * @Date: 2023-02-24 13:18:44
 * @LastEditTime: 2023-02-24 13:26:25
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C++_Mini_Program/graph/common_util.h
 */
#pragma once

template <typename A, typename B>
void PrintGraphPath(A a, B b, const int s)
{
  for (int v = 0; v < a.Vertex(); ++v)
  {
    if (b.HasPathTo(v))
    {
      std::cout << s << " to " << v << ": ";
      for (auto x : b.PathTo(v))
      {
        if (x == s)
        {
          std::cout << x;
        }
        else
        {
          std::cout << "-" << x;
        }
      }
      std::cout << std::endl;
    }
  }
}