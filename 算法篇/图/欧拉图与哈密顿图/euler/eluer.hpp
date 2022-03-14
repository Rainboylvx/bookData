#include <vector>

//[Eulerian path - Wikipedia](https://en.wikipedia.org/wiki/Eulerian_path)
struct linkList;

//图的方向性
enum class graph_dir {
    UNDIRECTED,
    DIRECTED,
};

//欧拉图的分类
enum class euler_graph_class {
    nonEulerian, //不是欧拉图
    Eulerian,//欧拉图
    semiEulerian // 半欧拉图
};

struct euler_graph {

    graph_dir _M_gh_dir{graph_dir::UNDIRECTED}; //图的方向性

    //
    euler_graph_class judge(){
    }
    //找到一条欧拉路径
    template<typename T,template <typename U = T> class vector = std::vector  >
    void hierholzer_algo(linkList& e,vector<T>& vec){
    }
};
