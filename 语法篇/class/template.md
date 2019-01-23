# 模板


## 前言

假如设计一个求两参数最大值的函数,但是我们不知道参数的类型,在实践中我们可能需要定义四个函数：

```c
int max ( int a , int b ) { return ( a > b ) ? a , b ; }

long max ( long a , long b ) { return ( a > b ) ? a , b ;}

double max ( double a , double  b ) { return ( a >b)? a , b ; }

char max ( char a , char b ) { return ( a > b ) ? a , b ;}
```

这些函数几乎相同，唯一的区别就是形参类型不同

需要事先知道有哪些类型会使用这些函数，对于未知类型这些函数不起作用

## 模板的概念

所谓模板是一种使用**无类型参数**来产生一系列函数或类的**机制**。

若一个程序的功能是对某种**特定的数据类型**进行处理，则可以将所处理的数据类型说明为参数，以便在其他数据类型的情况下使用，这就是模板的由来。

模板是以一种**完全通用**的方法来设计函数或类而不必预先说明将被使用的每个对象的类型。

通过模板可以产生类或函数的集合，使它们操作不同的数据类型，从而避免需要为每一种数据类型产生一个单独的类或函数。 

## 模板分类


**1.函数模板(function template)**

  - 是独立于类型的函数
  - 可产生函数的特定版本

**2.类模板(class template)**

 - 跟类相关的模板，如vector
 - 可产生类对特定类型的版本，如vector<int>


## 模板的使用


1.模板的写法

```c
<返回值类型> <函数名>（模板函数形参表）
{
      //函数定义体
}
```

2.求两个数最大值，使用模板

```c
template <typename T >
bool mymax(const T &x , const T & y){
        return ( x > y ) ? x:y;
}
```


3.调用

```c
#include <iostream>
using namespace std;

//因为有默认的max函数,所以我们取名mymax
template <typename T >
T mymax(const T &x , const T & y){
        return ( x > y ) ? x:y;
}

int main(){
    int a=1,b=2;
    cout << "int: "<<mymax(a,b)<<endl;
    double c=1.1,d=1.2;
    cout << "double: "<<mymax(c,d)<<endl;
    return 0;
}
```

### 问题1

编写一个对具有n个元素的数组`a[ ]`求最小值的程序，要求将求最小值的函数设计成函数模板

```c
#include <iostream>
using namespace std;

template <typename T>
T mymin(T a[],int n){
    int i;
    T minv = a[0];
    for(i=1;i<n;i++)
        if(minv >a[i])
            minv=a[i];
    
    return minv;
}

int a[] = {1,2,3,4,1,2,3,4};
double b[] = {1.2,-3.4,6,6,8,1.1};

int main(){
    cout << "min in a[]:" << mymin(a,8) <<endl;
    cout << "min in b[]:"<< mymin(b,6)<<endl;

    return 0;
}
```

## 最简单类模板的使用

模板技术也可以用在类上,我们下面定义一个最简单的模板类,同学们能体会它的作用即可.


```c
#include <iostream>
using namespace std;

template <typename f>
struct chengji{
    f fen;
};

int main(){
    chengji<int> xiaoming;
    xiaoming.fen = 100;
    cout << xiaoming.fen  << endl;
    
    chengji<double> xiaohong;
    xiaohong.fen = 110.11;
    cout << xiaohong.fen << endl;
    return 0;
}
```


## 模板的好处

 - 函数模板方法克服了C语言解决上述问题时用大量不同函数名表示相似功能的坏习惯
 - 克服了宏定义不能进行参数类型检查的弊端
 - 克服了C++函数重载用相同函数名字重写几个函数的繁琐
 - 缺点，调试比较困难

## 说明

百度文库PPT
http://wenku.baidu.com/link?url=XCXYE4uANTHEQykVBR5vAtevKPYEXB93gfjzHHONmHF_Rb-paUKric2sgp8AbAUlbIMejsxWXuUsvPKrJ9XqffHmqHs6ZSAW7byEow1J4jW

