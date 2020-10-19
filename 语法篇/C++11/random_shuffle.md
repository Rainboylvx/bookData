---
_id: "accd98ad3a"
title: random_shuffle
date: 2020-10-17 09:10
update: 2020-10-17 09:10
author: Rainboy
---

@[toc]

## 使用random_shuffle()算法

`random_shuffle`包含在`<algorithm>`头文件中

可以使用C++中的`random_shuffle()`算法对数组进行乱序。与生成单个随机数时一样，程序在调用`random_shuffle()`之前为随机数生成器确定种子。

**注:**`random_shuffle()`只能支持**随机访问迭代器**的容器,不用于`list`

**使用:**

```c
std::random_device rd; //随机种子
std::mt19937 rnd(rd());
random_shuffle(v.begin(), v.end(),rnd); //vector
random_shuffle(a,a+sizof(a)/sizof(a[0]),rnd);//数组
```

```c
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);

    for(int i = 0;i < v.size();i++)
        std::cout << v[i] << ' ';
    std::cout << "\n";
}
```

### 自己实现 --没有写完

让我们看看C++的程序，下面的程序是给直接在数组中进行乱序，每次随机选择一个位置，把它与最后一
个位置的数据对换，直到结束。

如果能生成0-n不重复的随机数字,不就OK了

```c
void randArray(void)
{
int t=0;

for(int i=0;i<LEN;i++)
{
a[i]=i+1;
}

for(int i=0;i<LEN;i++)
{
t=rand()%LEN;
swap(a[i],a[t]);
}
}
```

