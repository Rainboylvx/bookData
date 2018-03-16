## 辗转相除法

求解问题：两个整数a,b的最大公约数。

Code：

int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a%b);
}


## 证明
gcd(a,b)=gcd(b,a%b)。

设r=a%b，则有a=kb+r。

设d为a,b的任意一个公因数，则有d∣a，d∣b→d∣r=a−kb；
另设d为b,r的任意一个公因数，则有d∣b，d∣r=a−kb→d∣a=kb+r。
由上可知d既是a,b的公因数，又是b,a%b的公因数，于是最大公约数也成立。命题得证。

http://blog.csdn.net/kanosword/article/details/52955557
