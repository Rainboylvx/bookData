---
_id: "73df3dbd5a"
title: index
date: 2020-11-25 15:51
update: 2020-11-25 15:51
author: Rainboy
titleEmojiTag: ":tv:"
---

## 问题的引入


计算$a \times b % mod$的结果，$a \times b$ 有可能直接超过`long long`的范围，导致数据溢出。


乘法在计算机中处理的时间并不是这么快的，也要拆分为加法来做的。所以快速乘法会更快的计算a*b的结果。

实现的原理都是基于按照二进制位一步一步乘来避免重复的操作，利用前面的中间结果，从而实现快速的目的。

设b的二进制表示为$(b1+b2+b3+b4+...+bn)$

$$
a \times b = a \times (b1+b2+b3+b4+...+bn)
$$

## 代码模板

<!-- template start -->
```c
using ll = long long;
ll multiply(ll a,ll b,ll p){
    ll ret = 0;
    for( ; b ; b >> 1){
        if( b & 1) ret = ( ret+x) %p;
        x = ( x+ x) %p;
    }
    return ret;
}
```
<!-- template end -->

## 练习题目

## 参考

- [快速乘法/幂 算法详解](https://blog.csdn.net/maxichu/article/details/45459715)
