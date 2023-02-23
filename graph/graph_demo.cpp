#include "graph_struct.h"

int main(int agrc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    // int s = 0;
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); //以文本模式打开txt文件
    Graph graph_1(srcFile);
    std::cout << graph_1.ToString();
    srcFile.close();
    std::cout << " \nthe second graph: \n" << std::endl;
    std::ifstream srcFile_2(file_name, std::ios::in);
    GraphByList graph_2(srcFile_2);
    std::cout << graph_2.ToString();
    srcFile.close();
    return 0;
}