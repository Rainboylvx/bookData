
## 调试利器GDB

GUIDE的调试功能其实弱的可怜,要想快速的调试当然是用`GDB`了

 - [GDB官网](https://www.gnu.org/software/gdb/)
 - [什么是GDB-enWiki](https://en.wikipedia.org/wiki/GNU_Debugger)
 - [什么是GDB-zhWhiki](https://zh.wikipedia.org/wiki/GNU_Debugger)
 - [GDB十分钟教程](http://blog.csdn.net/liigo/article/details/582231)
 - [GDB教程系列1-7](http://blog.csdn.net/haoel/article/details/2879)
 - [视频教程-Linux C语言指针与内存](http://www.imooc.com/learn/394)


## 开始

首先记住下面的基本命令:

g++是编译器，gdb是调试工具。我们使用的GUIDE就是建立在这两个工具上面的,GUIDE支持直接操作gdb，但是很不好用。

在Linux中，可以使用“终端”直接调用g++和gdb。在Windows中，需要对PATH环境变量进行修改[ Windows XP下的设置方法：右击“我的电脑”，选择“属性”，进入“高级”选项卡。单击“环境变量”按钮，在弹出的对话框中找到PATH，点击“编辑”，在后面加入g++所在路径，如“C:\MinGw\bin”。]，加入g++和gdb所在目录，才能在“命令提示符”中直接调用它们。下面假设你的工作目录是程序所在目录，可以直接调用g++和gdb，并且已经打开了“终端”或“命令提示符”。

如果手动编译程序，输入`g++ test.cpp -o test.exe`（Linux下不需要“.exe”，下同）。

以下是g++常用的编译参数：

 - -o：指定编译之后的程序名。如果不输入，程序就叫“a.exe”。
 - -Wall：输出警告。
 - -DDEBUG：编译时定义一个叫“DEBUG”的符号。
 - -O1、-O2、-O3：优化。从1到3速度由慢到快。但“-O3”容易误解程序员意思。
 - -g：产生调试符号。加入“-g”之后就可以用gdb直接调试程序。
 - -lm：自动链接数学库（<math.h>）。

**GDB常用命令:**


| 命令          | 全称            | 作用                                                                                                      | 实例和说明                                                                                                              |
|---------------|-----------------|-----------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|
| file <文件名> | file            | 加载被调试的可执行程序文件。<br>因为一般都在被调试程序所在目录下执行GDB，因而文本名不需要带路径。         | (gdb) file gdb-sample                                                                                                   |
| r             | Run             | 运行被调试的程序。 <br>如果此前没有下过断点，则执行完整个程序；如果有断点，则程序暂停在第一个可用断点处。 | (gdb) r                                                                                                                 |
| c             | Continue        | 继续执行被调试程序，直至下一个断点或程序结束。                                                            | (gdb) c                                                                                                                 |
| l             | list            | 查看源代码。                                                                                              | l 15：显示第15行及附近代码。<br>l main：显示main()附近10行。<br>如果不带参数，将继续显示上次代码的后10行。              |
| b <br>cl      | break<br> clear | 设置断点。<br>取消断点。	<br>                                                                          | b 24或cl 24：在第24行设置/取消断点。<br>b main或cl main：在main()入口处设置/取消断点。                                  |
| b的进一步使用 |                 |                                                                                                           |                                                                                                                         |
| b <行号>      | break           | 使用**行号**设置断点                                                                                      |                                                                                                                         |
| b <函数名称>  | break           | 使用**函数名称**设置断点                                                                                  |                                                                                                                         |
| b *<函数名称> | break           | 使用**执行地址**设置断点                                                                                  |                                                                                                                         |
| b *<代码地址> | break           | 使用**执行地址**设置断点                                                                                  |                                                                                                                         |
| d [编号]      | delete          | d: Delete breakpoint的简写，删除指定编号的某个断点，或删除所有断点。断点编号从1开始递增。                 |                                                                                                                         |
| r             | run             | 运行程序。                                                                                                | 一直运行，直到遇到断点或程序结束。                                                                                      |
| c             | continue        | 继续运行。                                                                                                | 中断之后使用。                                                                                                          |
| k             | kill            | 杀死正在调试的进程。                                                                                      | 停止调试。                                                                                                              |
| u             | until           | 让程序运行到指定位置。                                                                                    | u 9：运行到第九行，然后暂停。<br>u search：运行到search()的入口，然后暂停。                                             |
| disp          | display         | 相当于IDE里的“Watch”。                                                                                    | disp x：每次程序暂停，自动输出x的值。<br>disp x+1：自动输出表达式“x+1”的值。<br>dis disp或en disp：禁用/启用所有Watch。 |
| n<br>s        | next<br>step    | 单步运行-步过。	<br>单步运行-步入                                                                         | 单步执行。它们区别是一旦遇到函数，“s”要进入函数内部，而“n”直接计算函数的值然后继续。<br> n 10 执行10次n                 |
| P             | print           | 计算表达式。                                                                                              | p a：输出变量a的值。<br>p 1+1：计算“1＋1”的值。                                                                         |
|               | call            | 执行一条C++代码，如果有返回值，就输出到屏幕上                                                             | call j=2：改变变量j的值<br>call print()：调用print()                                                                    |
| i             | info            | 显示信息。                                                                                                | i b：显示所有断点<br>i lo（info locals）：显示所有局部变量。<br>i disp：显示所有“Watch”。                               |
| d             | delete          | 删除。                                                                                                    | d disp：删除所有“Watch”。<br>d breakpoints：删除所有断点。<br>bt	backtrace	查看调用栈。                            |
| q             | quit            | 退出gdb。                                                                                                 |                                                                                                                         |
| h             | help            | 获得帮助信息。                                                                                            | 全部是英语。                                                                                                            |
|               | whatis          | 查看变量类型                                                                                              | whatis n：查看n的类型                                                                                                   |
| 直接回车      |                 | 执行上一条命令。                                                                                          | 在输入n或s后一路回车，相当于打了一路n或s。                                                                              |
| bt            | backtrace       | 查看堆栈                                                                                                  | bt 可以知道当前在哪一行                                                                                                 |
以下是和断点有关的命令。使用之前，要知道断点的编号（可用`i b`查看）：

| 命令 | 全称      | 作用                                  | 实例和说明                                                                |
|------|-----------|---------------------------------------|---------------------------------------------------------------------------|
| ig   | ignore    | 让断点在前n次到达时都不停下来。       | ig 3 12：让编号为3的断点在前12次到达时都不停下来。                        |
| cond | condition | 给断点加一个条件。                    | cond 2 i>3：2号断点只有在i>3时才起作用。                                  |
| comm | commands  | 在某个断点处停下来后执行一段gdb命令。 | comm 4：在断点4停下来后执行一段命令。输入这条命令后，就输入要执行的内容。 |
| wa   | watch     | 当变量或表达式的值发生改变时停下来。  | wa i：当i的值发生改变时停下来。                                           |
| aw   | awatch    | 变量被读写时都会停下来。              | aw i：当i被读写时都会停下来。                                             |
| rw   | rwatch    | 当变量被读的时候停下来。              | rw i：当i被读时停下来。                                                   |



--------------------------

## 讲解--初级使用

### 题目1:使用GBD调试A+B问题

下面我们就以大家都会的A+B问题来讲解一下GDB的入门


视频:-->以后添加



1.确保我们的g++.exe 已经加入windows下的环境变量
 
```
打开cmd
g++ -v 试一试
```

2.编译我们的程序 -g 一定要写在-o的前面


A+B代码:

```c
#include <cstdio>

int aplusb(double a,double b){
    int x = a+b;
    return x;
}

int main(){
    double i,j;
    scanf("%lf%lf",&i,&j);
    int a = aplusb(i,j);
    printf("%d",a);
    return 0;
}

```

``` 
g++ -g -o aplusb.exe aplusb.cpp
```
 
如果在linux平台下.exe 这个后缀名,不用写

```  
g++ -g -o aplusb aplusb.cpp
```  

3.如何载入与运行程序

 - file
 - r-run
 - l-list
 - n-next
 - s-step

4.断点的使用简单使用

 - b行号,函数名,
 - d断点编号,cl
 - `i b`所有断点,`i lo`,`i disp`

5.disp的使用

 - disp 表达式
 - dis disp 或者 en disp
 -

6.其它

  - 直接回车-上一次的代码
  - quit
  - help
  - call 执行一条代码,相当于`repl`
  - P-print 计算表达式
  - bt backtrace 查看调用栈
  - u-until 直到


7.断点的使用高级使用

怎么知道`for`第50次后的`j`的值?

```c
int main(){
    int i,j=0;
    for(i=0;i<100;i++)
        j+=i;
    return 0;
}
```

 - ig
 - cond


找到最大值

```c
int a ={4,5,7,9,2,7,1,7,3,6,7,1,2,4};
int main(){
    int i,max = 0xffffffff;
    for(i=0;i<sizeof(a);i++)
        if(max < a[i])
            max = a[i];
    return 0;
}
```

 - watch
 - awatch
 - rwatch


----------------------

### 其它技巧

#### 数组

有时候，你需要查看一段连续的内存空间的值。比如数组的一段，或是动态分配的数据的大小。你可以使用GDB的“@”操作符，“@”的左边是第一个内存的地址的值，“@”的右边则你你想查看内存的长度。例如，你的程序中有这样的语句：

`int *array = (int *) malloc (len * sizeof (int));`

于是，在GDB调试过程中，你可以以如下命令显示出这个动态数组的取值：

```
p *array@len
```

@的左边是数组的首地址的值，也就是变量array所指向的内容，右边则是数据的长度，其保存在变量len中，其输出结果，大约是下面这个样子的：
```
(gdb) p *array@len
$1 = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40}
```
如果是静态数组的话，可以直接用print数组名，就可以显示数组中所有数据的内容了。

#### 多个变量

```
(gdb) p {i, start, end}
$4 = {2, 3, 5}
```

这样子就可以一下显示多个变量的值了。
如果向自动的显示变量的值，
可以使用`display {i, start, end}`
这样子在每次单步的时候，会显示这三个变量的值。



#### 输出格式

一般来说，GDB会根据变量的类型输出变量的值。但你也可以自定义GDB的输出的格式。例如，你想输出一个整数的十六进制，或是二进制来查看这个整型变量的中的位的情况。要做到这样，你可以使用GDB的数据显示格式：

| 数值 | 含义                           |
|------|--------------------------------|
| x    | 按十六进制格式显示变量。       |
| d    | 按十进制格式显示变量。         |
| u    | 按十六进制格式显示无符号整型。 |
| o    | 按八进制格式显示变量。         |
| t    | 按二进制格式显示变量。         |
| a    | 按十六进制格式显示变量。       |
| c    | 按字符格式显示变量。           |
| f    | 按浮点数格式显示变量。         |

例子:

```c
(gdb) p/a i
$22 = 0x65
(gdb) disp/a i
```


#### 输入输出重定向

当我们使用终端输入数据较多时,我们会选择从文件读入:

```
freopen("1.in","w",stdin);
```
但是我们很懒,不想写这句代码,而且这个代码把我们的读入文件写死了,怎么办?
我们可以用shell的重定身功能

```
a.exe <1.in
```

同样可以输出重定向

```
a.exe >1.out
a.exe <1.in >1.out
```

在Gdb中怎么用?

```c
gdb a.exe
run <1.in >1.out
```

我们也可以在单步中使用

```c
s <1.in
s <1.in >1.out
```



----------------

## 题目练习


### 题目1:使用GDB的调试功能,找到下面代码的2个错误

代码要实现的功能:输入数字n(0<=n<=60),输了Fibonacci前n项,

修改要求:增加或删除的字符数==2(把代码自己重写一遍是错误的)

```c
#include <cstdio>
int a[100] = {0};
void fibo(int b){
    a[1] = 1;
    a[0] = 1;
    int i;
	for(i=0;i<b && i<2;i++)
		printf("%d ",a[i]);
    for(i=2;i<=b;i++)
        printf("%d ",a[i]=a[i-1]+a[i-2]);
}
int main(){
	int t;
	scanf("%d",t);
	fibo(t);
    return 0;
}
```

### 题目2: 冒泡排序哪里错了呢?


 - 第一步:a为什么不能排序?
 - 第二步:为什么会运行时错误?

```c
int a[]= {4,5,3,2};
int main(){
    int i,j,t;
    for(i=0;i<sizeof(a);i++)
        for(j=0;j<sizeof(a)-i;i++)
            if(a[j] > a[j+1])
                t=a[j],a[j]=a[j+1],a[j+1]=t;
	return 0;
}
```

## 总结

!!!学习使用了GDB一段时间后，就会发现它真的好强大！好用！


## 拓展

NOIP用不到或者不能用的

 - [CGDB](https://cgdb.github.io/)
 - [CGDB中文手册](https://www.gitbook.com/book/leeyiw/cgdb-manual-in-chinese/details)
