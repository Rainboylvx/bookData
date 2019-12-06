## 前置

1. 动态开点线段树
1. 权值线段树

> 权值线段树能代替平衡树做一些求 k 大、排名、找前驱后继的操作，了解一下就可以啦


合并

```c
int merge(int a,int b,int l,int r){
    if(!a) return b;
    if(!b) return a;
    if( l == r){
        // 按题目意思 合并
        // tr[a].val += tr[b].val
        return a;
    }

    int md = (l+r) >> 1;
    tr[a].l = merge(tr[a].l,tr[b].l,l,mid);
    tr[a].r = merge(tr[a].r,tr[b].r,mid+1,r);
    push_up(a);
    return a;
}
```
时间复杂度证明

你对每个点都开一个线段树后能维护的东西,线段树合并都能合并,因为它们的本质都一样

作用

查询子树内前驱,后继,第k大,x是第几大的权值线段树能干的事

出现最多的数,总和最大的数,

又是cf600E这个题目

## 题目

 - p4556 雨天的尾巴

## 参考/引用

 - [线段树的合并--不为人知的使用技巧 by 黄嘉泰](https://wenku.baidu.com/view/88f4e134e518964bcf847c95.html)
 - [Styx ,线段树合并：从入门到放弃](https://www.luogu.com.cn/blog/styx-ferryman/xian-duan-shu-ge-bing-zong-ru-men-dao-fang-qi?tdsourcetag=s_pcqq_aiomsg)
