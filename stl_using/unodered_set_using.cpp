#include <iostream>
#include <unordered_set>
#include <vector>

std::vector<std::unordered_set<int>> g_vec_set;
std::unordered_set<int> GetSet(int num)
{
    return g_vec_set[num];
}

std::unordered_set<int>& GetSet2(int num)
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
    // GetSet() 函数返回一个临时对象，执行完下面的一条语句后
    // iter_1迭代器已经执行一个消亡的对象，就出现问题了。
    auto iter_1 = GetSet(0).begin();
    while (iter_1 != GetSet(0).end())
    {
        std::cout << *iter_1 << " ";
        ++iter_1;
    }
    std::cout << std::endl;

    auto iter = GetSet2(0).find(10);
    if (iter != GetSet2(0).end())
    {
      std::cout << *iter << std::endl;
    }
    // std::cout << *iter << std::endl;
    //GetSet() 函数返回一个引用
    auto uset_1 = GetSet2(0);
    auto iter_12 =uset_1.begin();
    while (iter_12 != uset_1.end())
    {
        std::cout << *iter_12 << " ";
        ++iter_12;
    }
    std::cout << std::endl;

    //GetSet() 函数返回一个引用
    auto iter_2 = GetSet2(0).begin();
    while (iter_2 != GetSet2(0).end())
    {
        std::cout << *iter_2 << " ";
        ++iter_2;
    }
    std::cout << std::endl;
    return 0;
}