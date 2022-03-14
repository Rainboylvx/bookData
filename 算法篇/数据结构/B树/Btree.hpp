// Author:Rainboy 
// ver : 0.0.1 
// last update : 2021-12-21 09:52
#pragma once
#include <array>
#include <iostream>
#include <sstream>


template<typename T,size_t deg>
struct BTreeNode
{
    static constexpr int maxKeySize{deg*2-1}; //最多key大小
    static constexpr int maxChildSize{deg*2}; //最多child大小
    static constexpr int degree{deg};
    static constexpr int half{deg-1}; //full之后的的一半

    //~BTreeNode(){ //析构
        //std::cout << std::hex <<  "delete "<< reinterpret_cast<uint64_t>(this) << std::endl;
        ////if(leaf) return;
        ////for(int i=0;i<=n;++i){
            ////delete child[i];
        ////}
    //}
    void cdtor(){  //递归的删除节点
        if( leaf == true) return;//边界
        for(int i=0;i<=n;++i){
            child[i]->cdtor();
            delete child[i];
        }
    }

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
        //static MeM<BTreeNode, 300000> mem;
        //return mem.get();
        auto x = new BTreeNode<T, deg>();
        //std::cout << std::hex <<  "new "<< reinterpret_cast<uint64_t>(x) << std::endl;
        return x;
    }

    /**
     * 插入一个k值,保证当前点是notFull的
     */
    void insertNonFull(T& k);

    //分裂孩子,保证y是full的
    // i keys[i] 要空出来
    // y 指向孩子的
    void splitChild(int i,BTreeNode * y);
    // 从当前点开始search k
    BTreeNode* search(int k); 

/* ===================== 删除 =====================*/
    // 分成8个函数来使用
    //1) remove
    //2) removeFromLeaf
    //3) removeFromNonLeaf
    //4) getPred
    //5) getSucc
    //6) borrowFromPrev
    //7) borrowFromNext
    //8) merge
    //9) findKey

    /**
     * 删除值k
     */
    void remove(int k);

    /**
     * 从leaf上删除下标为idx的点
     */
    void removeFromLeaf(int idx);

    /**
     * 从一个内部点上删除下标为idx的点
     */
    void removeFromNonLeaf(int idx);

    // 得到下标为idx这个key的前趋
    T& getPred(int idx);

    // 得到下标为idx这个key的后趋
    T& getSucc(int idx);

    // 填充 idx下标的孩子,如果这个孩子少于t-1keys
    void fill(int idx);

    // 借idx的左兄弟借一个key,放到idx上
    void borrowFromPrev(int idx);

    // 借idx的右兄弟借一个key,放到idx上
    void borrowFromNext(int idx);

    // 合并 idx的左右孩子
    void merge(int idx);
/* ===================== 删除 END =====================*/

    //点移动
    //从 src的下标为src_pos点开始到dst的下标dst_pos的点 移size个点
    //只移动每个点的右孩子
    void moveBettwenTwo(BTreeNode* src,BTreeNode* dst,int src_pos,int dst_pos,int size){
        if(src == dst) { //两都不能一样
            std::cout << "error at"; // TODO 
        }
        for(int i = size-1; i>=0; --i){
            dst->keys[dst_pos+i] = std::move(src->keys[src_pos+i]);
        }
    }
    //每个点从i开始向左移动1格
    //   
    //   
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   | 1 | 2 | 3 | 4 |   |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //          x   y   z
    //
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  | 1 | 2 | 3 | 4 |   |   |
    //  +---+---+---+---+---+---+
    //      |   |   |   |   |   |    
    //      v   v   v   v   v   v    
    //      x   y   z
    //
    //
    void moveLeftOne(int pos){
        for(int i = pos ; i< n;i++){
            keys[i-1] = std::move(keys[i]);
            right(i-1) = right(i);
        }
        //n-=1;
    }

    //   
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   | 1 | 2 | 3 | 4 |   |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //          x   y   z
    //
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   |   | 1 | 2 | 3 | 4 |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //              x   y   z
    void moveRightOne(int pos){
        for(int i = n ; i > pos ;i--){
            keys[i] = std::move(keys[i-1]);
            right(i) = right(i-1);
        }
        //n+=1;
    }
};

template<typename T,size_t deg=3>
struct BTree {
    using node = BTreeNode<T, deg>;

    ~BTree(); //析构函数

    node* search(T& k) {
        if( root == nullptr) return nullptr;
        return root->search(k);
    }
    //插入一个新的结点
    void insert(T& k);
    void remove(const T& k);
    void traverse(); //遍历

    std::string  to_dot(){
        std::stringstream ss;
        ss << "digraph g {\n node[shape=record];\n";
        __to_dot(root,ss);
        ss <<"}";
        return ss.str();
    }
    void __to_dot(node *p ,std::stringstream& ss){
        if( p == nullptr ) return;
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
};

template<typename T,size_t deg>
void BTreeNode<T,deg>::insertNonFull(T& k){
    int i  = bsearch(k); //i是第一个>k的位置
    if( leaf == true){ //这个叶子
        for(int j = n-1;j >=i;j--) //后移
            keys[j+1] = std::move(keys[j]);
        keys[i] = std::move(k);
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

template<typename T,size_t deg>
void BTreeNode<T,deg>::splitChild(int i,BTreeNode * y){
    //创建一个新的点
    BTreeNode * z = getNewNode();
    z->n = half;
    z->leaf = y->leaf;

    //后half个点移动到 z上
    // half 其实也是中间的点的下标
    for(int j = maxKeySize-1;j > half ;j--){
        auto zj = j-half-1; // 对应的z上的点
        z->keys[zj] = std::move(y->keys[j]);
        z->right(zj) = y->right(j);
    }
    z->left(0) = y->right(half);
    y->n = half; //设定y的keys大小

    //当前点的i ->i+1 来空中一个位置
    for(int j=n-1;j>=i;j--){
        keys[j+1] = std::move(keys[j]);
        right(j+1) = right(j);
    }
    right(i) = z; // 这个点的批向的新child
    keys[i] = std::move(y->keys[half]);
    n++; //key的数量上升1
}

template<typename T,size_t deg>
BTreeNode<T,deg>* BTreeNode<T,deg>::search(int k) // 从当前点开始search k
{
    int i = bsearch(k);
    //if 找到位置 与k 相等,返回这个点
    if( keys[i] == k) return this;
    //key没有找到且这个点是leaf,那就是没有找到
    if( leaf == true) return nullptr;
    //递归查找
    return left(i)->search(k); 
}


// ============= 删除 =============
template<typename T,size_t deg>
void BTreeNode<T,deg>::removeFromLeaf(int idx){
    for(int i = idx+1;i < n; ++i)
        keys[i-1] = std::move(keys[i]);
    n-=1; //key的数量
}

//叶子结点没有前趋与后趋的概念
template<typename T,size_t deg>
T& BTreeNode<T,deg>::getPred(int idx){
    auto cur = left(idx);
    while( !cur->leaf)
        cur = cur->child[cur->n];
    return cur->keys[cur->n-1];
}

template<typename T,size_t deg>
T& BTreeNode<T,deg>::getSucc(int idx){
    auto cur = right(idx);
    while( !cur->leaf)
        cur = cur->child[0];
    return cur->keys[0];
}

//
//        idx-1 idx
//        +---+---+
//        |   |   |
//        +---+---+
//        |   |   |
//     +--+   |   +--+
//     v      v      v
//   bro     child    
         
template<typename T,size_t deg>
void BTreeNode<T,deg>::borrowFromPrev(int idx){
    auto child = left(idx); //这个孩子
    auto bro   = left(idx-1);// 兄弟

    // child 所有孩子向右移动一格
    child->moveRightOne(0);
    child->right(0) = child->left(0);// p[ ]p[1] [2]

    //注意当前的关键字为 keys[idx-1]
    //        idx-1 idx   idx  
    //        +---+ +---+ +---+
    //        |   | |   | |   |
    //        +---+ +---+ +---+
    //     |       |
    //     |       |
    //     v       v
    //     idx-1   idx
    //
    child->keys[0] = std::move(keys[idx-1]);
    child->left(0) = bro->right(bro->n-1); //为bro的最后一个
    child->n +=1;

    keys[idx-1] = std::move(bro->keys[bro->n-1]);
    bro->n -=1;

}

template<typename T,size_t deg>
void BTreeNode<T,deg>::borrowFromNext(int idx){
    auto child = left(idx); //这个孩子
    auto bro   = right(idx);// 兄弟

    // 把当前key下放到孩子
    child->keys[child->n] = std::move(keys[idx]);

    //兄弟节点的首孩子的左变为 孩子的末尾节点的右
    child->right(child->n) = bro->left(0);
    child->n +=1;

    keys[idx] = std::move(bro->keys[0]);

    //兄弟所有孩子向前移动一格
    bro->left(0) = bro->right(0);
    bro->moveLeftOne(1);
    bro->n -=1;

}


template<typename T,size_t deg>
void BTreeNode<T,deg>::merge(int idx){
    auto lc = left(idx); //左孩子
    auto rc = right(idx); //右孩子
    // 把key放到左孩子的末尾
    lc->keys[half] = std::move(keys[idx]);
    //把 右孩子的值转移过来
    for(int i =0; i < rc->n ; ++i){
        lc->keys[half+1+i] = std::move(rc->keys[i]);
        //把 右的孩子也转移过来
        lc->left(half+1+i) = rc->left(i);
    }
    //把 右的孩子也转移过来
    lc->left(half+1+rc->n) = rc->left(rc->n);

    //把后面的值与孩子移动过来
    for(int i =idx+1;i < n ; ++i){
        keys[i-1] = std::move(keys[i]); // TODO std::move
        right(i-1) = right(i); //指针左移动
    }
    lc->n += rc->n+1;
    n--;

    delete rc;
    return;
}


/**
 * 如果left(idx)这个孩子的结点key数量等于 t-1 key 就填充它
 */
template<typename T,size_t deg>
void BTreeNode<T,deg>::fill(int idx){
    //如果有前一个bro 且bro不是 half,向它借
    if( idx !=0 && child[idx-1]->n > half)
        borrowFromPrev(idx); 
    else if( idx != n && child[idx+1]->n > half)
        borrowFromNext(idx);
    //此时两个兄弟都 half,唯有合并
    else {
        if(idx !=n)
            merge(idx);
        else
            merge(idx-1);
    }

}


template<typename T,size_t deg>
void BTreeNode<T,deg>::removeFromNonLeaf(int idx){
    auto k = std::move(keys[idx]);

    //如果左孩子有足够的元素(至少是t)
    //找到前趋 pred ,替换,删除
    if( left(idx)->n > half){
        auto pred = getPred(idx); //这里应该改成move
        keys[idx] = std::move(pred);
        left(idx)->remove(pred);
    }
    //如果右孩子有足够的元素(至少是t)
    //找到后趋 pred ,替换,删除
    else if( right(idx)->n > half){
        auto succ = getSucc(idx);
        keys[idx] = std::move(succ);
        right(idx)->remove(succ);
    }
    else { //合并,然后删除
        merge(idx);
        left(idx)->remove(k);
    }
}

template<typename T,size_t deg>
void BTreeNode<T,deg>::traverse(){
    for(int i= 0; i < n; ++i){
        if( leaf == false)
            child[i]->traverse();
        std::cout<< keys[i] << " ";
    }
    //最后一个孩子
    if(leaf == false)
        child[n]->traverse();
}

template<typename T,size_t deg>
void BTreeNode<T,deg>::remove(int k){
    int idx = bsearch(k);

    // 找到了这个key
    if( idx < n && keys[idx] == k){ 
        if( leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    // 没有找到了这个key
    else {

        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            //std::cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
        
        // flag 表明 k 所在的
        bool flag = ( (idx==n)? true : false );
        // 如果所在树的上的点是不到t的,fill it
        // fill 可能 borrowFromPrev borrowFromNext,merge
        if( left(idx)->n == half) //填充 第idx个孩子
            fill(idx);           //保证孩子至少有t个key
        // fill 可能 borrowFromPrev borrowFromNext,merge
        //
        //合并之后删除哪里
        //如果是br
        
        // flag 原来是最后一个点
        // idx > n 表明合并了到前面了
        if(flag && idx > n)
            child[idx-1]->remove(k);
        else
            child[idx]->remove(k);
    }
}

// ============================= Btree =============================

template<typename T,size_t deg>
void BTree<T,deg>::remove(const T& k){
    if( root == nullptr ){
        std::cout << "The three is empty \n";
        return;
    }
    root->remove(k);

    //如果删除后 root有0个key
    //使root的第一个孩子作为新root
    if( root->n == 0){
        auto tmp = root;
        if( root ->leaf)
            root = nullptr;
        else
            root = root->child[0];
        tmp->leaf = true;
        delete tmp;
    }
}


template<typename T,size_t deg>
void BTree<T,deg>::traverse(){ //遍历
    if( root !=nullptr )
        root->traverse();
}

template<typename T,size_t deg>
void BTree<T,deg>::insert(T& k){ //遍历
    //空的结点
    if( root == nullptr){
        root = node::getNewNode();
        root->keys[0] = std::move(k);
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

template<typename T,size_t deg>
BTree<T,deg>::~BTree(){ //遍历
    if( root == nullptr) return;
    root->cdtor();
    delete root;
}
