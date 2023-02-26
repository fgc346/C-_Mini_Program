#pragma once
#include "edge_weighted_digraph.h"

#include <queue>
#include <limits>
#include <stack>

using Node_Distance = std::pair<int, double *>;    // (v, &distTo[v]) distTo表示s-v的路径代价
struct myGreater {
   bool operator() (Node_Distance a, Node_Distance b){
     return *(a.second) >  *(b.second);   //小顶堆
  }
};
using MyPriorityQueue = std::priority_queue<Node_Distance, std::vector<Node_Distance>, myGreater>;

const double POSITIVE_INFINITY = std::numeric_limits<double>::max();
const int NIL = -1;



class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph G, int s)
    {
        G_ = &G;
        //最开始将所有节点到起点的距离设置为最大值，正无穷
        InitDijkstraSP(G.V(), s);
        for (int i = 0; i < G.V(); ++i)
        {
            pq_.push(std::make_pair(i, &distTo_[i]));
        }
        while (!pq_.empty())
        {
            auto node = pq_.top();
            pq_.pop();
            relax(G, node);
        }

    }
    void relax(EdgeWeightedDigraph G, Node_Distance v)
    {
        for (auto e : G.Adj(v.first))
        {
            int w = e.To();
            if (distTo_[w] > distTo_[v.first] + e.Weight())
            {
                distTo_[w] = distTo_[v.first] + e.Weight();
                edgeTo_[w] = e;
            }
        }
    }
    double distTo(int v)
    {
        return distTo_[v];
    }
    bool HasPathTo(int v)
    {
        return distTo_[v] < POSITIVE_INFINITY;
    }
    std::vector<DirectedEdge> PathTo(int v)
    {
        std::vector<DirectedEdge> path;
        if (!HasPathTo(v))
        {
             return path;
        }
        std::stack<DirectedEdge> path_stack;
        for (DirectedEdge e = edgeTo_[v]; e.To() != NIL; e = edgeTo_[e.From()])
        {
             path_stack.push(e);
        }
        while (!path_stack.empty())
        {
             path.emplace_back(path_stack.top());
             path_stack.pop();
        }
        return path;
    }
private:
    void InitDijkstraSP(int vertex_num, int s)
    {
        for (int i = 0; i < vertex_num; ++i)
        {
            distTo_.emplace_back(POSITIVE_INFINITY);
            edgeTo_.emplace_back(DirectedEdge(i, NIL, POSITIVE_INFINITY));
        }
        distTo_[s] = 0.0;
    }
private:
    std::vector<DirectedEdge> edgeTo_;
    std::vector<double> distTo_;
    int s_; //起点
    EdgeWeightedDigraph* G_;
    MyPriorityQueue pq_;

    // std::priority_queue<double, std::vector<double>, std::greater<double>> pq_; 
    // std::priority_queue<DirectedEdge, std::vector<DirectedEdge>, decltype([](DirectedEdge left, DirectedEdge right) -> bool {left.Weight() > right.Weight();})> pq_;
    //默认是大顶堆 priority_queue<double, vector<double>, less<double> >
    // 这里是小顶堆,最小的元素先出队
};

