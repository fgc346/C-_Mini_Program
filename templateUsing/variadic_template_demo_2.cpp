#include <iostream>
#include <string>

#include <vector>
#include <map>

//用来终止递归并打印最后一个元素的函数
//此函数必须在可变参数版本的print定义之前声明
template<typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os << t;
}

template <typename T, typename ... Args>
std::ostream &print(std::ostream &os, const T &t, const Args& ... rest)
{
    os << t << ", ";
    return print(os, rest...);
}

// template<typename T>
// std::ostream &print(std::ostream &os, const T &t)
// {
//     return os << t;
// }

template <typename T> std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << " pointer: " << p;
    if (p)
    {
        ret << " " << debug_rep(*p);
    }
    else
    {
        ret << " null pointer";
    }
    return ret.str();
}

std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}


template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string &);
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

int main()
{
    int i = 0;
    double d = 3.14;
    std::string s = "how now brown cow";
    char ch = 'a';
    char* ptr = "hello, ptr";
    
    print(std::cout, i, s, 42);
    std::cout << std::endl;
    std::cout << "first pram print" << std::endl;
    print(std::cout, i);
    std::cout << std::endl;
    std::cout << "three pram print " << std::endl;
    print(std::cout, i, s, 42);
    std::cout << std::endl;
    std::cout << "five pram print " << std::endl;
    std::vector<int> vec{1,2,3};
    std::map<int, std::string> mapTemp{
        {1, "a"},{2, "b"}, {3, "c"}
    };
    print(std::cout, i, s, 42, ch, ptr);

    std::cout << std::endl;

    return 0;
}