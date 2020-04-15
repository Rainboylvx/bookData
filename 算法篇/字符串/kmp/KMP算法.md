---
title: KMP算法
date: 2019-04-03 14:52
update: 2019-04-03 14:52
author: Rainboy
---

# KMP算法

kmp[i]的基本定义是：在第1-第i-1位中前缀与后缀相同的部分最长是多长。这样，即可以理解为，若第i位失配了，则至少要往前跳多少步，才可能重新匹配得上。这样便可以解释前面的例子了。

时间复杂度$O(n+m)$

## 算法演示

 - https://people.ok.ubc.ca/ylucet/DS/KnuthMorrisPratt.html
 - http://whocouldthat.be/visualizing-string-matching/


```viz-dot
digraph title {
    node[shape=rect];
    "1.算法过程" -> "2.next数组的处理";
}
```

## 了解算法过程

我们这里约定:

 - 字符串从下标1开始
 - j表示B字符串的前j个字符和A字符串匹配
 - next[j]表示b字符串第j个位置的前next[j]个字符和从头开始的next[j]个字符相同,不能全部相同(next[j] != j)

::: center
```viz-dot
graph g{
    node[shape=plaintext fillcolor=white colorscheme=accent8 ];
    a[
        label=< <TABLE CELLBORDER="0" BORDER="0" CELLSPACING="3" CELLPADDING="0">
            <tr>
                <td PORT="">A:</td>
                <td PORT="">abcabcabd</td>
            </tr>
            <tr>
                <td PORT="">B:</td>
                <td PORT="">abcabd</td>
            </tr>
        </TABLE> >
    ]
}
```
:::

::: center
```viz-dot
<%- include("dot/next_with_bstring.dot") %>
```
:::

我们先不要在意next数组是如何得到的,如何利用B的next数组和字符串A匹配


<<<< viz-gallery(title="title",engine="dot",height="400")

<% 
var log =[]
var engine = "dot"
for(let i=1;i<=16;i++){
    var page = `dot/kmp_${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<


## next数组的值

我们有一个b数组如下$a,b,a,c,a,b$,如何求b数组的next的值?

显然next[1] = 0,因为第一个元素的左边没有元素了

 - 让$j=0,i=2$
    - j=0,表示b[1]左边匹配长度为0,j+1表示b[1]
    - i=2,表示从第二个位置b[2],开始计算next的值
 - 循环:如果b[i]与b[j+1]不匹配且j!=0,$j=next[j]$,==> `while(j && b[j+1] != b[i]) j = next[j]; `
 - 如果$b[j+1]=b[i]$,$j++$
 - 是next[i] = j

原理:**自我匹配**


<<<< viz-gallery(title="求next数组",engine="dot",height="400")

<% 
var log =[]
var engine = "dot"
for(let i=1;i<=4;i++){
    var page = `dot/next_${i}.dot`
%>

``` <%= engine || ""%> <%= log[i-1] || "" %>
<%- include(page) %>
```
<%}%>

<<<<


## 匹配


当到达某个不匹配的地方的时候,需要重新匹配!kmp的匹配就一种类似递归的思想.只要理解了这种思想,$KMP$算法就简单了.


## 模板

<!-- template start -->
```c
const int kmp_max_len = 1e5;
struct KMP{
    int la,lb;
    char a[kmp_max_len],b[kmp_max_len];
    int next[kmp_max_len];
    int cnt =0; //匹配字符串的数量

    void deal_next(){
        int i,j=0;
        next[1] = 0;
        for(i=2;i<=lb;++i){
            while(j && b[j+1] != b[i])  j = next[j];
            if( b[j+1] == b[i]) j++;
            next[i] = j;
        }
    }
    void kmp(){
        int i,j=0;
        for(i=1;i<=la;++i){
            while(j && b[j+1] != a[i]) j = next[j];
            if( b[j+1] == a[i]) j++;
            if( j == lb){ 
                //printf("%d\n",i-lb+1); 
                cnt++;
                j=next[j];
            }
        }
    }
};
```
<!-- template end -->




## 题目

题目地址: [luogu P3375 【模板】KMP字符串匹配](https://www.luogu.org/problemnew/show/P3375)

### 代码

```c
#include <cstdio>
#include <cstring>
#define maxn 1000005


char a[maxn];
char b[maxn];
int la,lb;
int next[maxn]={0};

void init(){
   scanf("%s",a+1);
   scanf("%s",b+1);
   la = strlen(a+1);
   lb = strlen(b+1);
}

// 自己匹配自己
/* 得到next数组 */
void deal_next(){
    int i,j=0;
    // 从第二个位置开始算,因为next[1] = 0
    for (i=2;i<=lb;i++){
        while(j && b[i] != b[j+1])
            j = next[j];
        if( b[j+1] == b[i]) j++;
        next[i] = j;
    }
}

void kmp(){
    int i,j=0;  //j代表第二个字符串有开头的j个字符和第一个字符串相等
    for (i=1;i<=la;i++){
        
        while(j && b[j+1] != a[i])  //
            j= next[j];             // 代表第二个字符串向右推

        if( b[j+1] == a[i])
            j++;
        if( j == lb){
            printf("%d\n",i-lb+1); //输出匹配的位置
            j = next[j];
        }
    }
}

int main(){
    init();
    deal_next();
    kmp();
    int i;
    for (i=1;i<=lb;i++){
        printf("%d ",next[i]);
    }
    return 0;
}
```

## 练习题目

- loj 10043 「一本通 2.2 例 1」剪花布条 [题解](<%- USER.pcs_site %>loj-10043)
- loj 10044 「一本通 2.2 例 2」Power Strings [题解](<%- USER.pcs_site %>loj-10044)
- loj 10045 「一本通 2.2 练习 1」Radio Transmission [题解](<%- USER.pcs_site %>loj-10045)
- loj 10046 「一本通 2.2 练习 2」OKR-Periods of Words
- loj 10047 「一本通 2.2 练习 3」似乎在梦中见过的样子
- loj 10048 「一本通 2.2 练习 4」Censoring [题解](<%- USER.pcs_site %>loj-10048)


## 参考/引用

 - [Matrix67 KMP算法与一个经典概率问题](http://www.matrix67.com/blog/archives/366)
