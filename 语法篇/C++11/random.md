## 说明

mt19937是c++11中加入的新特性

它是一种随机数算法，用法与rand()函数类似

但是具有速度快，周期长的特点(它的名字便来自周期长度：2^19937-1)

说的直白一点，我们都知道rand()在windows下生成的数据范围为0-32767

但是这个函数的随机范围大概在\((-maxint,+maxint)\)(maxint为int类型最大值)


## 使用

```c
#include<random>

std::random_device rd;  //获取随机数种子
std::mt19937 rnd(rd());

//std::mt19937 rnd(time(0));

int main()
{
    printf("%lld\n",rnd());
    return 0;
}

```
## 参考:

 - [cppreference std::mersenne_twister_engine](https://zh.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)
 - [mt19937是什么鬼？](https://blog.csdn.net/caimouse/article/details/55668071)
 - [深海中的STL—mt19937](https://www.cnblogs.com/zwfymqz/archive/2018/03/01/8489116.html)
