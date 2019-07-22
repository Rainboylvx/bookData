# lambda

lambda表达式在其所在的位置上定义了一个匿名函数对象。构造闭包：能够俘获作用域中的变量的无名函数对象


```c
[ 俘获 ] <模板形参>(可选)(C++20) ( 形参 ) 说明符(可选) 异常说明 attr -> ret requires(可选)(C++20) { 函数体 }
[ 俘获 ] ( 形参 ) -> ret { 函数体 }
[ 俘获 ] ( 形参 ) { 函数体 }
[ 俘获 ] { 函数体 }
```

```plaintext
[函数对象参数] (操作符重载函数参数) mutable或exception声明 ->返回值类型 {函数体}

一、[函数对象参数]，标识一个Lambda的开始，这部分必须存在，不能省略。函数对象参数是传递给编译器自动生成的函数对象类的构造函数的。函数对象参数只能使用那些到定义Lambda为止时Lambda所在作用范围内可见的局部变量（包括Lambda所在类的this）。函数对象参数有以下形式：


1、空。没有使用任何函数对象参数。

2、=。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是值传递方式（相当于编译器自动为我们按值传递了所有局部变量）。

           3、&。函数体内可以使用Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this），并且是引用传递方式（相当于编译器自动为我们按引用传递了所有局部变量）。

4、this。函数体内可以使用Lambda所在类中的成员变量。
           5、a。将a按值进行传递。按值进行传递时，函数体内不能修改传递进来的a的拷贝，因为默认情况下函数是const的。要修改传递进来的a的拷贝，可以添加mutable修饰符。
6、&a。将a按引用进行传递。
7、a, &b。将a按值进行传递，b按引用进行传递。
8、=，&a, &b。除a和b按引用进行传递外，其他参数都按值进行传递。
9、&, a, b。除a和b按值进行传递外，其他参数都按引用进行传递。

1.[var]表示值传递方式捕捉变量var；
2.[=]表示值传递方式捕捉所有父作用域的变量（包括this）；
3.[&var]表示引用传递捕捉变量var；
4.[&]表示引用传递方式捕捉所有父作用域的变量（包括this）；
5.[this]表示值传递方式捕捉当前的this指针。

上面提到了一个父作用域，也就是包含Lambda函数的语句块，说通俗点就是包含Lambda的“{}”代码块。上面的捕捉列表还可以进行组合，例如：

1.[=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量;
2.[&,a,this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。

不过值得注意的是，捕捉列表不允许变量重复传递。下面一些例子就是典型的重复，会导致编译时期的错误。例如：

3.[=,a]这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;
4.[&,&this]这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复。

二、(操作符重载函数参数)，标识重载的()操作符的参数，没有参数时，这部分可以省略。参数可以通过按值（如：(a,b)）和按引用（如：(&a,&b)）两种方式进行传递。
      三、mutable或exception声明，这部分可以省略。按值传递函数对象参数时，加上mutable修饰符后，可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）。exception声明用于指定函数抛出的异常，如抛出整数类型的异常，可以使用throw(int)。

四、`->`返回值类型，标识函数返回值的类型，当返回值为void，或者函数体中只有一处return的地方（此时编译器可以自动推断出返回值类型）时，这部分可以省略。

五、{函数体}，标识函数的实现，这部分不能省略，但函数体可以为空。
```


### a+b

```c
#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,b;
    cin >> a >> b;
    auto lambda_func = [=]()->int{
        return a+b;
    };
    cout << lambda_func();
    return 0;
}
```

## 2

```c
#include<iostream>
using namespace std;

int main()
{
    int j = 10;
    auto by_val_lambda = [=]{ return j + 1; };
    auto by_ref_lambda = [&]{ return j + 1; };
    cout<<"by_val_lambda: "<<by_val_lambda()<<endl;
    cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;

    ++j;
    cout<<"by_val_lambda: "<<by_val_lambda()<<endl;
    cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;

    return 0;
}
```

输出

```plaintext
by_val_lambda: 11
by_ref_lambda: 11
by_val_lambda: 11
by_ref_lambda: 12
```

你想到了么？？？那这又是为什么呢？为什么第三个输出不是12呢？
在by_val_lambda中，j被视为一个常量，一旦初始化后不会再改变（可以认为之后只是一个跟父作用域中j同名的常量），而在by_ref_lambda中，j仍然在使用父作用域中的值。所以，在使用Lambda函数的时候，如果需要捕捉的值成为Lambda函数的常量，我们通常会使用按值传递的方式捕捉；相反的，如果需要捕捉的值成成为Lambda函数运行时的变量，则应该采用按引用方式进行捕捉。

## 参考资料

 - [cppreference.com Lambda 表达式](https://zh.cppreference.com/w/cpp/language/lambda)
 - [C++11 语法记录: Lambda简单入门](https://blog.csdn.net/pleasecallmewhy/article/details/34941721)
 - [C++ 11 Lambda表达式 通俗易懂](https://blog.csdn.net/lcalqf/article/details/79401210)
