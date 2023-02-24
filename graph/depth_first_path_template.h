#include "graph_struct.h"
#include <stack>

template <typename T >
class DepthFirstPaths
{
public:
    DepthFirstPaths(T G, int s)
    {
        marked_.assign(G.Vertex(), false);
        edgeTo_.assign(G.Vertex(), 0);
        s_ = s;
        dfs(G, s);
    }
    bool HasPathTo(int v)
    {
        return marked_[v];
    }
    std::vector<int> PathTo(int v)
    {
        if (!HasPathTo(v))
        {
            return std::vector<int>();
        }

        std::stack<int> path_stack;
        for (int x = v; x != s_; x = edgeTo_[x])
        {
            path_stack.push(x);
        }
        path_stack.push(s_);
        std::vector<int> path;
        while (!path_stack.empty())
        {
            path.emplace_back(path_stack.top());
            path_stack.pop();
        }
        return path;
    }
private:
    void dfs(T G, int v)
    {
        marked_[v] = true;
        for (auto u : G.Adj(v))
        {
            if (!marked_[u])
            {
                edgeTo_[u] = v;
                dfs(G, u);
            }

        }
    }
private:
    std::vector<bool> marked_;  //这个顶点上调用过dfs()了吗
    std::vector<int> edgeTo_;   //从起点到一个顶点的已知路径上的最后一个顶点
    int s_;                     //起点
};