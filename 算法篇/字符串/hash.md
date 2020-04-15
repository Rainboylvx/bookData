---
_id: 526d3ce7c6
title: 字符串hash
date: 2019-11-23 09:49
update: 2019-11-23 09:49
author: Rainboy
---

# 字符串hash

假设字符串为$C_1=c_1c_2c_3c_4c_4 \cdots c_m$,选取两个合适的互质常数$b,h\ (b \lt h)$,我们定义哈希函数为:

$$
H(C) = (c_1 \cdot b ^{m-1}+ c_2 \cdot b ^{m-2}+ c_3 \cdot b ^{m-3}+ c_4 \cdot b ^{m-4}+ \cdots
c_m \cdot b ^{0}) \mod h
$$

这里相当于把字符串看成$b$进制数

设$H(C,k)$表示前$k$字符构成的字符串哈希值,则(以下均不考虑取模):

$$
H(C,k+1) = H(C,k) \times b  + c_{k+1}
$$

若$C'= c_{k+1} c_{k+2} \cdots c_{k+n} $,则:

$$
H(C') = H(C,k+n)-H(c,k) \times b^n
$$

我们只要预先求得$b^n$,就能在$O(1)$时间内得到任意字符串的子串哈希值,从而完成字符串匹配.

在算法实现时,可以利用32位或64位无符号整数计算哈希值,并取$h=2^{32}$或$h=2^{64}$,通过自然溢出省去求模运算.

## 模板


```viz-dot
digraph g {
    node[shape=plaintext colorscheme=accent8];
    nodesep=1;

    string[
    label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="2" CELLPADDING="3">
        <tr>
            <td PORT="" bgcolor="1">string</td> <td PORT="" bgcolor="1">hash</td>
            <td bgcolor="1">mod</td>
        </tr>
        <tr>
            <td PORT="" >abc</td> <td PORT="">1234</td>
            <td>34</td>
        </tr>
        <tr>
            <td PORT="">ab</td> <td PORT="">12</td>
            <td>12</td>
        </tr>
        <tr>
            <td PORT="">abcd</td> <td PORT="">2234</td>
            <td>34</td>
        </tr>
        <tr>
            <td PORT="">ab</td> <td PORT="">12</td>
            <td>12</td>
        </tr>
    </TABLE> >
    ]

    a[
    label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="5">
        <tr>
            <td PORT="0" bgcolor="1">hashmap</td>
        </tr>
        <tr>
            <td PORT="1">1234</td>
        </tr>
        <tr>
             <td PORT="2">12</td>
        </tr>
        <tr>
             <td PORT="3">2234</td>
        </tr>
    </TABLE> >
    ]
    //a:3:e->a:1:e;

    next[
    label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="5">
        <tr>
            <td PORT="0" bgcolor="1">next</td>
        </tr>
        <tr>
            <td PORT="1">3</td>
        </tr>
        <tr>
             <td PORT="2">-1</td>
        </tr>
        <tr>
             <td PORT="3">-1</td>
        </tr>
    </TABLE> >
    ]

    head[
    label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="5">
        <tr>
            <td PORT="0" bgcolor="1">head</td>
        </tr>
        <tr>
             <td PORT="2">12</td>
        </tr>
        <tr>
            <td PORT="3">34</td>
        </tr>
    </TABLE> >
    ]
    edge[constraint=false]
    head:2->next:2;

    head:3->next:1;
    next:1:w->next:3:w[minlen=2];
}
```


## 参考/引用

 - 信息学奥赛一本通-提高篇-第二部分-第一章:哈希与哈希表



