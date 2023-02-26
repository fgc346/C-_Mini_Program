#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "common_util.h"
#include "graph_struct.h"

#if 0
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

#endif

class SymbolGraph
{
public:
    SymbolGraph(std::ifstream &fin, const std::string &sp)
    {
        std::string line_str;
        std::vector<std::vector<std::string>> graph_vv;
        while (getline(fin, line_str))
        {
            std::vector<std::string> v;
            SplitString(line_str, v, sp);
            for (int i = 0; i < v.size(); ++i)
            {
                if (!st_.count(v[i]))
                {
                    st_.insert(std::make_pair(v[i], st_.size()));
                    keys_.emplace_back(v[i]);
                }
            }
            graph_vv.emplace_back(v);
        }

        std::cout << " the symbol-index : " << std::endl;
        for (auto value : st_)
        {
            std::cout << value.first << " : " << value.second << std::endl;
        }
        // std::cout << std::endl;
        std::cout << "the index-symbol : " << std::endl;
        for (int i = 0; i < keys_.size(); ++i)
        {
            std::cout << i << " : " << keys_[i] << std::endl;
        }
        std::cout << std::endl;

        int vertex_num = st_.size();
        int edge_num = graph_vv.size();
        std::cout << "graph vertex num : " << vertex_num << " edge_num : " << edge_num << std::endl;
        std::cout << "from file get original data: " << std::endl;
        for (auto row : graph_vv)
        {
            for (auto elem : row)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        G_ = new Graph(vertex_num);
        for (int i = 0; i < edge_num; ++i)
        {
            auto vertex_edge = graph_vv[i];
            int v = st_[vertex_edge[0]];
            for (int j = 1; j < vertex_edge.size(); ++j)
            {
                G_->AddEdge(v, st_[vertex_edge[j]]);
            }
        }
    }

bool Contains(std::string s) {
    return st_.count(s);
}
int Index(std::string s) {
    return st_[s];
}
std::string Name(int v)
{
    return keys_[v];
}

Graph GraphData()
{
    return *G_;
}
private:
    std::map<std::string, int> st_;  // 符号名--索引
    std::vector<std::string> keys_;  // 索引--符号名
    Graph* G_;                       // 图
};