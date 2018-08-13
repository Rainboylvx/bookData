## STL的中二分查找

$$lower_bound( )$$和$$upper_bound( )$$都是利用二分查找的方法在一个排好序的数组中进行查找的。

**函数原型:**四个参数
```c
template< class ForwardIt, class T, class Compare >
constexpr ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
```
## 在从小到大的排序数组中

$$lower_bound( begin,end,num)$$：从数组的$$begin$$位置到$$end-1$$位置二分查找第一个大于或等于$$num$$的数字，找到返回该数字的地址，不存在则返回$$end$$。通过返回的地址减去起始地址$$begin$$,得到找到数字在数组中的下标。


$$upper_bound( begin,end,num)$$：从数组的$$begin$$位置到$$end-1$$位置二分查找第一个大于$$num$$的数字，找到返回该数字的地址，不存在则返回$$end$$。通过返回的地址减去起始地址$$begin$$,得到找到数字在数组中的下标。

数据:



```
8 4
1 2 2 3 4 5 6 7
1 2
1 7
2 2
2 7
```
 - `1 7`表示找到第一个`>=7`元素的下标,找不到输出`-1`
 - `2 7`表示找到第一个`>7`元素的下标,找不到输出`-1`


```c
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m;
int a[100];

int main(){
    int i,j,k;
    
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    int t1,t2;
    
    for (i=1;i<=m;i++){
        scanf("%d%d",&t1,&t2);
        if(t1 == 1){
            int ans = lower_bound(a,a+n+1,t2) - a;
            ans = ans <=n ? ans :-1;
            printf("%d\n",ans);
        }
        else{
            int ans = upper_bound(a,a+n+1,t2) - a;
            ans = ans <=n ? ans :-1;
            printf("%d\n",ans);
        }
    }
    return 0;
}
```


## 在从大到小的排序数组中，重载lower_bound()和upper_bound()

$$lower_bound( begin,end,num,greater<type>() )$$:从数组的begin位置到end-1位置二分查找第一个小于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

upper_bound( begin,end,num,greater<type>() ):从数组的begin位置到end-1位置二分查找第一个小于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
