# 拓展欧基里得算法

## 贝祖定理

有二元一次方程如下:

```math
ax+by = gcd(a,b)
```
其中$$a,b$$是整数,那么存在整数解$$x,y$$,使方程成立.这个公式我们称为**标准贝祖等式**


同样的,我们也可以推出如下:

```math
ax+by = k*gcd(a,b)
```
其中k为整数,当标准贝祖等式有整数解的时候,这个公式也一定有解,设标准贝祖等式的一组解为:$$(x_0,y_0)$$,那么这个公式的对应的一组解为:$$(k*x_0,k*y_0)$$

**更一般的定义:**

二元一次方程:$$ax+by=c$$存在整数解的充分必要条件:$$ c \bmod (gcd(a,b)) == 0$$



## 拓展欧几里得算法

求解问题：在求解两数的最大公约数同时，可以求得二元一次不定方程$$ax+by=gcd(a,b)$$的一组解


### 算法原理

**原理1:**我们知道在求$$gcd(a,b)$$的过程中:$$gcd(a,b) = gcd(b ,a \%b)=......=gcd(m,0)$$

那么在边界的时候,显示有:

```math
m*x+0*y= gcd(a,b) =gcd(m,0) =m
```

根据**标准贝祖等式**这个方程是有整数解,显示其中的一组解为

```math
\left\{\begin{matrix} x=1 \\  y=0\end{matrix}\right.
```

**原理2:**根据贝祖等式,$$gcd(a,b),gcd(b,a \% b)$$可以形成下面的公式
```math
\left\{\begin{matrix}
now&:&ax+by = gcd(a,b) \\
nxt&:&bx_0+(a \%b)y_0 = gcd(b,a\%b)
\end{matrix}\right.
```

它们都是有整数的解的,那它们解之间有什么关系呢?

因为$$gcd(a,b),gcd(b,a \% b)$$,所以如下:

```math
\begin{matrix}
ax+by &=& bx_0+(a \%b)y_0 \\
\Longrightarrow &=& bx_0 +(a-(a/b) \times b)y_0 \\
\Longrightarrow &=& ay_0+b(x_0-(a/b)\times y_0) \\
ax+by &=&  ay_0+b(x_0-(a/b)\times y_0)  \\
\end{matrix}
```

所以我们可以得到相邻的两层的gcd形成的二元一次方程组的解的关系如下:

```math
\left\{\begin{matrix}
x&=&y_0  \\ 
y&=&x_0-(a/b)\times y_0
\end{matrix}\right.
```

其中$$a/b$$表示整除

### 代码


```c
int exgcd(int a,int b,int &x,int &y){//ax+by=gcd(a,b)
    if(b==0){x=1,y=0;return a;}
    int gcd=exgcd(b,a%b,x,y);
    int _x=x;
    x=y;
    y=_x-(a/b)*y;
/*
    int gcd=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
*/
    return gcd;
}
```

## 应用1 求贝祖等式的一组解

对于一般性的贝祖等式$$ax+by=c$$，如果$$c \bmod gcd(a,b) == 0$$，那么表明：对于给定的$$a,b,c$$不存在整数解。否则，对于解出的某一组特解$$x,y$$（标准贝祖等式下），其真正解出的特解应为$$x=x_0 \times \frac{c}{gcd(a,b)}$$。


## 应用2 求通解

已知一个标准贝祖等式:$$ax+by=gcd(a,b)$$的一组解,如果求其它的解?如果等式有解,那就无数组解

```math
\begin{matrix}
ax+by=gcd(a,b) \\
\Longrightarrow \frac{a}{gcd(a,b)}x + \frac{b}{gcd(a,b)}y = 1 \\
\end{matrix}
```

我们构造出下面的公式:

```math
 \frac{a}{gcd(a,b)}(x+\frac{b}{gcd(a,b)} \times t) + \frac{b}{gcd(a,b)}(y-\frac{a}{gcd(a,b)} \times t) = 1 ,t \in Z
```

于是我们得到:

```math
\left\{\begin{matrix}
x&=&x_0+\frac{b}{gcd(a,b)} \times t \\ 
y&=&y_0+\frac{a}{gcd(a,b)} \times t
\end{matrix}\right.
```
其中$$t \in Z$$,如是我们可以说只要有一组解,就可以得到无限的解

### 应用3 得到最小正整数解

当我们得到的一个解x是正数里,因为$$x=x_0 +m\times t$$,所以最小正整数解为$$x_0= x \bmod m$$,注意$$m$$取绝对值

如果$$x$$是负数,那我们用

```c
int a = (x % abs(m) ) + abs(m)
```
## GCD 表示最大公数

假如我们用GCD的方法来求a =32 b = 12 的最大公约数,那么过程如下：

| a  | b          |
|----|------------|
| 32 | 12         |
| 12 | 32 %12 = 8 |
| 8  | 12 % 8 = 4 |
| 4  | 8 % 4=0    |

最后得到GCD(32,12) = 4

### 拓展欧几里得定理：

如果公式： $$a*x + b*y  = gcd(a,b)$$ 那么一定有解，且有无数解

### 证明

方程1:$$32*x + 12*y = 4$$ 其中$$x_1,y_1$$为一组解

方程2:$$12*x + 8 *y = 4$$ 其中$$x_0,y_0$$为一组解

那么$$x_0,y_0,x_1,y_1$$有什么关系呢？


可以知道

```math
8= 32 - 32/12*12 = 32-2*12
```

代入 $$12*x_0 +(32-2*12)y_0=4$$

化简得到:

```math
32*y_0 + 12(x_0-2*y_0)=4
```

对照:

$$32*x_1 -12*y_1 =4$$

**得到重要的关系式**=>


```math
\left\{\begin{matrix}
 x_1=&y_0 \\
y_1=&x_0-2*y_0
\end{matrix}\right.
```


其中$$ 2= 32 /12$$

如果$$a=32,b=12$$也可以这样认为  ==>

```math
\left\{\begin{matrix}
x_1=y_0 \\
y_1=x_0-a/b*y_0
\end{matrix}\right.
```


我们又知道：

```math
gcd(32,12) = gcd(12,8) = gcd(8,4) = gcd(4,0)
```

所有我们一定可以通过$$ 4x+0*y =4$$ 的一组解 返推出 $$32*x+12*y =4$$ 的一组,那我们取$$4*x+0*y = 4$$,

```math
\left\{\begin{matrix}
x=1 \\
y=0
\end{matrix}\right.
```

这一组解

### 验证

**公式1:**

$$4x+0*y =4$$

 的一组解为:

```math
\left\{\begin{matrix}
 x_0=&1 \\
y_0=&0
\end{matrix}\right.
```

-------------

**公式2:**

$$8x+4y =4$$
 的一组解为$$x_1,y_1$$,那么

```math
\left\{\begin{matrix}
 x_1=&y_0&=&0 \\
y_1=&x_0-8/4*y_0&=&1
\end{matrix}\right.
```

带入公式2验证,确实正确.

-----------------

**公式3:**

同理:
$$12x+8y =4$$
的一组解$$x_2,y_2$$,那么

```math
\left\{\begin{matrix}
 x_2=&y_1&=&1 \\
y_2=&x_1-12/8*y_1&=&-1
\end{matrix}\right.
```

带入公式3验证,确实正确.

------------

**公式4:**

同理:
$$32x+12y =4$$
的一组解$$x_3,y_3$$,那么

```math
\left\{\begin{matrix}
 x_3=&y_2&=&-1 \\
y_3=&x_2-32/12*y_2&=&3
\end{matrix}\right.
```

带入公式4验证,确实正确.

## 结论

知道了$$ 32*x+12*y =4$$ 的一个解$$x_0,y_0$$，其它解：

$$  x= x_0+(b/gcd(a,b))*t$$

$$  y= y_0-(a/gcd(a,b))*t$$

因为:

$$a*x_0 + a*b/gcd*t +b*y_0 -a*b/gcd*t =gcd$$

$$a(x_0+b/gcd*t) + b(y_0-a/gcd*t) = gcd$$


可以看到如果有一个解,就有无数的解

### exgcd代码模板

```cpp
int ex_gcd(int a,int b,int c,int &x,int &y){
    if(b == 0){
        x=c/a;
        y=0;
        return a;
    }
    int ans = ex_gcd(b,a%b,c2,x,y);
    int tmp =x;
    x = y;
    y = tmp -a/b*y;
    return ans;
}
```

## cojs上的代码

```c
#include <iostream>
using namespace std;

//扩展欧几里德算法
int ExGCD(int a, int b, int& x, int& y)
{
if(b == 0)
{
x = 1, y = 0;
return a;
}
int d = ExGCD(b, a%b, x, y);
int temp = x;
x = y;
y = temp - a/b*y;
return d;
}

int main()
{
int x, y, d;
d = ExGCD(99, 78, x, y);
cout << d << " " << x << " " << y << endl;
return 0;
}

//定理一: 如果a,b是不都为0的任意整数,则d=gcd(a,b)是a,b的线性组合{ax+by: x,y∈Z}的最小元素.
// 已知d=gcd(a,b)=gcd(b,a mod b)
//
//由gcd(b,a mod b)得知,d = bx + a mod b = bx + (a-floor(a/b)*b)*y = a*y + b(x-floor(a/b)*y)
//当推到gcd(a,b)时,d′ = d = a*y + b(x-floor(a/b)*y)

//其他比较重要定理:
//定理二:d|a, d|b => d|(ax+by)  注:d|a表示a mod b == 0,即a能被b整除
//定理一推论: 对任意整数a,b如果d|a,d|b,则d|gcd(a,b)

//附:
int GCD(int a, int b)
{
  　　if(b == 0)
　　return a;
　　return GCD(b, a % b);
}
//迭代形式:
int GCD(int a, int b)
{
while(b != 0)
{
int r = b;
b = a % b;
a = r;
}
return a;
```

## 题目

cogs上

| PID  | 题目名称            |
|------|---------------------|
| 1225 | 倒酒                |
| 1265 | [NOIP2012] 同余方程 |
| 2057 | [ZLXOI2015]殉国     |
| 2547 | 军队                |

经典的裸题SDOI2011 计算器

题目解析 http://hzwer.com/5878.html


第二问求axΞ b(mod n)，转化为ax=ny+b，转化为ax+ny=b，利用拓展欧几里得算法求出ax+ny=gcd(a,n)，如果b不是gcd的倍数则无解否则为x/gcd*b。
