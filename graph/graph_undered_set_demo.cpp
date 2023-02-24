/*
 * @Author: fenggaochao
 * @Date: 2023-02-24 12:59:45
 * @LastEditTime: 2023-02-24 13:26:41
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C++_Mini_Program/graph/graph_undered_set_demo.cpp
 */
#include "graph_struct_set.h"
#include "depth_first_path_template.h"
#include "common_util.h"

int main(int argc,char* argv[])
{
  std::string file_name(argv[1]);
  int s = std::stoi(argv[2]);
  std::cout << " file_name = " << file_name << " s = " << s << std::endl;
  std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
  GraphByUnorderSet graph_1(srcFile);
  srcFile.close();
  std::cout << graph_1.ToString();

  DepthFirstPaths<GraphByUnorderSet> dfs_path(graph_1, s);
  std::cout << "0-1: " << dfs_path.HasPathTo(1);
  std::cout << " dfs paths: " << std::endl;
  // for (int v = 0; v < graph_1.Vertex(); ++v)
  // {
  //   if (dfs_path.HasPathTo(v))
  //   {
  //     std::cout << s << " to " << v << ": ";
  //     for (auto x : dfs_path.PathTo(v))
  //     {
  //       if (x == s)
  //       {
  //         std::cout << x;
  //       }
  //       else
  //       {
  //         std::cout << "-" << x;
  //       }
  //     }
  //     std::cout << std::endl;
  //   }
  // }
  PrintGraphPath(graph_1, dfs_path, s);
  return 0;
}