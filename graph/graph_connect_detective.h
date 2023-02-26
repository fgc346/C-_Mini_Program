#pragma once
#include <vector>

template <typename T>
class CC
{
public:
    CC(T g) : count_(0)
    {
        visited_.assign(g.Vertex(),false);
        ids_.assign(g.Vertex(),0);
        for(int s = 0; s < g.Vertex(); ++s)
        {
            if(!visited_[s])
            {
                dfs(g, s);
                ++count_;
            }
        }
    }

    void dfs(T g, int v)
    {
        visited_[v] = true;
        ids_[v] = count_;
        for (auto u : g.Adj(v))
        {
            if (!visited_[u])
            {
                dfs(g, u);
            }
        }
    }

    bool Connected(int v, int u)
    {
        return ids_[v] == ids_[u];
    }
    int Id(int v)
    {
        return ids_[v];
    }
    int Count()
    {
        return count_;
    }
private:
    std::vector<bool> visited_;
    std::vector<int> ids_;
    int count_;
};