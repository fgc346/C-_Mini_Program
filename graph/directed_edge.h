#pragma once

class DirectedEdge
{
public:
    DirectedEdge(int u, int v, double weight) : u_(u), v_(v), weight_(weight)
    {
    }
    double Weight()
    {
        return weight_;
    }
    int From()
    {
        return u_;
    }
    int To()
    {
        return v_;
    }
private:
    int u_;              //边的起点
    int v_;              //边的终点
    double weight_;      // 边的权重
};