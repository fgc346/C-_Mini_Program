#include "DijkstraSP.h"

int main(int argc, char *argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    EdgeWeightedDigraph graph_1(srcFile);
    srcFile.close();
    std::cout << graph_1.ToString();

    std::cout << " the dijkstra short path: " << std::endl;
    DijkstraSP sp(graph_1, s);
    for (int t = 0; t < graph_1.V(); ++t)
    {
        std::cout << s << " to " << t << " (" << sp.distTo(t) << ") : ";
        if (sp.HasPathTo(t))
        {
            for (auto e : sp.PathTo(t))
            {
                std::cout << e.From() << "->" << e.To() << " " << e.Weight() << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}