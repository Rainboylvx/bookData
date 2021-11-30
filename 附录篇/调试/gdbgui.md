## 前言

可能对一些初学都同学来说，在终端使用GDB或CGDB十分不习惯，所以这里介绍一个可视化的调试工具 [gdbgui](https://www.gdbgui.com/) 它十的简单，但夠初学者使用了

## 安装

[Installation - gdbgui](https://www.gdbgui.com/installation/)

我这里使用最简单的

在noilinux2.0 也就是ubuntu 20.04 下安装
```bash
sudo apt update
sudo apt install python3-pip
sudo pip3 install gdbgui
```


## 简单的介绍使用

- start 开始执行
- pause
- continue 继续执行
- step over 步过
- step into 步入
- step out  步出

[Getting Started - gdbgui](https://www.gdbgui.com/gettingstarted/)

```c++
#include <iostream>

int add(int a,int b){
    int sum = a+b;
    return sum;
}

int main(){
    int a,b,c;
    a = 1;
    b = 2;
    c = 3;
    c = add(a,b);
    std::cout << c << std::endl;
    return 0;
}
```

## 技巧1 如何略过不要想一步步执行的代码

```c++
#include <iostream>

int main(){
    int a=0,b,c;
    for(int i=1;i<=100;++i){
        a++;
    }
    std::cout << a << std::endl;

    return 0;
}
```

## 技巧2 从文件里读入数据

```c++
#include <iostream>

int main(){
    std::cin >> a;
    std::cout << a << std::endl;
    return 0;
}
```

## 技巧3 条件断点

在视频里

## 其它

 - [ 在线调试  | GDB online Debugger ](https://www.onlinegdb.com/)，
