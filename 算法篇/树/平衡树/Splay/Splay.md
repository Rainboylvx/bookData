---
_id: 5158e4b779
title: "Splay入门"
date: 2019-11-11 16:38
update: 2019-11-11 16:38
author: Rainboy
password: spl42
---

@[toc]


## 前置知识

$AVL$平衡树,主要是理解,旋转不会破坏平衡,甚至可以改进平衡,推荐观看:[作品【AgOHの数据结构】平衡树专题之叁 树旋转与AVL树](https://www.bilibili.com/video/av60770002)


## 简介

Splay又叫做: 文艺平衡树,分裂树, 伸展树,它由丹尼尔·斯立特Daniel Sleator 和 罗伯特·恩卓·塔扬Robert Endre Tarjan(~~怎么又是你~~) 在1985年发明的

>  在伸展树上的一般操作都基于伸展(splaying)操作：假设想要对一个二叉查找树执行一系列的查找操作，为了使整个查找时间更小，被查频率高的那些条目就应当经常处于靠近树根的位置。于是想到设计一个简单方法， 在每次查找之后对树进行重构，把被查找的条目搬移到离树根近一些的地方。伸展树应运而生。伸展树是一种自调整形式的二叉查找树，它会沿着从某个节点到树根之间的路径，通过一系列的旋转把这个节点搬移到树根去。 --- [百度百科](https://baike.baidu.com/item/伸展树/7003945)

又上可知:**伸展(splaying)**:**把结点搬到根这种操作**

均摊复杂度$(Olog_2n)$

## 结点维护信息


```c
struct Node{ int val,fa,ch[2],cnt,size; };
```
| $val$ | $fa$ | $ch[2]$  | $cnt$    | $size$     |
|-------|------|----------|----------|------------|
| 值    | 父亲 | 左右孩子 | 出现次数 | 子结点数量 |


其中$ch[0],ch[1]$分别存的是结点的左右孩子的编号

```c
const int maxn = 1e5+5;
struct Node
{
    int fa,ch[2],val,cnt,size;  //ch[0]是左儿子，ch[1]是右儿子
}spl[maxn];
int cnt,root; //内存池计数,根编号

//新建节点，要注意fa指针的初始化
void newnode(int &now,int fa,int val)
{
    spl[now=++cnt].val=val;
    spl[now].fa=fa;
    spl[now].size=spl[now].cnt=1;
}
```

## 基础操作

 - $ident(x,f)$:判断节点$x$是父亲节点的左儿子还是右儿子
 - $connect(int x, int fa, int ch)$:x节点将成为fa节点的ch孩子
 - $push_up(x)$用孩子的size更新自己的size

```c
bool ident(int x,f){ return spl[f].ch[1] == x; }

void connect(int x,int fa,int ch){
    spl[x].fa = fa;
    spl[fa].ch[ch] = x;
}

inline void push_up(int x)
{
    spl[x].size=spl[spl[x].ch[0]].size+spl[spl[x].ch[1]].size+spl[x].cnt;
}
```


## 核心操作:旋转

### 1.基础

旋转操作并不会破坏树的**有序性**(中序遍历是上升序列),那么右两种基本的旋转:

- $zig$右旋:**使root的左孩子变成根**
- $zag$左旋:**使root的右孩子变成根**

```viz-dot
<%- include("dot/base_rotate_zig_zag.dot") %>
```

### 2.链型

[链型-动画]( <%= USER.dsa_site%>#/splay-rotate-2)

 - 从`\` 到 `/` 为$zag \text{-} zag$,左旋两次,先对$x$的父亲$f$进行左旋,然后对$x$进行左旋
 - 从`/` 到 `\` 为$zig \text{-} zig$,右旋两次,先对$x$的父亲$f$进行右旋,然后对$x$进行右旋


### 3:之字型

- [ 之字型 > -动画 ]( <%= USER.dsa_site%>#/splay-rotate-3-1)
    - 从`>` 到 `<` 为$zig \text{-} zag$,先右旋后左旋,先对$x$进行右旋,然后对$x$进行左旋
- [ 之字型< -动画]( <%= USER.dsa_site%>#/splay-rotate-3-2)
    - 从`<` 到 `>` 为$zag \text{-} zig$,先左旋后右旋,先对$x$进行左旋,然后对$x$进行右旋


例子:

todo
然后, 把某个结点翻转上去?

### 综合: `rotate`

综上,设x为要旋转到上面的点,f为x的父亲,ff为f的父亲,发现:

 - 如果$indent(x) == indent(f)$,为一条链的情况,否则为之字的情况
 - 一共有6种情况

::: line
```viz-dot
<%- include("dot/state1.dot") %>
```
```viz-dot
<%- include("dot/state2.dot") %>
```

```viz-dot
<%- include("dot/state3.dot") %>
```
```viz-dot
<%- include("dot/state4.dot") %>
```

```viz-dot
<%- include("dot/state5.dot") %>
```

```viz-dot
<%- include("dot/state6.dot") %>
```
:::


只针对zig(x)和zag(x)来说,都是要把x提升,**具体是左旋还是右旋,要看x是父亲的左孩子还是右孩子,每次旋转都会让四个点,三条边重新建立关系**

 - x是左孩子,右旋过程: 1:`connect(x.rchild,f,0)`,2:`connect(x,ff,f == ff.rchild)`,3:`connect(f,x,1)`
 - x是右孩子,左旋过程: 1:`connect(x.lhild,f,1)`,2:`connect(x,ff,f == ff.rchild)`,3:`connect(f,x,0)`

我们完全可以把这两种关系综合成一个:


```c
void rotate(int x)      //合二为一的旋转
{
    // f:父亲,ff:祖父,k:x是父亲的那个孩子
    int f=spl[x].fa,ff=spl[f].fa,k=ident(x,f);
    connect(spl[x].ch[k^1],f,k);        //x的孩子作为父亲f的孩子
    connect(x,ff,ident(f,ff));          //x作为祖父的孩子
    connect(f,x,k^1);                   //f作为x的孩子
    push_up(f),push_up(x);                //别忘了更新大小信息
}
```

## 核心操作: 伸展(splay)

我们认为根结点(root)的父亲为$0$.

```c
void splaying(int x,int top)//代表把x转到top的儿子，top为0则转到根结点
{
    // !top => top == 0
    if(!top) 
        root=x; //改变根结点
    while(spl[x].fa!=top) //
    {
        int f=spl[x].fa,ff=spl[f].fa;
        //祖父不是目的结点,要旋转两次,因为有三个点
        if(ff!=top) 
            rotate( ident(f,ff)^ident(x,f)? x : f );
            //直线:旋转父亲
            //之字:旋转自己
        rotate(x);      //最后一次都是旋转自己
    }
}
```

::: warning
- 每个点初始化的时候,fa默认为0,所有root的父亲是0
- $fa[root] = 0$,所有当top==0的时候,可以旋转到根结点,自己仔细想一下
:::

## 其他操作

### 插入:ins


```c
// fa默认为0,now默认为root
void ins(int val,int &now=root,int fa=0)    //递归式，要传fa指针
{
    if(!now) //当前是空结点,建立,伸展到root
        newnode(now,fa,val),splaying(now,0);
    else if(val<spl[now].val) //去左子树
        ins(val,spl[now].ch[0],now);
    else if(val>spl[now].val) //去右子树
        ins(val,spl[now].ch[1],now);
    else //相等,计数+1,伸展到root
        spl[now].cnt++,splaying(now,0);
}
```

### 删除:del

```c
//删除结点，要注意fa指针的维护
void delnode(int x)
{
    splaying(x,0);//把x伸展到root
    if(spl[x].cnt>1) spl[x].cnt--;//计数-1
    else if(spl[x].ch[1]) //存在右子树
    {
        int p = spl[x].ch[1];//p 右子树编号
        //p 右子树中的最小值
        while(spl[p].ch[0]) p=spl[p].ch[0];
        splaying(p,x);//p 伸展到 x的孩子

        //x的左孩子,变p的左孩子
        connect(spl[x].ch[0],p,0);
        root=p;//根变p
        spl[p].fa=0;//根的父亲
        push_up(root);//更新size
    } // 只存在左子树,直接做
    else root=spl[x].ch[0],spl[root].fa=0;
}

//相当于找到这个点
void del(int val,int now=root)
{
    if(val==spl[now].val) delnode(now);
    else if(val<spl[now].val) del(val,spl[now].ch[0]);
    else del(val,spl[now].ch[1]);
}
```
设要删除的点为$x$,先把x伸展到root:`splay(x,0)`,分三种情况考虑

 - $x$的$cnt > 1$
 - $x$的$cnt = 1$
    - $x$存在右子树(可能存在左子树)
      - 找到,右子树中的最小值p
      - p 伸展到 x的孩子
      - x的左孩子,变p的左孩子
    - $x$只存在左子树,直接把左孩子作为根

### getrank 和 atrank

核心思想

 - $getrank$:有多少比自己小
 - $atrank$:不停的缩小rank,去逼近目录位置

```c
//以下与替罪羊树同

//得到值val的rank(排名)
int getrank(int val)
{
    int now=root,rank=1;
    while(now)
    {
        if(val ==spl[now].val){
            rank+=spl[spl[now].ch[0]].size;
            splaying(now,0);
            break;
        } //去左子树
        else if(val<=spl[now].val)
            now=spl[now].ch[0]; 
        else //去右子树
        {
            rank+=spl[spl[now].ch[0]].size+spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return rank;
}

//得到rank(排名)的值
int atrank(int rank)
{
    int now=root;
    while(now)
    {
        int lsize = spl[spl[now].ch[0]].size;
        if( rank >= lsize+1 &&  rank <= lsize+spl[now].cnt){
            splaying(now, 0);
            break;
        }
        else if(lsize>=rank) // 在左边
            now=spl[now].ch[0];
        else // 在右边
        {
            rank-= lsize+ spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return spl[now].val;
}
```

图片演示

```viz-dot
<%- include("dot/rank_example.dot") %>
```

尝试

 - 找到值为5的rank
 - 找到值为6的rank
 - 找到值为0的rank
 - 找到值为100的rank
 - 找到rank为6的值
 - 找到rank为8的值
 - 找到rank为3的值
 - 找到rank为100的值


### pre 和 nxt 前驱/后驱


pre
```c
int pre = getnum( getrank(x)-1);
```

nxt
```c
int nxt = getnum( getrank(x+1));
```

## 样例题目

- [luogu P3369 【模板】普通平衡树](https://www.luogu.org/problem/P3369)

**代码**

::: fold
```c
<%- include("code/3369.cpp") %>
```
:::


## 练习题目

 - [luogu P3391 【模板】文艺平衡树（Splay）](https://www.luogu.org/problemnew/show/P3391)
 - 序列终结者,bzoj 1251,luogu P4146
 - 郁闷的出纳员,SlimeOJ,loj,luogu,根据标题查找
 - 湖南省选:宠物饲养所, SlimeOJ 1566,BZOJ 1208,luogu P2286,loj 10144

## 参考/引用

 - [【AgOHの数据结构】平衡树专题之肆 Splay(伸展树)](https://www.bilibili.com/video/av61868482)
 - [OI-wiki Splay](https://oi-wiki.org/ds/splay)
 - [Splay树及其应用--朱全民](https://wenku.baidu.com/view/c3b4e02f5a8102d276a22feb.html)
 - [splay详解（一） by 自为风月马前卒](https://www.cnblogs.com/zwfymqz/p/7896036.html)
 - [More Senior Data Structure · 特别浅地浅谈Splay by _pks 'w'](https://pks-loving.blog.luogu.org/more-senior-data-structure-te-bie-qian-di-qian-tan-splay)
 - [伸展树的基本操作与应用 IOI2004 国家集训队论文 杨思雨](https://wenku.baidu.com/view/7f0ff024ccbff121dd3683ac.html)
