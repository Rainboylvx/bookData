# C++排序函数 sort


下面的我们来使用C++本身给我们提供的排序函数.

```
sort(a+m,a+n);      //[a+m,a+n) 范围内的元素进行排序
sort(a+m,a+n,cmp); //cmp 是函数
```


样例代码

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100];
int main(){
    int i;
    for (i=0;i<10;i++){ //输入10个数
        scanf("%d",&a[i]);
    }

    sort(a+0,a+10); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```


如果我们想让从大到小排序怎么办?

```c
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100];

/* 原是是为真的时候,第一个数字放前面 */
int mycmp(int &a,int &b){ 
    if(a > b)
        return 1;
    return 0;
}

int main(){
    int i;
    for (i=0;i<10;i++){ //输入10个数
        scanf("%d",&a[i]);
    }

    sort(a+0,a+10,mycmp); //数组名+数字的本质是指针操作
    for(i=0;i<10;i++)
        printf("%d ",a[i]);

    return 0;
}
```
