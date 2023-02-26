#include <string>
#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[])
{
    std::string str("abc");
    std::string::size_type position;
    position = str.find("a", 100);
    if (position == std::string::npos)
    {
        printf("str %s not find  'a' in pos 100\n", str.data());
    }
    return 0;
}