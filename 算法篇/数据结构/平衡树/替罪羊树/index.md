---
_id: "2c8463b9b7"
title: "替罪羊树[Scapegoat Tree]"
date: 2019-11-01 16:50
update: 2019-11-01 16:50
author: Rainboy
#password: tzy42
---

@[toc]

> 暴力即是优雅


## 原理: 暴力重构

<<<< viz-gallery(title="重构演示",engine="dot",height="400")

<% 
var log =["重构root的左子树","左子树中序遍历拉成一条直线","从中间「拎」起来"]
var engine = "dot"
for(let i=1;i<=3;i++){
    var page = `dot/重构/${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<

我们发现:

 - 重构后,整个树依然是一颗$BST$
 - 「拎」的操作是分治的,先取中间点,然后分别对左右区间做同样的操作,时间是$O(n)$
 - 「拎」操作后,子树会尽可能的平衡

## 核心操作

### 点的信息

```c
struct Node {
    int l,r,val; //左,右孩子,值
    //以当前点为根的子树的,大小(点的数量),实际大小
    int size,fact; 
    bool exist; //是否删除
};
Node tzy[maxn]; //内存池
int cnt,root; //内存池计数,根结点编号
/* 内存池中取一个新的结点 */
void newnode(int &now,int val){
    now = ++cnt;
    tzy[now].val = val;
    tzy[now].size = tzy[now].fact=1;
    tzy[now].exist = true;
}
```

使用了**懒惰删除**,这是替罪羊的精髓

### 删除/懒惰删除

替罪羊树的删除节点并不是真正的删除，而是惰性删除,即给节点增加一个已经删除的标记，删除后的节点与普通节点无异，只是不参与查找操作而已

$Q1$:为什么可以标记删除,而不是真正删除?

```viz-dot
<%- include("dot/del_1.dot") %>
```

如上图

- 标记删除$5$后,依然可以利用$BST$的性质找到$6$
- 标记删除的点,在查找的是,认为它不存在,但是利用的它
- 重构就直接丢弃
- 如果加入的一个新点,就是标记删除的点,那就恢复它$exist=true$;
- 不影响平衡性


```c
/* 删除 */
void del(int now,int val){
    if(tzy[now].exist && tzy[now].val == val){
        tzy[now].exist = false;
        tzy[now].fact--;
        check(root, now); //后面讲
        return;
    }
    tzy[now].fact--;
    if( val < tzy[now].val)
        del(tzy[now].l,val);
    else
        del(tzy[now].r,val);
}
```

## 插入

插入点和普通的BST一样,直接插入就可以了


```c
/* 插入 */
void ins(int &now,int val){
    if(!now){
        newnode(now, val);
        check(root,now); //后面讲
        return;
    }
    tzy[now].size++;
    tzy[now].fact++;
    if( val < tzy[now].val)
        ins(tzy[now].l,val);
    else
        ins(tzy[now].r,val);
}
```


## 重构(核心)

### 插入导致的不平衡

插入点后有可能导致树不平衡,如何判断一个树不平衡呢?

> 我们先了解下它的一个基本理论：**α权重平衡(α-weight-balanced)**。下文所述的平衡均为α权重平衡。
> 我们认为一棵树xx是平衡的当且仅当它每一棵子树满足下列条件：
> 
> $$ \begin{aligned} \text{size}(x.\text{left}) &\le \alpha \cdot \text{size}(x) \\ \text{size}(x.\text{right}) &\le \alpha \cdot \text{size}(x) \end{aligned} $$
> 
> 其中，$ \alpha \in [0.5, 1] $。

> 这个$\alpha$可能会令人非常疑惑。我们首先来思考一下两个极值：$1$和$0.5$。

> 当$a = 1$时，无论什么二叉树都会被视为平衡的，因为左右子树的大小不会超过这棵树的大小。这正对应着普通的二叉搜索树。

> 而当$ a = 0.5$时，这时的要求将非常严格，左右子树的大小都必须是这棵树的大小的一半，此时只有完全二叉树能满足平衡要求。AVL树就是尝试保持这种平衡。

> 我们都知道，二叉搜索树极易退化，而AVL树又为了平衡导致常数相当大，并且代码又臭又长，几乎没有人写。

> 作为AVL树的改进，红黑树并不追求完美的平衡。通过放宽一些严格的平衡限制，保证了$ \alpha = 0.666\dots $的平衡，同时降低了常数，有着优良的性能。现在绝大多数语言的标准库都有它的身影。然而，红黑树对于OI竞赛而言代码量太大，不适合现场发挥。

>较为常用的Treap和Splay树则对$\alpha$没有强制的限定，它们利用随机化的思想来使树尽可能平衡，即它们会尽量使$\alpha$值降低。我粗略测定了Treap、非旋转式Treap和Splay的$\alpha$。结果如下：

> | BST  测试                  |   1   |   2   |   3   |   4   |   5   |    平均   |
> |-----------------------------|:-----:|:-----:|:-----:|:-----:|:-----:|:---------:|
> | Splay（5个不同数据）        | 0.758 | 0.588 | 0.582 | 0.612 | 0.759 | **0.659** |
> | Treap（同一个数据）         | 0.766 | 0.578 | 0.601 | 0.587 | 0.781 | **0.662** |
> | 非旋转式Treap（同一个数据） | 0.914 | 0.860 | 0.613 | 0.678 | 0.803 | **0.773** |
> 
> 以上的结果仅供参考。可见一般的BST都能够使$\alpha$维持在$0.6$到$0.7$之间

摘自:https://riteme.site/blog/2016-4-6/scapegoat.html

我们这里选的$\alpha$为$0.75$

### 懒惰删除导致的重构

想一想上面的懒惰删除, 当然我们不能无止尽地进行标记。如果被标记的节点数超过了整颗子树的$0.3$，我们就直接将整棵树重构，同时清除删除的节点。
为什么可以选0.3? 因为: $1-0.75 \approx  0.3$

### 重构的时机

从插入/删除的位置开始一层一层往上回溯的时候，对于每一层都进行一次判断,，一直找到最后一层不满足该条件的层序号（也就是从根开始的第一层不满足该条件的层序号），然后从该层开始重构以该层为根的子树（一个节点导致树的不平衡，就要导致整棵子树被重构，估计这也是“替罪羊”这个名字的由来吧）。

### 代码实现


```c
const double alpha  = 0.75;
const double del_alpha = 0.3;
const int base_node = 5;

/* 是否平衡 */
bool imbalence(int now){
    if( max(tzy[tzy[now].l].size , tzy[tzy[now].r].size) > tzy[now].size*alpha + base_node
    || tzy[now].size - tzy[now].fact > tzy[now].size*del_alpha + base_node)
        return true;
    return false;
}

vector<int> v;
/* 中序遍历 */
void middle_sort(int now){
    if(!now ) return;
    middle_sort(tzy[now].l);
    if( tzy[now].exist)  v.push_back(now);
    middle_sort(tzy[now].r);
}

/* 分治重构 */
void lift(int l,int r,int &now){
    if(l == r){ //叶子结点
        now = v[l];
        tzy[now].l = tzy[now].r = 0;
        tzy[now].size = tzy[now].fact = 1;
        return ;
    }
    int m =(l+r)>> 1;

    /* >=key 放右方,见下面[细节] */
    while( l < m && tzy[v[m]].val == tzy[v[m-1]].val) m--;
    now=v[m];  //编号
    /* 如果左区间还存在 */
    if( l < m ) lift(l, m-1, tzy[now].l);
    else tzy[now].l = 0;
    /* 右区间一定存在 */
    lift(m+1,r,tzy[now].r);

    tzy[now].size = tzy[ tzy[now].l ].size + tzy[ tzy[now].r ].size+1;
    tzy[now].fact = tzy[ tzy[now].l ].fact + tzy[ tzy[now].r ].fact+1;
}

/* 重建 */
void rebuild(int &now){
    v.clear(); // 清空中序序列
    middle_sort(now);
    if( v.empty()){ //中序后,为空
        now = 0;
        return;
    }
    lift(0,v.size()-1,now);
}

/* 更新一条链 */
void update(int now,int end){
    if(!now) return;
    if( tzy[end].val < tzy[now].val){
        update(tzy[now].l, end);
    }
    else update(tzy[now].r, end);
    tzy[now].size = tzy[ tzy[now].l ].size + tzy[ tzy[now].r ].size+1;
}

void check(int &now,int end){
    if( now == end) return;
    if( imbalence(now)){
        rebuild(now);
        update(root, now);
        return;
    }
    if( tzy[end].val < tzy[now].val)
        check(tzy[now].l, end);
    else check(tzy[now].r, end);
}
```

### 细节

如果$m$指向的一片相同值,$m$应该移向最左边的一个位置

```viz-dot
<%- include("dot/ps_1.dot") %>
```

形成

```viz-dot
<%- include("dot/ps_2.dot") %>
```


使用头递归的方式来更新

## 排名 rank

得到值$val$的排名,保证$val$的树上存在

核心思想:**a找到比val值小的结点数+1**

```c
/* 得到排名 */
int getrank(int val){
    int now  = root,rank=1;
    while(now) { //点不为空
        if( tzy[now].val >= val) //比val大
            now = tzy[now].l;
        else{       // 比val小
            rank+= tzy[now].exist + tzy[ tzy[now].l ].fact;
            now = tzy[now].r;
        }
    }
    return rank;
}
```
## 得到排名为rank的值

核心思想: **根据左子树的数量来决定向左还是向右走**

```c
/* 得到排名 rank的 值 */
int getnum(int rank){
    int now = root;
    while(now) {
        if( tzy[now].exist && tzy[ tzy[now].l ].fact + tzy[now].exist == rank)
            break;
        else if( tzy[tzy[now].l].fact >= rank)
            now = tzy[now].l;
        else {
            rank -= tzy[tzy[now].l].fact + tzy[now].exist;
            now = tzy[now].r;
        }
    }
    return tzy[now].val;
}
```

## 前驱

```c
int ans = getnum( getrank(x)-1);
```

$Q$:为什么不是`getnum( getrank(x-1) )`?

针对上面的「细节树」如果想得到$5$的前驱`getnum( getrank(5-1) )==5`?

根据上面的[细节],$ \geq val$都尽量放右边,

## 后继

```c
int ans = getnum( getrank(x+1));
```

$Q$:为什么不是`getnum( getrank(x)+1 )`?

针对上面的「细节树」如果想得到$5$的后驱`getnum( getrank(5)+1 )==5`?



## 模板代码

<!-- template start -->
```c
struct ScapeGoatTree {
    //v 点值 | sz size 子树点数 | rs realsize 子树大小 | cn cnt当前点的数量 | c[2] child[2] 左右孩子
    typedef struct { int v,sz,rs,cn,c[2]; } node; 
    node tr[maxn];
    int root,idx=0,dc=0,top=0,sta[maxn]; // dc = delele count

    int fl[maxn],flcn=0;
    inline void flpush(int p){ fl[++flcn] = p; }

    inline int &lc(int p) { return tr[p].c[0];}
    inline int &rc(int p) { return tr[p].c[1];}
    inline int &c(int p,int i){return tr[p].c[i];};
    inline int &sz(int p) { return tr[p].sz;}
    inline int &cn(int p) { return tr[p].cn;}
    inline int &va(int p) { return tr[p].v;}
    inline int &rs(int p) { return tr[p].rs;}

    // 是否平衡
    bool Imb(int p){ return max(rs(lc(p)),rs(rc(p)))-5 > rs(p)*0.75; }
    //bool Imb(int p){ return max(rs(lc(p)),rs(rc(p)))-1 > rs(p)*0.6; }
    void New(int &p,int val){ tr[p = ++idx] = {val,1,1,1,{0,0}}; }
    //void New(int &p,int fa,int val){ tr[p = ++idx] = {val,1,1,1,fa,{0,0}}; }

    void pushup(int p){
        sz(p) = sz(lc(p)) + sz(rc(p)) + cn(p); 
        rs(p) = rs(lc(p)) + rs(rc(p)) + 1; 
    }
    void dfs(int p){
        if(!p) return;
        dfs(lc(p));
        if( cn(p)) sta[++top] = p;
        else dc--;
        dfs(rc(p));
    }
    void Build(int l,int r,int &p){
        if( l > r) { p = 0; return; };
        if( l == r) {
            p = sta[l];
            rs(p)=1;
            rc(p)=lc(p)=0;
            sz(p)=cn(p);
            return;
        }
        int m = (l+r) >> 1;
        p = sta[m];
        Build(l,m-1,lc(p));
        Build(m+1,r,rc(p));
        pushup(p);
    }
    void Rebuild(int &p){
        top = 0;
        dfs(p);
        Build(1,top,p);
    }
    int find(int v){
        int p = root; flcn =0;
        while(c(p,v > va(p))  && v != va(p) ){
            flpush(p);
            p = c(p,v > va(p));
        }
        flpush(p);
        return p;
    }
    void ins(int v){
        if(!root){
            New(root,v);
            return;
        }
        int p = find(v);
        if( va(p) == v) cn(p)++;
        else New(c(p,v>va(p)), v);

        int bba = -1;
        for(int i=flcn;i>=1;--i){
            pushup(fl[i]);
            if( Imb(fl[i])) bba = i;
        }
        if( ~bba){
            if( bba == 1) Rebuild(root);
            else {
                Rebuild( c(fl[bba-1],va(fl[bba]) > va(fl[bba-1])) );
                for(int i =bba-1;i>=1;--i) pushup(fl[i]);
            }
        }
    }

    void del(int v){
        int p = find(v);
        if(va(p) != v || !p ) return; //没有找到这个点
        if(!--cn(p)) dc++; //这个点删空了,计数
        if(dc> sz(root)) Rebuild(root);
        else  //更新链上的值
            for(int i = flcn ;i>=1;--i) pushup(fl[i]);
    }
    // 每一次向右走，排名都会增加
    // 边界1: va(p) != p 但已经不向下走了，
    //          还要加上lc(p)的数量
    //          如果va(p) < v 还加上cn(p)
    // 边界2: va(p) == v 还要加上lc(p)的数量
    int Rank(int v){ //得到v的排名
        int p = root , ans = 1;
        while( va(p) != v && c(p,v>va(p)) ){
            if( v > va(p)) ans += sz(lc(p)) + cn(p);
            p = c(p,v > va(p));
        }
        return ans + sz(lc(p)) + ( va(p) < v ? cn(p) : 0);
    }

    // 得到排名为k的值
    // 排名树的数量是 sz(lc(p))
    // 排名为k的数在左子树上： sz(lc(p)) >= k
    // 排名为k的数在右子树上： sz(lc(p)) + cn(p) < k
    // 排名为k的数在当前点上： 不满足上面的两个条件
    int at(int k){
        int p = root;
        while( p ){
            if( sz(lc(p)) >= k ) p = lc(p);
            else if ( sz(lc(p)) + cn(p) < k)
                k -= sz(lc(p)) + cn(p), p = rc(p);
            else break;
        }
        return p;
    }
    // pre  前趋
    // 得到v的排名k
    // 得到排名为k-1的数
    // 1 2 2 2 5
    // 1 2     5
    // rank(5) == rank(4) == rank(3)
    // at(rank(5-1)) = 5
    inline int pre(int v){
        return va(at(Rank(v)-1));
    }
    // next 后继
    // 得到的v+1的排名，
    // 1 2 2 2 5
    // 1 2     5 rank 显然应该Rank(v+1)
    // rank(2)+1 = 5
    // rank(3)+1 = 6
    // rank(4)+1 = 6
    // Rank(2) = 2 Rank(3) = 5 at(Rank(2)+1) = 2
    inline int next(int v){
        return va(at(Rank(v+1)));
    }
} scgt;
```
<!-- template end -->

## 模板题目

题目地址 [luogu P3369 【模板】普通平衡树](https://www.luogu.org/problem/P3369)


**代码**

::: fold
<!-- template start -->
```c
<%- include("code/3369.cpp") %>
```
<!-- template end -->
:::


## 参考

 - [【AgOHの数据结构】平衡树专题之壹 替罪羊树](https://www.bilibili.com/video/av58948184)
 - [替罪羊树(Scapegoat Tree)](https://riteme.site/blog/2016-4-6/scapegoat.html)
 - [替罪羊树 Scapegoat Tree  & BZOJ3224](https://zhuanlan.zhihu.com/p/21263304)
