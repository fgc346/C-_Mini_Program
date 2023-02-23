/*
 * @Author: fenggaochao
 * @Date: 2021-10-20 15:50:02
 * @LastEditTime: 2021-10-20 15:55:06
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/base/vector_insert_demo.cpp
 */

#include <vector>
#include <string>
#include <stdio.h>

int main() {
  std::vector<int>  vec1{1, 2, 3, 4};
  std::vector<int> vec2;
  vec2.insert(vec2.end(), vec1.begin(), vec1.begin()+2);
  printf("the element: ");
  for ( auto v1 : vec2)
  {
    printf("%d,", v1);
  }
  printf("\n");
  return 0;
}