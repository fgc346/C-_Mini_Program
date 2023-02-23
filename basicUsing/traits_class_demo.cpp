#include "traits_template_demo.h"
#include <iostream>
#include <type_traits>

int main()
{
    int numbers[] = {1,2,3,4,5};
    std::cout <<  "the average =  " <<  average(&numbers[0],&numbers[5]) << std::endl;
    char characters[] = "traits";
    std::cout << "the char[] average = " << static_cast<int>(average(&characters[0],&characters[6])) << std::endl;
    std::cout << "the char[],traits average = " << static_cast<int>(average_2<char,TypeTraits<char>>(&characters[0],&characters[6])) << std::endl;
    Component<NullType> template_A;
    std::string str("hello template member function");
    template_A.Initialize(str);
    Component<void> template_B;
    template_B.Initialize("specfy");
    return 0;
}