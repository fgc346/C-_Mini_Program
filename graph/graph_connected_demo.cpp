#include "graph_struct_set.h"
#include "graph_connect_detective.h"

int main(int argc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    GraphByUnorderSet graph_1(srcFile);
    srcFile.close();
    std::cout << graph_1.ToString();

    CC<GraphByUnorderSet> cc(graph_1);
    int m = cc.Count();
    std::cout << " the graph have " << m << " components" << std::endl;
    
    std::vector<std::vector<int>> components(m);
    for (int v = 0; v < graph_1.Vertex(); ++v)
    {
        std::cout << cc.Id(v) << " ";
        components[cc.Id(v)].emplace_back(v);
    }
    std::cout << std::endl;

    for (int i = 0; i < m; ++i)
    {
        for (int v : components[i])
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}