---
_id: "1180a3c36a"
title: helloworld
date: 2020-11-03 15:19
update: 2020-11-03 15:19
author: Rainboy
---

## 竞赛环境的准备

请看`附录篇/竞赛环境的准备` 三节视频课

- [学习环境的安装（一）：ubnuntu20.04 的安装](https://www.bilibili.com/video/BV1sV411y7NK)
- [学习环境的安装（二） 系统设置与软件安装](https://www.bilibili.com/video/BV1KT4y1F7Y3)
- [学习环境的安装（三）终端的简单使用](https://www.bilibili.com/video/BV1rv411671f)

自学大概一天你可以学会

## vim的学习使用

请看`附录篇/vim/vim的安装与使用` 视频课

[vim的学习 - 视频教程](https://www.bilibili.com/video/BV1Gy4y1r7s5)

自学大概一天你可以学会，随着打代码的增多与时间的推移你会越来越熟练！

## 第一个程序

本书的教学环境我已经录好视频，打开vim输入下面的代码：`vim 1.cpp`

**代码**

```c
#include <cstdio> //头文件
int main(){ //主函数
    printf("hello world!"); //输出
    return 0; //程序结束
}
```

保存`:wq`，退出vim。在终端下输入

```bash
g++ -g -o 1 1.cpp
```

这样可以使用编译命令`g++`，把我们写的代码编译成一个可执行的程序`1`，运行它

```bash
./1
```

会发现程序执行成功，输出`hello world!`

## 编译命令的快捷使用

```b
b 1.cpp
```
