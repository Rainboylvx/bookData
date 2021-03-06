---
_id: "2e880abd3a"
title: EXGCD与解不定方程
date: 2020-01-03 11:15
update: 2020-01-03 11:15
author: Rainboy
cover: 
---

@[toc]
## 贝祖定理

有二元一次方程如下:

$$
ax+by = gcd(a,b)
$$

其中$a,b$是整数,那么存在整数解$x,y$,使方程成立.这个公式我们称为**标准贝祖等式**


同样的,我们也可以推出如下:

$$
ax+by = k*gcd(a,b)
$$

其中k为整数,当标准贝祖等式有整数解的时候,这个公式也一定有解,设标准贝祖等式的一组解为:$(x_0,y_0)$,那么这个公式的对应的一组解为:$(k \cdot x_0,k \cdot y_0)$

**更一般的定义:**

二元一次方程:$ax+by=c$存在整数解的充分必要条件:$c \bmod (gcd(a,b)) == 0$, 即$gcd(a,b) | c$



## 拓展欧几里得算法详解

求解问题：在求解两数的最大公约数同时，可以求得二元一次不定方程$ax+by=gcd(a,b)$的一组解


### 算法原理

**原理1:**我们知道在求$gcd(a,b)$的过程中:$gcd(a,b) = gcd(b ,a \%b)=......=gcd(m,0)$

那么在边界的时候,显示有:

$$
m*x+0*y= gcd(a,b) =gcd(m,0) =m
$$

根据**标准贝祖等式**这个方程是有整数解,显示其中的一组解为

$$
\left\{\begin{matrix} x=1 \\  y=0\end{matrix}\right.
$$

**原理2:**根据贝祖等式,$gcd(a,b),gcd(b,a \% b)$可以形成下面的公式

$$
\left\{\begin{matrix}
now&:&ax+by = gcd(a,b) \\
nxt&:&bx_0+(a \%b)y_0 = gcd(b,a\%b)
\end{matrix}\right.
$$

它们都是有整数的解的,那它们解之间有什么关系呢?

因为$gcd(a,b),gcd(b,a \% b)$,所以如下:

$$
\begin{matrix}
ax+by &=& bx_0+(a \%b)y_0 \\
\Longrightarrow &=& bx_0 +(a-(a/b) \times b)y_0 \\
\Longrightarrow &=& ay_0+b(x_0-(a/b)\times y_0) \\
ax+by &=&  ay_0+b(x_0-(a/b)\times y_0)  \\
\end{matrix}
$$

所以我们可以得到相邻的两层的gcd形成的二元一次方程组的解的关系如下:

$$
\left\{\begin{matrix}
x&=&y_0  \\ 
y&=&x_0-(a/b)\times y_0
\end{matrix}\right.
$$

其中$a/b$表示整除

### 样例

如果我们要求$32 \cdot x + 12 \cdot y = 4$的一组解,解的过程如下:
![1](./exgcd.png)

### 模板代码

<!-- template start -->
```c
int exgcd(int a,int b,int &x,int &y){//ax+by=gcd(a,b)
    if(b==0){x=1,y=0;return a;}
    int gcd=exgcd(b,a%b,x,y);
    int tx=x;
    x=y;
    y=tx-(a/b)*y;
    return gcd;
}
```
<!-- template end -->

### 应用1 求贝祖等式的一组解

对于一般性的贝祖等式$ax+by=c$，如果$c \bmod gcd(a,b) != 0$，那么表明：对于给定的$a,b,c$不存在整数解。否则，对于解出的某一组特解$x,y$（标准贝祖等式下），其真正解出的特解应为$x=x_0 \times \frac{c}{gcd(a,b)}$。


### 应用2 求通解

已知一个标准贝祖等式:$ax+by=gcd(a,b)$的一组解,如果求其它的解?如果等式有解,那就无数组解

$$
\begin{matrix}
ax+by=gcd(a,b) \\
\Longrightarrow \frac{a}{gcd(a,b)}x + \frac{b}{gcd(a,b)}y = 1 \\
\end{matrix}
$$

我们构造出下面的公式:

$$
\frac{a}{gcd(a,b)}(x+\frac{b}{gcd(a,b)} \times t) + \frac{b}{gcd(a,b)}(y-\frac{a}{gcd(a,b)} \times t) = 1 ,t \in Z
$$

于是我们得到:

$$
\left\{\begin{matrix}
x&=&x_0+\frac{b}{gcd(a,b)} \times t \\ 
y&=&y_0+\frac{a}{gcd(a,b)} \times t
\end{matrix}\right.
$$

其中$t \in Z$,如是我们可以说只要有一组解,就可以得到无限的解

### 应用3 得到最小正整数解

当我们得到的一个解x是正数解,因为$x=x_0 +m\times t$,所以最小正整数解为$x_0= x \bmod m$,注意$m$取绝对值

如果$x$是负数,那我们用

```c
int a = (x % abs(m) ) + abs(m)
```

无论x是正还是负数,都可以用下面的算式求出,最小正整数解

```c
m = abs(m)
int a = ((x % m ) + m ) % m;
```

## 总结

<!-- template start -->
二元一次方程:$a \cdot x + b \cdot y = c$有整数解的充分必要条件是$gcd(a,b) \mid c$,根据exgcd先求出方程$a \cdot x + b \cdot y = gcd(a,b)$的一组解$\left \{x_0,y_0\right \}$,进而得到原方程的一组解$\left \{k \cdot x_0,k \cdot y_0\right \},k = c \div gcd(a,b)$,令$m = b \div gcd(a,b)$

 - 当前层的解与下一层解的关系：$x = y_0,y = x_0-\lfloor  \frac{a}{b} \rfloor \cdot y_0$
 - 通解:$k \cdot (x_0 + m \cdot t), t \in Z$
 - 最小正整数解:$k \cdot(( x_0 \% m +m) \% m)$

<!-- template end -->


## 练习题目



- [luogu P1082 同余方程](<%- USER.pcs_site %>luogu-P1082)
- [luogu P1516  青蛙的约会](<%- USER.pcs_site %>luogu-P1516)

| PID              | 题目名称        |
|------------------|-----------------|
| luogu P1292 倒酒 | 倒酒            |
| cogs 2057        | [ZLXOI2015]殉国 |
| cogs 2547        | 军队            |

经典的裸题SDOI2011 计算器,综合了快速幂取余,exgcd,bsgs

题目解析 http://hzwer.com/5878.html


