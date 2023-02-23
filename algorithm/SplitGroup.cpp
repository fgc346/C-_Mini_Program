/*
 * @Author: fenggaochao
 * @Date: 2023-02-16 14:58:21
 * @LastEditTime: 2023-02-16 17:15:07
 * @LastEditors: fenggaochao
 * @Description: 对一组数字进行分组
 * @FilePath: /C++_Mini_Program/algorithm/SplitGroup.cpp
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

// 对一个数组，根据给定的数字，进行分割
std::vector<std::vector<int>> SplitArrayByNum(std::vector<int> &original_arr, int num)
{
  std::sort(original_arr.begin(), original_arr.end());
  std::vector<std::vector<int>> groups_arr;
  if (original_arr.empty())
  {
    return groups_arr;
  }
  // 将第一个元素加入第一个分组
  std::vector<int> tmp_arr_group = {original_arr.front()};
  for (size_t i = 0; i + 1 < original_arr.size(); ++i)
  {
    //判断下一个元素是否应该进入新的分组
    if(original_arr[i + 1] - original_arr[i] > num)
    {
      groups_arr.emplace_back(tmp_arr_group);
      tmp_arr_group.clear();
    }
    tmp_arr_group.emplace_back(original_arr[i + 1]);
  }
  //将最后一个分组加入最后的分组列表中
  groups_arr.emplace_back(tmp_arr_group);
  return groups_arr;
}


// 对一个数组，根据给定的数字，进行分割
std::vector<std::vector<int>> SplitArrayByNum2(std::vector<int> &original_arr, int num)
{
  std::sort(original_arr.begin(), original_arr.end());
  std::vector<std::vector<int>> groups_arr;
  if (original_arr.empty())
  {
    return groups_arr;
  }
  // 将第一个元素加入第一个分组
  std::vector<int> tmp_arr_group = {original_arr.front()};
  for (size_t i = 1; i  < original_arr.size(); ++i)
  {
    //判断当前元素是否应该进入新的分组
    if(original_arr[i] - original_arr[i-1] > num)
    {
      groups_arr.emplace_back(tmp_arr_group);
      tmp_arr_group.clear();
    }
    tmp_arr_group.emplace_back(original_arr[i]);
  }
  //将最后一个分组加入最后的分组列表中
  groups_arr.emplace_back(tmp_arr_group);
  return groups_arr;
}

int main()
{
  std::vector<int> original_arr = {1,4, 5,10,15,30,26,18,80,50,100,42,55};
  for (const auto elem : original_arr)
  {
    std::cout << " " << elem;
  }
  std::cout << std::endl;
  std::cout << " the orignal num size = " << original_arr.size() << std::endl;
  int num = 0;
  std::cout << "please input split num " << std::endl;
  while(std::cin >> num)
  {
    std::cout << " now split num is : " << num << std::endl;
    auto groups_arr = SplitArrayByNum2(original_arr, num);
    int group_idx = 0;
    for (const auto &group : groups_arr)
    {
      ++group_idx;
      std::cout << " the group index : " << group_idx  << " the size of group " <<  group.size() << std::endl;
      for (const auto &elem : group)
      {
        std::cout << " " << elem;
      }
      std::cout << std::endl;
    }
  std::cout << "please input split num " << std::endl;

  }
  return 0;
}