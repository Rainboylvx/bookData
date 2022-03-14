#include <cyaroncpp/cyaron.hpp>
using namespace std;
using namespace cyaron;

int main(){
    auto data = 
        [](cyaron::IO& rndio){ //生成数据的lambda，接收的参数必须是IO &
            auto n = cyaron::RND(200,1000); //n个操作
            //auto n = 10;
            rndio.input_writeln(n);
            for(int i=1;i<=n-1;++i){
                auto o = cyaron::RND(1,2); //n个操作
                rndio.input_writeln(o,cyaron::RND(1,100)); // 1 是写入 2是删除
            }
            rndio.input_writeln(3);
        };
    Compare::program<false>("test.cpp", "std.cpp",data,1000);

    return 0;
}
