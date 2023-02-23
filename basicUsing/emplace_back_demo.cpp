#include <stdio.h>
#include <vector>
#include <string>

int main()
{
    std::vector<std::pair<int, int>> vec_pair_1;
    vec_pair_1.push_back(std::make_pair(1,1));
    // vec_pair_1.push_back(2,2);   //push_back 不能直接使用（1,1）
    vec_pair_1.push_back({2,2});
    for (auto & elem : vec_pair_1)
    {
        printf("%d,%d\n", elem.first, elem.second);
    }

    std::vector<std::pair<std::string, int>>  vec_pair_2;
    vec_pair_2.emplace_back("fgc", 12);
    vec_pair_2.emplace_back("jk", 9);

    printf("output the vec_pair with emplace_back\n");
    for ( auto & elem : vec_pair_2)
    {
        printf("%s,%d\n", elem.first.data(), elem.second);
    }

    return 0;
}