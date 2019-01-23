# C++操作符重载

这里是对C++操作符重载的简单的讲解,基于我们学习竞赛的原因,我们不需要完全学习所有的语言细节,我们只要掌握以下内容即可.

我们在竞赛的过程中,只要学会很少的重载知识就行(`+,-,>,<,==`).

## 什么操作符重载

想一想我们定义的一个`struct _m {int a;int b;}`,但是有些时候我们需要让两个`_m x;`和`_m y;`按某种规则比较大小,应该如何做呢?

**方法一:**我们自己写一个函数来实现

```c
bool max(_m &x,_m&y) {
    return x.a < y.a;
}
```
**方法二:** 在`struct`内部重载比较操作符

```c
#include <iostream>
using namespace std;

struct _m {
    //初始化
    _m(){}
    _m(int x,int y):a(x),b(y){}

    int a,b;
    bool operator< (const _m &y){
        return a < y.a;
    }
};

int main(){
    _m m1(1,2);
    _m m2(2,3);
    cout << "m1 < m2 :" << (m1 <m2) << endl;
    cout << "m2 < m1 :" << (m2 <m1) << endl;
    cout << "m2 < m1 :" << m2.operator<(m1) << endl;//这种
    return 0;
}
```

**注[1]:**重载只用一个参数的的原因,相当于`<`变成和`.`一想的性质:成为类的成员.想一想你可以直接使用`m1.a`,当然可以直接使用`m1<`.

作为类的成员函数的时候:

**(1).**重载一元操作符,没有显示的形参,非成员函数的时候,有一个形参.二元操作符类似

看上面的写法,我们明显可以发现使用重载,我们可以不用写多个的比较函数

##  全局重载

**一个例子:**
```c
#include <iostream>
using namespace std;
struct _m {
    //初始化
    _m(){}
    _m(int x,int y):a(x),b(y){}
    int a,b;
};

int operator+(const int &a,const _m &b){
    return a+b.a;
}

int operator+(const _m &a,const _m &b){
    return a.a+b.a;
}

int main(){
    _m m1(1,2);
    _m m2(2,3);

    int x= 1;
    cout << "x+m2:" << (x+m2) << endl;
    // 下面这样写错误
    //cout << "m2+x:" << (m2+x) << endl;
    cout << "m1+m2:" << (m1+m2) << endl;
    cout << "m1+m2:" << operator+(m1,m2) << endl;
    return 0;
}
```



不能重载默认的操作符行为,如下:

```c
int operator+(const int &a,const int &b){
    return a+b+1;
}
```
如果你这样重载,C++在计算`a=1,b=1;c=a+b;`的时候,就会混乱.

记住:

**(1).**重载的操作符参数中至少有一个类类型(只可以重载操作符没有的行为)

**(2).**不能为任何内置类型定义额外的新的操作符.例如,不能给两个数组类型重载操作符`operator +`

## 问题

### 问题1:

给结构体`struct _m{int x,y}`加入`+=`的能力,x,y的值都增加一个固定的数.

### 问题2:

给结构体`struct _m{int x,y}`加入`+=`的能力,x,y的值分别加两个不同的数.

### 问题3:

给结构体`struct _m{int x,y}`加入`==`的能力.
