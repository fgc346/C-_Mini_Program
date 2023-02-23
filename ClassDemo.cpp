#include "ClassDemo.h"
#include <limits>
#include <iostream>
int main()
{
    // A a;
    // a.printMember();
    for(int i = 0; i < 20; ++i)
    {
        std::cout << rand() / double(RAND_MAX) << std::endl;
    }
    //  double max_x_ = std::numeric_limits<double>::lowest();
    // double min_x_ = std::numeric_limits<double>::max();
    // double max_y_ = std::numeric_limits<double>::lowest();
    // double min_y_ = std::numeric_limits<double>::max();
    // printf("std::numeric_limits<double>::lowest()=%f\n", max_x_);       //1.79769e+308
    // printf("std::numeric_limits<double>::max()=%f\n", min_x_);
    // printf("std::numeric_limits<double>::lowest()=%f\n", max_y_);
    // printf("std::numeric_limits<double>::max()=%f\n", min_y_);
    //  std::cout<<"numeric_limits<double>::min()= "<< std::numeric_limits<double>::min()<<std::endl;  
    // std::cout<<"numeric_limits<double>::max()= "<< std::numeric_limits<double>::max()<<std::endl; 
    return 0;
}