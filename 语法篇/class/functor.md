# 仿函数(functor)教程

仿函数(functor)，就是使一个类的使用看上去象一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了

有些功能的的代码，会在不同的成员函数中用到，想复用这些代码。


## 使用functor的意义


### 公共的函数

可以，这是一个解决方法，不过函数用到的一些变量，就可能成为公共的全局变量，再说为了复用这么一片代码，就要单立出一个函数，也不是很好维护。

### 仿函数

写一个简单类，除了那些维护一个类的成员函数外，就只是实现一个operator()，在类实例化时，就将要用的，非参数的元素传入类中。

### 意义

 - 因为仿函数可以拥有成员函数和成员变量，这意味着仿函数拥有状态。另一个好处是可以在执行期初始化它们。
 - 仿函数都有自己的型别(泛型编程编写仿函数)
 - 仿函数通常比一般函数快(就template而言)


##  认识仿函数

### 重载()

求两个int变量的最大值

### 代码1
```c
#include <iostream>
#include <string>
using namespace std;

struct _max {
    int operator()(int &a,int &b){
        return a>b?a:b;
    }
};

int main(){
    _max myMax;
    int x= 1,y=2;
    int m = myMax(x,y);
    cout << "max:" << m << endl;
    return 0;
}
```

### 代码2:更规范的写法

```c
#include <iostream>
#include <string>
using namespace std;

struct _max {
    //提供初始化
    _max(){}
    int operator()(const int &a,const int &b) const{
        return a>b?a:b;
    }
};

int main(){
    _max myMax;
    int x= 1,y=2;
    int m = myMax(x,y);
    /* 
     * int m = myMax(1,2);
     * 这样写就错了,想想为什么
     * */
    cout << "max:" << m << endl;
    return 0;
}
```

## 通过实例学习functor

第一个代码

```c
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

// this is a functor
struct add_x {
  add_x(int x) : x(x) {}
  int operator()(int y) { return x + y; }
  int x;
};

int a[] = {1,2,3};
int main(){
    // 相济使用:
    add_x add42(42); // 创建一个类
    int i = add42(8); // "调用"它
    assert(i == 50); // and it added 42 to its argument
    if( i == 50 )
        cout << "i== 50 " <<endl;
    vector<int> in(a,a+3); // 创建vector
    vector<int> out(3);
    
    transform(in.begin(), in.end(), out.begin(), add_x(1)); 
    
    i;
    for(i=0;i<3;i++){
        cout << in[i]<<" " << out[i] << endl;
    }
    
    return 0;
}
```

## 说明

引用
https://my.oschina.net/llehs/blog/180594
