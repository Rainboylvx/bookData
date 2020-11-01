---
_id: "b993eba689"
title: random
date: 2020-10-17 08:51
update: 2020-10-17 08:51
author: Rainboy
---

## 说明

mt19937是c++11中加入的新特性

它是一种随机数算法，用法与rand()函数类似

但是具有速度快，周期长的特点(它的名字便来自周期长度：2^19937-1)

说的直白一点，我们都知道rand()在windows下生成的数据范围为0-32767

但是这个函数的随机范围大概在$(-maxint,+maxint)$(maxint为int类型最大值)

mt19937 还有一个很重要的优势，相对`rand()`来说他具有更高的随机种子精度，如果`rand()`使用`srand(time(0))`生成随机种子,那么1s内运行这个程序多次，生成的随机数据是一样的，这就给我们将会的对拍程序带来了麻烦。

有关随机数的模板，看这一节[算法篇/其它算法/随机数](/article/8c9bfaaf33)

## 使用

简单的生成随机数
```c
#include<random>

std::random_device rd;  //获取随机数种子
std::mt19937 rnd(rd());

//std::mt19937 rnd(time(0));

int main()
{
    printf("%d\n",rnd());
    return 0;
}
```

生成一定范围内的随机数
```c
#include <random>
#include <iostream>
 
int main()
{
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 rnd(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<int> dis(1, 6);
 
    for (int n=0; n<10; ++n)
        // 用 dis 变换 rnd 所生成的随机 unsigned int 到 [1, 6] 中的 int
        std::cout << dis(rnd) << ' ';
    std::cout << '\n';
}
```

## 参考:
- [标准库头文件 `<random>` - cppreference.com](https://zh.cppreference.com/w/cpp/header/random)
- [cppreference std::mersenne_twister_engine](https://zh.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)
- [mt19937是什么鬼？](https://blog.csdn.net/caimouse/article/details/55668071)
- [深海中的STL—mt19937](https://www.cnblogs.com/zwfymqz/archive/2018/03/01/8489116.html)
