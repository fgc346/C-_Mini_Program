#include "directed_edge.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "common_util.h"

// 有向加权图的数据结构

class EdgeWeightedDigraph
{
public:
    EdgeWeightedDigraph(int V)
    {
        V_ = V;
        E_ = 0;
        initAdj(V);
    }
    EdgeWeightedDigraph(std::ifstream &fin)
    {
        std::string line_str;
        getline(fin, line_str);
        std::stringstream v_str(line_str);
        v_str >> V_;
        std::cout << " v = " << V_ << std::endl;
        initAdj(V_);
        getline(fin, line_str);
        std::stringstream e_str(line_str);
        int e = 0;
        E_ = 0;
        e_str >> e;
        std::cout << " e_ = " << e << std::endl;
        for ( int i = 0; i < e; ++i)
        {
            //添加一条边
            getline(fin, line_str);
            int u = 0;
            int v = 0;
            double weight = 0;
            std::stringstream edge_str(line_str);
            edge_str >> u >> v >> weight;
            std::cout << " u = " << u << " v = " << v  << " weight = " << weight << std::endl;
            DirectedEdge edge_tmp(u, v, weight);
            AddEdge(edge_tmp);
        }
    }

    int V() {return V_;}
    int E() {return E_;}
    void AddEdge(DirectedEdge e)
    {
        adj_[e.From()].emplace_back(e);
        E_++;
    }
    std::vector<DirectedEdge>& Adj(int v)
    {
        return adj_[v];
    }
    std::vector<DirectedEdge> edges()
    {
        std::vector<DirectedEdge> bag;
        for (int v = 0; v < V_; ++v)
        {
            for (auto e : adj_[v])
            {
                bag.emplace_back(e);
            }
        }
        return bag;
    }

    std::string ToString()
    {
        std::string s = std::to_string(V_) + " vertices, " + std::to_string(E_) + " edges\n";
        for (int v = 0; v < V_; ++v)
        {
            s += std::to_string(v) + ": ";
            for (auto e : adj_[v])
            {
                s += std::to_string(e.From()) + "->" + std::to_string(e.To()) + " " + DoFraction(e.Weight()) + "\t";
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
            adj_.emplace_back(std::vector<DirectedEdge>());
        }
    }
private:
    int V_;      //顶点总数
    int E_;      // 边的总数
    std::vector<std::vector<DirectedEdge>> adj_; // 邻接链表
};