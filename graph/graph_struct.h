#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
#include <iostream>
#include <list>
#include <unordered_set>

// 图的邻接表方法
// 邻接表使用vector实现
class Graph
{
public:
    Graph(int v)
    {
        v_ = v;
        e_ = 0;
        initAdj(v_);
    }
    Graph(std::ifstream &fin)
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
        adj_[u].emplace_back(v);     // 将v加入到u的链表中
        adj_[v].emplace_back(u);     // 将u加入到v的链表中
        ++e_;
    }
    std::vector<int> Adj(int v)
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
            adj_.emplace_back(std::vector<int>());
        }
    }
private:
    int v_; // 顶点数目
    int e_; // 边的数目
    std::vector<std::vector<int>> adj_;  // 邻接表
};



// 图的邻接表方法
// 邻接表使用list实现
class GraphByList
{
public:
    GraphByList(int v)
    {
        v_ = v;
        e_ = 0;
        initAdj(v_);
    }
    GraphByList(std::ifstream &fin)
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
        adj_[u].emplace_back(v);     // 将v加入到u的链表中
        adj_[v].emplace_back(u);     // 将u加入到v的链表中
        ++e_;
    }
    std::list<int> Adj(int v)
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
            adj_.emplace_back(std::list<int>());
        }
    }
private:
    int v_; // 顶点数目
    int e_; // 边的数目
    std::vector<std::list<int>> adj_;  // 邻接表
};
