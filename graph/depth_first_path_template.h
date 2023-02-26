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
        // dfs(G, s);
        // dfs_non_recursion(G, s);
        dfs_non_recursion_2(G,s);
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
    void dfs_non_recursion(T G, int s)
    {
        std::stack<int> st;
        marked_[s] = true;
        st.push(s);
        while(!st.empty())
        {
            int pre = st.top();
            std::cout << " pre : " << pre << std::endl;
            // for (auto v : G.Adj(pre))
            // {
            //     std::cout << "  " << v;
            // }
            // std::cout << std::endl;
            // // 遍历输出 uset 容器存储的所有元素
            // std::unordered_set<int> uset(G.Adj(pre));
            // for (auto iter = uset.begin(); iter != uset.end(); ++iter)
            // {
            //     std::cout << *iter << std::endl;
            // }
            // std::cout << std::endl;
            // std::unordered_set<int>::iterator iter = (G.Adj(pre)).begin();
            // auto uset = G.Adj(pre);
            // auto iter = G.Adj(pre).begin();
            auto iter = G.Adj(pre).begin();
            while(iter != G.Adj(pre).end())
            {
                auto v = *iter;
                std::cout << " v = " << v << std::endl;
                if (!marked_[v])
                {
                    marked_[v] = true;
                    edgeTo_[v] = pre;
                    st.push(v);
                    break;
                }
                ++iter;
            }
            if (iter == G.Adj(pre).end())
            {
                st.pop();
            }
        }

    }

    void dfs_non_recursion_2(T G, int s)
    {
        std::stack<int> st;
        marked_[s] = true;
        st.push(s);
        std::cout << " the node " << s << " push into stack" << std::endl;
        while(!st.empty())
        {
            //当前节点出栈
            auto curr = st.top();
            st.pop();
            std::cout << " the node " << curr << " from stack pop" << std::endl;
            //对当前节点的子节点，从后往前入栈
            for (auto iter = G.Adj(curr).begin(); iter != G.Adj(curr).end(); ++iter)
            {
                if (!marked_[*iter])
                {
                    marked_[*iter] = true;
                    edgeTo_[*iter] = curr;
                    st.push(*iter);
                    std::cout << " the node " << *iter << " push into stack" << std::endl;
                }
            }
        }
    }
private:
    std::vector<bool> marked_;  //这个顶点上调用过dfs()了吗
    std::vector<int> edgeTo_;   //从起点到一个顶点的已知路径上的最后一个顶点
    int s_;                     //起点
};