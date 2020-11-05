---
_id: "dfd75bfcfb"
title: C++排序函数Sort
date: 2020-11-03 22:17
update: 2020-11-03 22:17
author: Rainboy
video: "https://www.bilibili.com/video/BV1JA411j7ex/"
titleEmojiTag: ":tv:"
---

@[toc]

# C++排序函数 sort


## 基础使用

下面的我们来使用C++本身给我们提供的排序函数`sort`,它的复杂度为：平均 $O(N \cdot log(N))$。

使用方法如下：
```c
sort(a+m,a+n);      //[a+m,a+n) 范围内的元素进行排序
sort(a+m,a+n,cmp);  //cmp 是函数 或仿函数
```

详细的使用方法请看：[std::sort - cppreference.com](https://zh.cppreference.com/w/cpp/algorithm/sort)

样例代码

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100] = {5,1,8,4,2,5,7,4,9,10};
int main(){
    int i;
    sort(a+0,a+10); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```


如果我们想让从大到小排序怎么办?

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100] = {5,1,8,4,2,5,7,4,9,10};

/* 原理是为真的时候,第一个数字放前面 */
bool mycmp(int &a,int &b){ 
    if(a > b)
        return 1;
    return 0;
}

int main(){
    int i;

    sort(a+0,a+10,mycmp); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```

**重点: 原理是为真的时候,mycmp函数的第一个参数放前面**

## 使用仿函数

`sort`的第三个参数不仅可以传递函数的名字，还可以传递仿函数对象


```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100] = {5,1,8,4,2,5,7,4,9,10};

struct Big {
    bool operator()(int a,int b){
        return a > b;
    }
};
int main(){
    int i;

    sort(a+0,a+10,Big ()); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```

c++ 内置了两个比较大小的仿函数[less](https://zh.cppreference.com/w/cpp/utility/functional/less)，[greater](https://zh.cppreference.com/w/cpp/utility/functional/greater) 分别进行大小的比较。

例如，我们可以直接用`greater`来实现从大到小排序，不用自己写仿函数了。

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100] = {5,1,8,4,2,5,7,4,9,10};

int main(){
    int i;

    sort(a+0,a+10,greater<int> ()); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```

## 对结构体进行排序

结构体一能直接比较大小，综合上面的所学，可以用下面的方式来实现大小比较

 1. 大小比较函数
 2. 重载`<`号
 3. 仿函数

 这里我们用重载`<`号，来实现排序

```c
#include <cstdio>
#include <algorithm>
using namespace std;

struct node {
    int a,b;
    // 重载<
    bool operator<(node B){
        if( a !=  B.a ) return a < B.a;
        return b < B.b;
    }
};
node a[10] = {
    {2 ,3 },
    {10,10},
    {5 ,5 },
    {4 ,4 },
    {10,4 },
    {7 ,1 },
    {10,10},
    {4 ,6 },
    {10,7 },
    {2 ,8 }
};

int main(){
    int i;
    sort(a+0,a+10); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++){
        printf("%d %d\n",a[i].a,a[i].b);
    }

    return 0;
}
```

特别的，如果你的结构体只有两个数据，且想要从小到大排序，那可以用`pair`这个数据类型来代替，因为它本身就是可以比较大小的。
