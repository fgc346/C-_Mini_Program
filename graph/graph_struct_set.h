/*
 * @Author: fenggaochao
 * @Date: 2023-02-24 13:02:31
 * @LastEditTime: 2023-02-24 13:08:06
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C++_Mini_Program/graph/graph_struct_set.h
 */

// 图的邻接表方法
// 邻接表unorder_set实现
// 邻接表使用unorder_set实现背包bag，就和算法这本书中的程序保持一致了


#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
#include <iostream>
#include <list>
#include <unordered_set>

class GraphByUnorderSet
{
public:
    GraphByUnorderSet(int v)
    {
        v_ = v;
        e_ = 0;
        initAdj(v_);
    }
    GraphByUnorderSet(std::ifstream &fin)
    {
        std::string line_str;
        getline(fin, line_str);
        std::stringstream v_str(line_str);
        v_str >> v_;
        std::cout << " v = " << v_ << std::endl;
        initAdj(v_);
        getline(fin, line_str);
        std::stringstream e_str(line_str);
        int e = 0;
        e_ = 0;
        e_str >> e;
        std::cout << " e_ = " << e << std::endl;
        for ( int i = 0; i < e; ++i)
        {
            //添加一条边
            getline(fin, line_str);
            int u = 0;
            int v = 0;
            std::stringstream edge_str(line_str);
            edge_str >> u >> v;
            std::cout << " u = " << u << " v = " << v << std::endl;
            AddEdge(u,v);
        }
    }
    int Vertex()
    {
        return v_;
    }
    int Edge()
    {
        return e_;
    }
    void AddEdge(int u, int v)
    {
        adj_[u].insert(v);     // 将v加入到u的链表中
        adj_[v].insert(u);     // 将u加入到v的链表中
        ++e_;
    }
    std::unordered_set<int>& Adj(int v)
    {
        return adj_[v];
    }
    std::string ToString()
    {
        std::string s = std::to_string(v_) + " vertices, " + std::to_string(e_) + " edges\n";
        for (int v = 0; v < v_; ++v)
        {
            s += std::to_string(v) + ": ";
            for (auto u : adj_[v])
            {
                s += std::to_string(u) + " ";
            }
            s += "\n";
        }
        return s;
    }

private:
    void initAdj(int v)
    {
        // 将所有链表初始化为空
        for (int i = 0; i < v; ++i)
        {
            adj_.emplace_back(std::unordered_set<int>());
        }
    }
private:
    int v_; // 顶点数目
    int e_; // 边的数目
    std::vector<std::unordered_set<int>> adj_;  // 邻接表
};