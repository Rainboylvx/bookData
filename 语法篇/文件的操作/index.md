# 文件的操作

我们在NOIP,NOI的竞赛中,要求我们从**文件**读入数据,然后把计算出的数据**写入**到一个文件中.我们平时使用的OJ站点(洛谷,codevs等)已经帮我们把程序自动和文件关联起来(但cogs不会),使我们可以少写两句代码.但是在真实的比赛中,我们是程序中自己读入文件和写入文件的.

## 一个题目

`c++`操作文件的函数很多,我们只用学会其中最简单的一个:

```c
freopen("1.in","r",stdin);
freopen("1.out","w",stdout);
```


我们来看一下`COGS`上面的第一人题目来学习一下:

### 代码

```c
#include <cstdio>
int main(){
	freopen("aplusb.in","r",stdin);
	freopen("aplusb.out","w",stdout);
	double a,b;
	scanf("%lf%lf",&a,&b);
	printf("%.0lf",a+b);
	return 0;
}
```

## linux下的输入输出重定向

linux下我们可以很方便的使用`<`和`>`重定向标准输入,标准输出

```bash
ls ./ > ls.txt
```

```c
#include <cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",a+b);
    return 0;
}
```
