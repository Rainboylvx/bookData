#include "Btree.h"


template<typename T,size_t deg>
void BTreeNode<T,deg>::insertNonFull(int k){
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
        keys[i-1] = keys[i];
    n-=1; //key的数量
}

//叶子结点没有前趋与后趋的概念
template<typename T,size_t deg>
T BTreeNode<T,deg>::getPred(int idx){
    auto cur = left(idx);
    while( !cur->leaf)
        cur = cur->child[cur->n];
    return cur->keys[cur->n-1];
}

template<typename T,size_t deg>
T BTreeNode<T,deg>::getSucc(int idx){
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
    right(0) = left(0);

    //child 的首孩子为关键字
    child->keys[0] = std::move(keys[idx-1]);
    child->left(0) = bro->right(bro->n-1);
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
    lc->keys[half] = keys[idx];
    //把 右孩子的值转移过来
    for(int i =0; i < rc->n ; ++i){
        lc->keys[half+1+i] = std::move(rc->keys[i]);
        //把 右的孩子也转移过来
        rc->left(half+1+i) = rc->left(i);
    }
    //把 右的孩子也转移过来
    rc->left(half+1+rc->n) = rc->left(rc->n);

    //把后面的值与孩子移动过来
    for(int i =idx+1;i < n ; ++i){
        keys[i-1] = keys[i]; // TODO std::move
        right(i-1) = right(i); //指针左移动
    }
    lc->n += lc->n+1;
    n--;

    //delete rc;
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
        auto pred = getPred(idx);
        keys[idx] = pred;
        left(idx)->remove(pred);
    }
    //如果右孩子有足够的元素(至少是t)
    //找到后趋 pred ,替换,删除
    else if( right(idx)->n > half){
        auto succ = getSucc(idx);
        keys[idx] = succ;
        right(idx)->remove(succ);
    }
    else { //合并,然后删除
        merge(idx);
        left(idx)->remove(k);
    }
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
            std::cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
        
        // flag 表明 k 所在的
        bool flag = ( (idx==n)? true : false );
        // 如果所在树的上的点是不到t的,fill it
        // fill 可能 borrowFromPrev borrowFromNext,merge
        if( left(idx)->n == half) 
            fill(idx);
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
