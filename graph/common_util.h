/*
 * @Author: fenggaochao
 * @Date: 2023-02-24 13:18:44
 * @LastEditTime: 2023-02-24 13:26:25
 * @LastEditors: fenggaochao
 * @Description:
 * @FilePath: /C++_Mini_Program/graph/common_util.h
 */
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <limits>

const char DECIMAL_POINT='.';

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

// s:待分割的字符串
// v:分割后的字符串
// c：分隔符
void SplitString(const std::string &source_str, std::vector<std::string> &destination_strs, const std::string &sp)
{
  std::string::size_type pos1, pos2;
  pos2 = source_str.find(sp);
  pos1 = 0;
  while (std::string::npos != pos2)
  {
    destination_strs.push_back(source_str.substr(pos1, pos2 - pos1));
    pos1 = pos2 + sp.size();
    pos2 = source_str.find(sp, pos1);
  }
  // 如果源文件的最后一个字符是分隔符，pos1的大小就等于字符串的长度
  if (pos1 != source_str.length())
    destination_strs.push_back(source_str.substr(pos1));
}

std::string DoFraction(double value, int decplaces = 3)
{
  std::ostringstream out;
  int prec = std::numeric_limits<double>::digits10; // 18
  out.precision(prec);                      // 覆盖默认精度
  out << value;
  std::string str = out.str(); // 从流中取出字符串
  size_t n = str.find(DECIMAL_POINT);
  if ((n != std::string::npos)              // 有小数点吗？
      && (str.size() > n + decplaces)) // 后面至少还有decplaces位吗？
  {
    str[n + decplaces] = '\0'; // 覆盖第一个多余的数
  }

  // str.swap(std::string(str.c_str())); // 删除nul之后的多余字符

  return str;
}