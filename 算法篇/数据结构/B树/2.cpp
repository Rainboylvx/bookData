/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 01日 星期三 13:43:18 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

constexpr size_t sizeD(double a){
    return a;
}

//靜态化动态
template<typename T,size_t size = 100>
struct MeM {
    size_t idx{0};
    //std::vector<T> mem(1000);
    std::array<T,size> mem;
    T* get() {return &mem[idx++];}
};


//使用链表的思想来创建
//历为linklist 它的的插入和删除都很简单
template<typename T,int M = 10>
struct BTree {
    struct node;
    struct pixel {
        pixel * pre,* nxt; //双向链表
        //内部值
        T val; 
        node * pchild;
    };
    struct node {
        pixel * chain{nullptr};
        int num{0}; //有多少个元素
        node* fa;
    };

    void insert(T val){
        if( root == nullptr)
            root = memNode.get();
        auto tp = memPixel.get();
        tp->pchild = nullptr;
        tp->val = val;
        auto x = find_util_leaf(root, val);
        __insert__(x, tp, nullptr);
    }

    void __insert__(node * p,pixel * tp,node * right){
        //直接插入
        auto t = p->chain;
        int i = 0;
        for( ; t->val < tp->val  && i < maxK;t = t->nxt ,i++ );
        // t就是要插入的点
        t->pchild = right;
        //auto tp  = memPixel.get();
        //tp->pchild = left;
        tp->nxt =t;
        tp->pre = t->pre;
        t->pre = tp;
        tp->pre->nxt = tp; //插入成功
        p->num++;
        // todo tp->left == t.pchild;

        if( p->num >= maxK) { //分裂
            //1. 找到中间点
            auto np = memNode.get();
            np->num = minK;
            t = p->chain;
            i = 0;
            for( ; i < minK;t = t->nxt ,i++ );
            auto middle = t;

            np->chain = t->nxt;
            t->nxt = nullptr;
            p->num = minK;

            auto ttp = memPixel.get();
            ttp->pchild = p;
            ttp->val = t->val;

            //建立一个新的node
            //
            if( p == root ) { //是root
                auto nnp = memNode.get();
                nnp->chain =middle;
                root = nnp;
                root->fa = root;
            }
            else 
                __insert__(p->fa, ttp, np);
        }
    }


    //直到找找到leaf
    auto
    find_util_leaf(node * p,T val) {
        auto t = p->chain;
        int i = 0;
        for(  ; t!=nullptr ; t = t->nxt ,i++){
            if( t->val > val || i == p->num)
                break;
        }
        if( t == nullptr || t->pchild == nullptr ) // 这个结点没有key
            return p;                             // 当root指向一个新的结点
        return find_util_leaf(t->pchild, val); //TODO &val
    }

private:
    node * root{nullptr};  //根结点
    MeM<node,10000> memNode; //内存
    MeM<pixel,10000> memPixel; //内存
    const int maxK = M-1;
    const int minK = M/2 + ( M % 2) -1;
};

BTree<int, 5> bt;

int main(int argc,char * argv[]){
    int t;
    while ( scanf("%d",&t) != EOF ) {
        bt.insert(t);
    }
    return 0;
}
