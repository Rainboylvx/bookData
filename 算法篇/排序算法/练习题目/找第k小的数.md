# 找第k小的数

题目地址: https://www.luogu.org/problemnew/show/1138

## 解析

排序后输出,一个一个找到第k个数,每个数和前面的数比较,如果不同,计数加1

## 代码

使用了quicksort

```c
/* 
 *   快速排序本质:
 *      用key值,把数据分成两个部分,一部分比较key小,一部分比key大
 * */

#include <cstdio>

int a[10010];
int n,k;

void quicksort(int l,int r){
    if( l < r) {
    int s=l,t=r;
    int key =a[l]; // 取第一个值为key

    while(s < t){
        while( s <t && a[t] >= key) --t;// 如果a[t] >= key,t下标不停变小,直到a[t] < key
        if(s < t) a[s++] = a[t];        //停下来的时候,看一看,是不是到中点,如果不是 交换值
        while(s<t && a[s] <= key) ++s;  //如果a[s] <= key  s的下标不停变大,直到a[s] > key
        if(s<t ) a[t--] = a[s];         //停下来的时候,看一看,是不是到了中点,如果不是,交换值
    }
    a[s] = key;  //上面while停止的时候,一定是s ==t
    quicksort(l,s-1);
    quicksort(s+1,r);
}
}

int main(){
	scanf("%d%d",&n,&k);
	int i,j;
	for(i=1;i<=n;i++)
	scanf("%d",&a[i]);
	quicksort(1,n);
	if( k ==1 ) printf("%d",a[1]);
	else {
		int cnt =1;
		for(i=2;i<=n;i++)
			if( a[i] != a[i-1]){
				cnt++;
				if( cnt == k){
					printf("%d",a[i]);
					return 0;
				}
			}
	}
	printf("NO RESULT");
    return 0;
}
```
