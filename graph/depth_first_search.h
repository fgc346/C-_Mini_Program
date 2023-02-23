#pragma once
#include "graph_struct.h"

class DepthFistSearch
{
public:
    DepthFistSearch(Graph G, int s) : count_(0)
    {
        int g_vertex_num = G.Vertex();
        marked_.assign(g_vertex_num, false);
        dfs(G, s);
    }
    bool Marked(int u)
    {
        return marked_[u];
    }
    int Count()
    {
        return count_;
    }
private:
    void dfs(Graph G, int v)
    {
        marked_[v] = true;
        ++count_;
        for (auto u : G.Adj(v))
        {
            if (!marked_[u])
            {
                dfs(G, u);
            }
        }
    }
private:
    std::vector<bool> marked_;
    int count_;
};

