# 这个模板适用于编译某一目录中的指定源文件，且没有调用第三方库，最终编译成一个可执行文件的情况

# 1,设置工程名称，叫“Demo2”，在Linux下可以随便设置
PROJECT(Graph)

# 2,设置 CMake 最低版本号，我电脑装的是3.5
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# 3,设定编译参数
SET(CMAKE_CXX_STANDARD 11) # C++11标准
SET(CMAKE_BUILD_TYPE "Debug") # 也可以是Debug

# 4,设置使用到的源文件和头文件
SET(SRC_LIST
  DijkstraSP.cpp
  DijkstraSP.h
  edge_weighted_digraph.h
  directed_edge.h
  common_util.h
)

# 5，把源码编译成一个可执行文件，文件名为自定义（DijkstraDemo），会保存在当前目录下
ADD_EXECUTABLE(DijkstraDemo ${SRC_LIST})
