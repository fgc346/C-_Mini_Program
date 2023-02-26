#include "symbol_graph_struct.h"

int main(int argc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    if (!srcFile.is_open())
    {
        std::cout << "the file_name " << file_name << " failed to open" << std::endl;
    }
    SymbolGraph symbol_graph_1(srcFile," ");
    srcFile.close();
    std::cout << symbol_graph_1.GraphData().ToString();
}