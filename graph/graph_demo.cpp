#include "graph_struct.h"
#include "depth_first_paths.h"
#include "breadth_first_paths.h"

int main(int agrc, char* argv[])
{
    std::string file_name(argv[1]);
    int s = std::stoi(argv[2]);
    // int s = 0;
    std::cout << " file_name = " << file_name << " s = " << s << std::endl;
    std::ifstream srcFile(file_name, std::ios::in); //以文本模式打开txt文件
    Graph graph_1(srcFile);
    srcFile.close();
    std::cout << graph_1.ToString();
    DepthFirstPaths dfs_path(graph_1, s);
    std::cout << "0-1: " << dfs_path.HasPathTo(1);
    std::cout << " dfs paths: " << std::endl << std::endl;
    for (int v = 0; v < graph_1.Vertex(); ++v)
    {
        if (dfs_path.HasPathTo(v))
        {
            std::cout << " vertex s = " << s << " and vertex v = " << v << " has path" << std::endl;
            for (auto x : dfs_path.PathTo(v))
            {
                if (x == s)
                {
                    std::cout << x;
                }
                else {
                    std::cout << "-" << x;
                }
            }
            std::cout << std::endl;
        }
    }


    BreadthFirstPaths bfs_path(graph_1, s);
    std::cout << "0-1: " << bfs_path.HasPathTo(1);
    std::cout << " bfs paths: " << std::endl << std::endl;
    for (int v = 0; v < graph_1.Vertex(); ++v)
    {
        if (bfs_path.HasPathTo(v))
        {
            std::cout << " vertex s = " << s << " and vertex v = " << v << " has path" << std::endl;
            for (auto x : bfs_path.PathTo(v))
            {
                if (x == s)
                {
                    std::cout << x;
                }
                else {
                    std::cout << "-" << x;
                }
            }
            std::cout << std::endl;
        }
    }

#if 0
    std::cout << " \nthe second graph: \n" << std::endl;
    std::ifstream srcFile_2(file_name, std::ios::in);
    GraphByList graph_2(srcFile_2);
    srcFile.close();
    std::cout << graph_2.ToString();
#endif
    return 0;
}