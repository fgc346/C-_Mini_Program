#pragma once
#include <vector>
#include <set>
#include <iostream>

template <typename T>
class Cycle
{
public:
    Cycle(T g) : hasCycle_(false),count_(0)
    {
        visited_.assign(g.Vertex(), false);
        for (int s = 0; s < g.Vertex(); ++s)
        {
            if (!visited_[s])
            {
                dfs(g, s, s);

            }
        }
    }
    void dfs(T g, int v, int u)
    {
        count_++;
        std::cout << "execute count: " << count_ << " dfs(v,u), v = " << v << " u  = " << u << std::endl;
        visited_[v] = true;
        for (auto w : g.Adj(v))
        {
            std::cout << " check w = " << w << std::endl;
            if (!visited_[w])
            {
                dfs(g, w, v);
            }
            else if (w != u)
            {
                hasCycle_ = true;
                std::cout << " w = " << w << " u = " << u << " hasCycle_ = " << hasCycle_ << std::endl;
            }
            // std::cout << " only check w = " << w << std::endl;
        }
    }
    bool HasCycle()
    {
        return hasCycle_;
    }
private:
    std::vector<bool> visited_;
    bool hasCycle_;
    int count_;
};



// 暂时先不实现这种方案
#if 0

// 算法思想,这种方案对有向图有效，对无向图无效
// 使用三个set 表示white，gray，black 顶点集
// white 表示没有访问过得节点
// gray 表示已访问，但是相邻节点还没有访问完
// black 表示已访问，并且相邻节点已全部访问
template <typename T>
class CycleInGraph
{
public:
    CycleInGraph(T g) : hasCycle_(false)
    {
        for (int s = 0; s < g.Vertex(); ++s)
        {
            white_set_.insert(s);
        }
        father_.assign(g.Vertex(), -1);
        while (!white_set_.empty())
        {
            int current = *white_set_.begin();
            std::cout << "from white_set get current = " << current << std::endl;
            if (dfs(g, current,father_[current]))
            {
                hasCycle_ = true;
                break;
            }
        }
        if (hasCycle_)
        {
            for (auto v : gray_set_)
            {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
    bool dfs(T g, int v, int parent)
    {
        MoveVertex(v, white_set_, gray_set_);
        std::cout << "move v " << v << " from white_set to gray_set" << std::endl;
        for (auto neighbor : g.Adj(v))
        {
            std::cout << " neighbor = " << neighbor << std::endl;
            if (black_set_.count(neighbor))
            {
                continue;
            }
            if (gray_set_.count(neighbor) && neighbor != parent)
            {
                return true;
            }
            if (dfs(g, neighbor, v))
            {
                return true;
            }
        }

        MoveVertex(v, gray_set_, black_set_);
        std::cout << "move v " << v << " from gray_set to black_set" << std::endl;
        father_[]
        return false;
    }

    void MoveVertex(int v, std::set<int> &source_set, std::set<int> &destination_set)
    {
        source_set.erase(v);
        destination_set.insert(v);
    }

    bool HasCycle()
    {
        return hasCycle_;
    }

private:
    std::set<int> white_set_;
    std::set<int> gray_set_;
    std::set<int> black_set_;
    std::vector<int> father_;
    bool hasCycle_;
};

#endif