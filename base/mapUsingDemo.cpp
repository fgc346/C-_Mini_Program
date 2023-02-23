#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <string>

#include <unordered_set>
#include <set>
#include <iostream>

//2020年12月20日16:32:58
//测试map的基本操作
//map插入操作
int main()
{
  std::map<int,std::string> map_info;
  map_info.insert(std::make_pair(1, "a"));
  map_info.insert(std::make_pair(2,"b"));
  map_info.insert(std::make_pair(3,"c"));
  map_info.insert(std::make_pair(4,"d"));
  map_info.insert(std::make_pair(5,"e"));
  map_info.insert(std::make_pair(6,"f"));
  map_info.insert(std::make_pair(7,"g"));
  map_info.insert(std::make_pair(8,"h"));
  map_info.insert(std::make_pair(9,"i"));
  map_info.insert(std::make_pair(10,"j"));
  map_info.insert(std::make_pair(11,"k"));
  map_info.insert(std::make_pair(12,"l"));
  map_info.insert(std::make_pair(13,"m"));

  for (const auto & elem : map_info)
  {
    std::cout << " the key = " << elem.first << " the value = " << elem.second << std::endl;
  }

  return 0;
    std::map<std::string, std::string> mapStudent;
    mapStudent.insert(std::make_pair("fgc","70"));
    mapStudent.insert(std::make_pair("hym","90"));
    std::map<std::string, std::string> mapStudent2;
    mapStudent2.insert(std::make_pair("yz","80"));
    mapStudent2.insert(std::make_pair("wxj","85"));

    mapStudent2["zs"] = "80";
    printf("insert before\n");
    // for(auto & stu : mapStudent)
    // {
    //     printf("the id = %s, the grade = %s\n",stu.first.data(), stu.second.data());
    // }
    mapStudent.insert(mapStudent2.begin(),mapStudent2.end());
    printf("insert after\n");
    // for(auto & stu : mapStudent)
    // {
    //     printf("the id = %s, the grade = %s\n",stu.first.data(), stu.second.data());
    // }

    std::unordered_map<std::string, std::unordered_map<std::string, std::string> > mmapSelfSingleRole;
    std::unordered_map<std::string, std::string> mapSelfSingleRole;
    mapSelfSingleRole["aaa"] = "111";
    mapSelfSingleRole["bbb"] = "222";
    mapSelfSingleRole["ccc"] = "333";
    mmapSelfSingleRole["fgc"].insert(mapSelfSingleRole.begin(), mapSelfSingleRole.end());
    printf("mmapSelfSingleRole[fgc],mmapSelfSingleRole[fgc].size=%d\n",mmapSelfSingleRole["fgc"].size());

    //multiset 默认是按从小到大顺序排列，第二个参数可以考虑是按从小到大还是从大到小。
    std::multiset<double, std::greater<double>> right_bounds;
    std::multiset<double> left_bounds;
    right_bounds.insert(10.0);
    right_bounds.insert(15.0);
    right_bounds.insert(20.0);
    left_bounds.insert(1.0);
    left_bounds.insert(2.0);
    left_bounds.insert(3.0);

    for(auto right : right_bounds)
    {
        printf(" the right bound = %0.2f\t", right);
    }
    printf("\n");
    for (auto left : left_bounds)
    {
        printf("the left bound = %0.2f\t", left);
    }
    printf("\n");


    getchar();
    return 0;
}