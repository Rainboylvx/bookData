/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 12月 01日 星期三 13:43:18 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
std::unordered_map<uint64_t, int> umap;

int n,m;
/* 定义全局变量 */

constexpr size_t sizeD(double a){
    return a;
}

//靜态化动态
template<typename T,size_t size = 200000>
struct MeM {
    size_t idx{0};
    //std::vector<T> mem(1000);
    std::array<T,size> mem;
    T* get() {return &mem[idx++];}
};
template<typename T,size_t deg=3>
struct BTreeNode;





template<typename T,size_t deg>
struct BTreeNode
{
    static constexpr int maxKeySize{deg*2-1}; //最多key大小
    static constexpr int maxChildSize{deg*2}; //最多child大小
    static constexpr int degree{deg};
    static constexpr int half{deg-1}; //full之后的的一半
    //static constexpr Father * father;

    int n{0}; //当前key的数量
    bool leaf{true};
    T keys[maxKeySize];
    BTreeNode * child[maxChildSize];

    //二分查找 第一个 >= k的位置
    int bsearch(int k){
        int l = 0,r=n;
        while( l < r){
            int mid = (l+r) >> 1;
            if( keys[mid] < k) l = mid+1;
            else r = mid;
        }
        return l;
    }

    inline bool isFull() { return n == maxKeySize;}
    // 下标i的key的左边孩子
    inline auto& left(int i){ return child[i]; }
    // 下标i的key的右边孩子
    inline auto& right(int i){ return child[i+1]; }

    void traverse(); //遍历

    static BTreeNode* getNewNode() {
        static MeM<BTreeNode, 100000> mem;
        return mem.get();
    }
    /**
     * 插入一个k值,保证当前点是notFull的
     */
    void insertNonFull(int k){
        int i  = bsearch(k); //i是第一个>k的位置
        if( leaf == true){ //这个叶子
            for(int j = n-1;j >=i;j--) //后移
                keys[j+1] = keys[j];
            keys[i] = k;
            n++;
        }
        else { // 这个是 notFull
            //i--; //i是后一个<=k的位置
            if( left(i)->isFull()) {
                splitChild(i, left(i)); //把i空出来
                //上升来的值比k小,那么应该去i+1的左边
                if( keys[i] < k ) i++;
            }
            left(i)->insertNonFull(k);
        }
    }

    //分裂孩子,保证y是full的
    // i keys[i] 要空出来
    // y 指向孩子的
    void splitChild(int i,BTreeNode * y){
        //创建一个新的点
        BTreeNode * z = getNewNode();
        z->n = half;
        z->leaf = y->leaf;

        //后half个点移动到 z上
        // half 其实也是中间的点的下标
        for(int j = maxKeySize-1;j > half ;j--){
            auto zj = j-half-1; // 对应的z上的点
            z->keys[zj] = y->keys[j];
            z->right(zj) = y->right(j);
        }
        z->left(0) = y->right(half);
        y->n = half; //设定y的keys大小

        //当前点的i ->i+1 来空中一个位置
        for(int j=n-1;j>=i;j--){
            keys[j+1] = keys[j];
            right(j+1) = right(j);
        }
        right(i) = z; // 这个点的批向的新child
        keys[i] = y->keys[half];
        n++; //key的数量上升1
    }
    BTreeNode* search(int k) // 从当前点开始search k
    {
        int i = bsearch(k);
        //if 找到位置 与k 相等,返回这个点
        if( keys[i] == k) return this;
        //key没有找到且这个点是leaf,那就是没有找到
        if( leaf == true) return nullptr;
        //递归查找
        return left(i)->search(k); 
    }
};

template<typename T,size_t deg=3>
struct BTree {
    using node = BTreeNode<T, deg>;
    node* search(int k) {
        if( root == nullptr) return nullptr;
        return root->search(k);
    }
    //插入一个新的结点
    void insert(int k){
        //空的结点
        if( root == nullptr){
            root = node::getNewNode();
            root->keys[0] = k;
            root->n = 1;
        }
        else { //Btree 不空
            if( root->isFull() ) { 
                auto s = node::getNewNode();
                s->left(0) = root;
                s->splitChild(0,root); //分裂root
                root = s;
                root->leaf = false;
                //现在root有两个孩子,决定使用哪个
                if(root->keys[0] > k)
                    root->left(0)->insertNonFull(k);
                else
                    root->right(0)->insertNonFull(k);
            }
            else
                root->insertNonFull(k);
        }
    }

/* ===================== 删除 =====================*/
/* ===================== 删除 END =====================*/

    std::string  to_dot(){
        std::stringstream ss;
        ss << "digraph g {\n node[shape=record];\n";
        __to_dot(root,ss);
        ss <<"}";
        return ss.str();
    }
    void __to_dot(node *p ,std::stringstream& ss){
        if( p == nullptr) return;
        auto u = reinterpret_cast<uint64_t>(p);
        ss << u << "[label=\"";
        for( int i =0; i < p->n;i++){
            ss << "f<" << i << ">|" << p->keys[i] << "|";
        }
        ss << "f<" << p->n << ">\"];\n";
        if( p->leaf ) return;
        for( int i =0; i <= p->n;i++){
            ss << u << ":f" << i << "->" << reinterpret_cast<uint64_t>(p->left(i)) << ";\n";
        }
        for( int i =0; i <= p->n;i++)
            __to_dot(p->left(i),ss);
    }
    node * root{nullptr};
private:
};

BTree<int, 2> a;




int main(int argc,char * argv[]){
    int t;
    while ( scanf("%d",&t)!=EOF ) {
        a.insert(t);
    }
    //a.root->splitChild(1, a.root->left(1));

	//a.insert(10);
	//a.insert(20);
	//a.insert(5);
	//a.insert(6);
    //a.insert(12);
	//a.insert(30);
	//a.insert(7);
	//a.insert(17);
	auto x = a.to_dot();
	std::cout << x << std::endl;
    return 0;
}
