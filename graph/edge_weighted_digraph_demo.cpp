#include "edge_weighted_digraph.h"

int main(int argc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    EdgeWeightedDigraph graph_1(srcFile);
    srcFile.close();
    std::cout << graph_1.ToString();
    
    return 0;
}