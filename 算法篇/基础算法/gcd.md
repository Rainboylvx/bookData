---
_id: "1346dd11aa"
title: gcd
date: 2020-09-29 10:51
update: 2020-09-29 10:51
author: Rainboy
---


## 最大公约数:gcd

<!-- template start -->
求解问题：两个整数a,b的最大公约数。

Code：

```c
int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a%b);
}
```
<!-- template end -->


## 证明
gcd(a,b)=gcd(b,a%b)。

设r=a%b，则有a=kb+r。

设d为a,b的任意一个公因数，则有d∣a，d∣b→d∣r=a−kb；
另设d为b,r的任意一个公因数，则有d∣b，d∣r=a−kb→d∣a=kb+r。
由上可知d既是a,b的公因数，又是b,a%b的公因数，于是最大公约数也成立。命题得证。

http://blog.csdn.net/kanosword/article/details/52955557

## 最小公倍数lcm



<!-- template start -->

根据小学的公式，得到lcm:

$$lcm(a,b) = a \times b \div gcd(a,b)$$

```c
int lcm(int a,int b){
    return a*(b /gcd(a,b));
}
```
<!-- template end -->

## 练习题目

 - luogu P1029 最大公约数和最小公倍数问题
 - luogo P1888 三角函数 入门难度
 - luogu P2651 添加括号III 入门难度
 - luogu P1372 又是毕业季I 洛谷原创 入门难度
 - luogu P4057 [Code+#1]晨跑
 - [luogu P1290 欧几里德的游戏](<%- USER.pcs_site %>luogu-P1290)
