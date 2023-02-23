#include "StrBlob.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        std::cout << "b1.size = " << b1.size() << " b2.size = " << b2.size() << std::endl;
        b2.push_back("about");
        std::cout << "after push_back, b1.size = " << b1.size() << " b2.size = " << b2.size() << std::endl;
    }
    std::cout << "after destory b2, b1.size = " << b1.size() << std::endl;

    //读取一个输入文件，逐行读取输入文件
    std::ifstream in("./data/strblob.txt");
    std::string text;
    StrBlob strblob_1;
    while (getline(in, text))
    {
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            strblob_1.push_back(word);
        }
    }
{
    StrBlobPtr str_blob_ptr(strblob_1);
    for ( size_t i = 0; i != strblob_1.size(); ++i)
    {
        std::cout << str_blob_ptr.deref() << std::endl;
        str_blob_ptr.incr();
    }
}

    std::cout << "strblob_1 = " << strblob_1.size() << std::endl;

    const StrBlob str_blob_2{"aaa", "yyy", "jiake"};
    StrBlobPtr str_blob_ptr_2(str_blob_2);
    for (size_t j = 0; j != str_blob_2.size(); ++j)
    {
        std::cout << str_blob_ptr_2.deref() << std::endl;
        str_blob_ptr_2.incr();
    }
    return 0;
}