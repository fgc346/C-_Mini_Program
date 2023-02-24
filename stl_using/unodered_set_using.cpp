#include <iostream>
#include <unordered_set>
#include <vector>

std::vector<std::unordered_set<int>> g_vec_set;
std::unordered_set<int> GetSet(int num)
{
    return g_vec_set[num];
}

int main()
{
    g_vec_set = {{1,2,3},{4,5,6},{7,8,9}};
    for (auto set : g_vec_set)
    {
        for (auto elem : set)
        {
            std::cout << "  " << elem;
        }
        std::cout << std::endl;
    }
    // 这样使用是有问题的，暂时没有发现这个样用的问题在哪里
    auto iter = GetSet(0).begin();
    while (iter != GetSet(0).end())
    {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;
    return 0;
}