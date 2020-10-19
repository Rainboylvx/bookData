---
_id: "17ce48b324"
title: 二叉平衡树BST
date: 2020-10-18 15:25
update: 2020-10-18 15:25
author: Rainboy
---
## 定义
二叉平衡树(Binnary Search Tree)，简写为BST。这是具有如下性质的二叉树

1. 树上的每个节点都带有一个数值，称为节点为的**“关键码”**
2. 节点p的关键码不小于它的左子树中的任意关键码
3. 节点p的关键码不大于它的右子树中的任意关键码

显然BST的中序序列是单调递增的。

## BST的建立

BST建立时，为了方便的查找前趋与后继，保证前趋与后继一定存在，从而不用进行越界判断，建立时带有两个初始的节点为$(-INF,INF)$

## 检索

显然检索的过程是一个dfs的过程

1. 若p == 0 没有找到节点,返回
2. 若a[p] == val 找到节点,返回
3. 若$val > a[p].val$，查找右子树
3. 若$val < a[p].val$，查找左子树

## 插入

与检索类似，插入也是一个DFS的过程。

## 查找前趋

val的“前趋”指的是在BST中关键码小于val的前提下，关键码最大的点

 1. 找到val的节点p，且p有左子树，从p的左孩子出发，一直向右走，就找到了val的前趋。
 2. 找到val的节点p，但p没有左子树，和上面一样，ans即为所求
 3. 没有找到val：些时val的前趋就在已经经过的结点中，ans即为所求

首先**证明1**
找到$a[p].val == val$如果p有左子树,那么它答案就是左子树上的最大值，为什么呢？

设p有一个左祖先x，那么显然子树Z上的点都是小于$a[x].val$的则$x$不是所求

设p有一个右祖先y，那么显示子树Z上的点都是大于$a[x].val的，显然p的左子树树上的点也是大于$a[x].val$的。

得证ans一定在p的左子树上，那么哪个点是p的左子树的最大值呢？显然一直向右走，值会越来越大，直到不能向走为止。

如果p存在且没有左孩子呢？

设p有一个左祖先x，那么显然子树Z上的点都是小于$a[x].val$的则$x$不是所求
设p有一个右祖先y，那么显示子树Z上的点都是大于$a[x].v$，则y可能是答案。显然从p向上的第一个右祖先一定所有右祖先中最大的那个，即为所求。

显然y同样是root到p的路径上的最后一个右父亲，那么也记录经过的点符合条件的最大的那个就是p。

如何p一直没有右祖先呢？答案是不可能，因为我们的BST上存在$-INF$。

如果p不存在呢？如果p不存在，最终会到达一个虚拟的点q，显然q没有左子树，和**情况2**一样。

## 后继

类比“前趋”，val的“后继”指的是在BST中关键码大于val的前提下，关键码最小的点

 1. 找到val的节点p，且p有右子树，从p的右孩子出发，一直向左走，就找到了val的前趋。
 2. 没有找到val：些时val的后继就在已经经过的结点中，ans即为所求
 3. 找到val的节点p，但p没有右子树，和上面一样，ans即为所求

## 节点的删除

 1. 若p的孩子节点的数据小于2，直接删除p，并令p的子节点代替p的位置，与p的父亲相连
 2. 若p的左右子树都存在，则在BST中求出val的后继节点next。**因为next没有左子树**，所以可以直接删除next，并令next的右子树代替next的位置。最后，再让next节点代替p节点，删除p即可。

## 模板代码
<!-- template start -->
```c
namespace BST {
    int tot,root,INF = 1<<30;
    struct node {
        int l,r,val;
    }a[maxn];

    int New(int val){
        a[++tot].val = val;
        return tot;
    }

    void build(){
        New(-INF),New(INF);
        root=1,a[1].r = 2;
    }

    //检索
    int Get(int p,int val){
        if( p == 0 ) return 0; //检索失败
        if( val == a[p].val) return p; //检索成功
        if( val > a[p].val) return Get(a[p].r,val);
        return Get(a[p].l,val);
    }

    //插入
    void Insert(int &p,int val){
        if( p == 0) { //边界，空的结点
            p = New(val); //p是引用，所以父结点的l或r会被更新
            return;
        }
        if( val == a[p].val) return;
        if( val < a[p].val) Insert(a[p].l, val);
        else Insert(a[p].r, val);
    }

    //后继
    int getNext(int val){
        int ans = 2; // a[2].val = INF;
        int p = root;
        while( p ){
            if( val == a[p].val ){
                if( a[p].r > 0){ //有右子树
                    p = a[p].r;
                    while( a[p].l > 0 ) p = a[p].l;
                    ans = p;
                }
                break;
            }
            if( a[p].val > val && a[p].val < a[ans].val ) ans = p;
            if( val < a[p].val ) p = a[p].l;
            else p = a[p].r;
        }
        return ans;
    }
    //前趋
    int getPre(int val){
        int ans = 1; // a[1].val = -INF;
        int p = root;
        while( p ){
            if( val == a[p].val){
                if( a[p].l > 0) { //有左子树
                    p = a[p].l;
                    while( a[p].r > 0) p = a[p].r;
                    ans = p;
                }
                break;
            }
            if( a[p].val < val && a[p].val > a[ans].val) ans = p;
            if( val > a[p].val ) p =a[p].l;
            else p = a[p].r;
        }
        return ans;
    }
    // 删除
    void Remove(int &p,int val){ 
        if( p == 0) return;
        if( val == a[p].val){
            if( a[p].l == 0){ //无左子树
                p = a[p].r;
            }
            else if(a[p].r == 0) {//无右子树
                p = a[p].l;
            }
            else { //有左子树 也有右子树
                int next = a[p].r;
                while(a[next].l > 0) next = a[next].l;
                Remove(a[p].r, a[next].val);
                // 令节点next代替节点p
                a[next].l = a[p].l,a[next].r = a[p].r;
                p = next;
            }
        }
        if( val < a[p].val) Remove(a[p].l, val);
        else Remove(a[p].r, val);
    }
}
```
<!-- template end -->


## BST的退化

面对随机数据，BST的每次操作的期望复杂度为$O(logN)$，但面对一个有序的数据的时候，BST会退化成一条链，每次的操作复杂度$O(N)$。


## 参考/引用

 - 《算法竞赛进阶指南》P232-P236
