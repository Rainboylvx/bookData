---
title: fhq-treap
date: 2019-11-07 10:28
update: 2019-11-07 10:28
author: Rainboy
---

@[toc]

## 简介

发明人:范浩强

FHQ Treap 同时也借用了 Treap 的特点,每一个节点拥有两个权值,一个是二叉树权值 tree,另一个是 heap。其次,它基于两个操作,一个是分裂 Split,另一个是 Merge。

平衡树好烦啊，转来转去的，而且treap遇到区间序列问题就gg。

有一种不用旋转的treap，叫fhq treap，可以解决区间序列问题.

不靠旋转保持平衡的平衡树,那如何平衡? 通过**随机化**保持平衡.

核心的操作: **1.分裂**,**2.合并**,深刻的理解这两个操作就可以学会本算法.如何理解呢?多找几个图进行练习.


## 基本思想: 平衡


Treap的思想就是，在每一次插入的时候，都会给每个点一个随机的key值，然后让整棵树在满足原本存储的值(val)成一棵二叉查找树外，而外的key值能成为一个堆(大根堆或小根堆)，比如上面那个栗子，如果加入了随机的key值，就可能变成下面这样：

$$treap = tree + heap$$

## 存储

结点信息
 - 左右子树编号
 - 值
 - 索引
 - 子树大小


## 分裂 Split

分裂有两种，一种是权值分裂，一种是排名分裂。我们先讲权值分裂

把树拆成两棵树,拆出来的一棵树的值全部小于等于给点的值,另外一部分的值全部大于给定的值.

把树拆成两棵树,拆出来的一棵树的值全部小于给点的大小,另外一部分的值全部大于等于给定的大小.

一般使用**按值分裂**,而在维护区间信息的时候,使用**按大小分裂**


### 核心思想

分裂(split),按值val分裂成两棵树,x树,y树;其中x树中的所有值都小于等于val,y树中的值都大意val

root为当前dfs树中子树的根

 - 如果root点的val$\leq$给定值,则root和其左子树上的点都$leq$给定值,那么它们应该属于$x$树
   - 对root的右子树进行分裂(split)
   - 分裂后的$x$树为原x树的右子树
   - 分裂后的$y$树为原y树的左子树
 - 如果root点的val$>$给定值,则root和其右子树上的点都$>$给定值,那么它们应该属于$Y$树
   - 对root的左子树进行分裂(split)
   - 分裂后的$x$树为原x树的右子树
   - 分裂后的$y$树为原y树的左子树

### 动画演示

过程:见动画:[fhq-treap 分裂动画](http://rainboy.coding.me/Data-Structure-Animation/#/fhq-treap-split)


### 代码模板

```c
void split(int now,int val,int &x,int &y){
    if( !now ) {
        x = y = 0;
        return;
    }

    if( fhq[now].val <= val){
        x= now;
        split(fhq[now].r, val, fhq[now].r, y);
    }
    else { // >
        y = now;
        split(fhq[now].l, val, x, fhq[now].l);
    }
    update(now);
}
```

## 合并 merge

### 核心思想

 - $x$树全部$ \leq val$, $y$树全部$ \geq val$
 - 如何简单合并,$x$树全部作为$y$的最小结点的左子树,或者$y$树作为$x$树最大结点的右子树
 - **但是要让合并的时候尽量达到平衡** :合并的时候基于$key$,保证树为$heap$


基于x,y树的rootX,rootY的key比较大小,如何是大根堆的话

- 如果rootX的key $ > $ rootY的key
  - rootX的右子树,和Y树,进行合并成一个树,并作为rootX的右孩子
- 否则,rootX的key $ \leq $ rootY的key
  - rootY的左子树,和X树,进行合并成一个树,并作为rootY的左孩子

这明显是一个**递归**的过程,边界是当其中的一棵树为**空树**时


### 动画演示

过程:见动画:[fhq-treap 分裂动画](http://rainboy.coding.me/Data-Structure-Animation/#/fhq-treap-merge)


### 代码模板

```c
/* 合并x,y树,返回树的根 */
int merge(int x,int y){
    if( !x || !y) return x+y;
    if( fhq[x].key > fhq[y].key){
        fhq[x].r = merge(fhq[x].r, y);
        update(x);
        return x;
    }
    else {
        fhq[y].l  = merge(x, fhq[y].l);
        update(y);
        return y;
    }
}
```

## 其他操作

### 插入

需要插入一个值val

 - 把树按val分裂成,x树,y树
 - 创建只有一个结点,值为val的树z
 - 合并x,z,为x树
 - 合并x,y树


```c
inline void ins(int val)
{
    split(root,val,x,y);
    root=merge(merge(x,newnode(val)),y);
}
```

### 删除


需要删除一个值val的一个点

 - 把树按val分裂成,x树,y树
 - 把x树按val-1分裂成,$x_1$树,$y_1$树
    - $y_1$树的根的值一定为$val$
    - 合并$y_1$的左右子树为新的$y_1$树,相当与删除$y_1$的根结点
    - 合并$x_1$,新$y_1$为新$x$树
    - 新$x$树与$y$树

```c
inline void del(int val)
{
    int x,y,x1,y1;
    split(root,val,x,y);
    split(x,val-1,x1,y1);
    y1=merge(fhq[y1].l,fhq[y1].r);
    root=merge(merge(x1,y1),y);
}
```

### 得到值的排名

 - 把树按$val-1$分裂成,x树,y树
 - 排名为x树的大小$+1$
 - 合并x树,y树

```c
inline void getrank(int val)
{
    split(root,val-1,x,y);
    print(fhq[x].size+1);
    root=merge(x,y);
}
```

### 得到排名的对应的值

和普通的平衡树一样

```c
inline void getnum(int rank)
{
    int now=root;
    while(now)
    {
        if(fhq[fhq[now].l].size+1==rank)
            break;
        else if(fhq[fhq[now].l].size>=rank)
            now=fhq[now].l;
        else 
        {
            rank-=fhq[fhq[now].l].size+1;
            now=fhq[now].r;
        }
    }
    print(fhq[now].val);
}
```

### 前驱

 - 把树按$val-1$分裂成,x树,y树
 - 找到x树的最大的点,就是所求
 - 合并x树,y树

```c
inline void pre(int val)
{
    split(root,val-1,x,y);
    int now = x;
    while(fhq[now].r)
        now = fhq[now].r;
    print(fhq[now].val);
    root=merge(x,y);
}
```

### 后驱

 - 把树按$val$分裂成,x树,y树
 - 在y树中找到最小的点,就是所求
 - 合并x树,y树

```c
inline void nxt(int val)
{
    split(root,val,x,y);
    int now = y;
    while(fhq[now].l)
        now = fhq[now].l;
    print(fhq[now].val);
    root=merge(x,y);
}
```


## 模板题目

**地址**[P3369 【模板】普通平衡树](https://www.luogu.org/problem/P3369)

**代码**
<!-- template start -->
todo
<!-- template end -->





## 参考

- [【算法讲堂】【电子科技大学】【ACM】无旋Treap及树套树入门](https://www.bilibili.com/video/av46204315)
