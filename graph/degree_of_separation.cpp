#include "symbol_graph_struct.h"
#include "breadth_first_paths.h"

int main(int argc, char *argv[])
{
    std::string file_name(argv[1]);
    std::string str = argv[2];
    std::cout << " file_name = " << file_name << " str = " << str << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); // 以文本模式打开txt文件
    if (!srcFile.is_open())
    {
        std::cout << "the file_name " << file_name << " failed to open" << std::endl;
    }
    SymbolGraph symbol_graph_1(srcFile, " ");
    srcFile.close();
    std::cout << symbol_graph_1.GraphData().ToString();

    Graph G = symbol_graph_1.GraphData();
    if (!symbol_graph_1.Contains(str))
    {
        std::cout << str << " not in datebase." << std::endl;
    }

    int s = symbol_graph_1.Index(str);
    std::cout << " str = " << str << " s = " << s;
    BreadthFirstPaths *bfs = new BreadthFirstPaths(G, s);
    std::cout << " bfs paths: " << std::endl;
    PrintGraphPath(G, *bfs, s);

    std::string sink;
    while (std::cin >> sink)
    {
        if (symbol_graph_1.Contains(sink))
        {
            int t = symbol_graph_1.Index(sink);
            std::cout << " sink =  " << sink << " t = " << t << std::endl;
            if (bfs->HasPathTo(t))
            {
                for (auto v : bfs->PathTo(t))
                {
                    std::cout << "\t" << symbol_graph_1.Name(v) << std::endl;
                }
            }
            else
            {
                std::cout << "Not connected" << std::endl;
            }
        }
        else
        {
            std::cout << " Not in datebase." << std::endl;
        }
    }

    return 0;
}