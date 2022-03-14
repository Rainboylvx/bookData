/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 11日 星期五 10:51:33 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100,maxe = 1e6+5; //点与边的数量

int n,m;

struct suffix_automatong {
    struct Node {
        int ch[26]{0}; // 边
        int len{0},fa{0}; // 当前点的最大maxlen,fa父亲节点
    } node[maxn<<1];
    int last = 1; // 最长前缀所属节点的编号
    int tot= 1;// tot当前sam节点总数


    //增加
    void add(int c){
        int p  = last;
        int np = last= ++tot;
        node[np].len = node[p].len+1;
        for( ; p && node[p].ch[c] == 0 ; p = node[p].fa )
            node[p].ch[c] = np;
        if( !p ) node[np].fa = 1; // above case 1
        else {
            int q = node[p].ch[c];
            if( node[q].len == node[p].len+1) 
                node[np].fa = q; // above case 2
            else {
                int nq = ++tot;
                node[nq]     = node[q]; //nq是q的复制,继承了q的出边
                node[nq].len = node[p].len+1; // 求出len
                node[q].fa   = node[last].fa = nq;
                for(;p&&node[p].ch[c] == q; p = node[p].fa)
                    node[p].ch[c] = nq; // above case 3
            }
        }
    }

    //转成dot格式
    std::string to_dot(){
        std::stringstream ss;
        ss << R"(digraph sam {
    )";
        for(int i=1;i<=tot;++i){
            for(int j = 0 ; j < 26;j++){
                int nex = node[i].ch[j];
                if(  nex != 0){
                    ss << i << "->" << nex << "[label=\"" << char(j+'a')  << "\",color=blue];\n"; //[label="c",color=blue];
                }
            }
        }
        for(int i=2;i<=tot;++i){
            ss << node[i].fa << "->" << i  << "[color=red,style=dotted,dir=back];\n";
        }
        for(int j=1;j<=tot;++j){
            ss << j << R"([label=")" << j << " len=" << node[j].len << R"("];)" << "\n";
        }
        ss << "}";
        return ss.str();
    }
} sam;

int main(int argc,char * argv[]){
    std::string  str;
    int len;
    std::cin >> str;
    int cnt = 1;
    for (const auto& e : str) {
        sam.add(e-'a');
        ofstream outfile;
        outfile.open(std::to_string(cnt++) + ".dot",ios::out);
        outfile << sam.to_dot();
        outfile.close();
    }
    //std::cout << sam.to_dot() << std::endl;
    return 0;
}
