#include "graph_struct_set.h"
#include "graph_cycle_check.h"

int main(int argc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    GraphByUnorderSet graph_1(srcFile);
    srcFile.close();
    std::cout << graph_1.ToString();

    Cycle<GraphByUnorderSet> cycle(graph_1);
    std::cout << " graph = " << cycle.HasCycle() << std::endl;
    return 0;
}