先来看看样例数据： `7 8 1 4 3 2` 每次取某位置之前连续两个数中的最小值。 


维护一个**单调增双端队列**,当你处理到第$$i$$个数的时候,有以下情况:

 - 队列为空,表示没有元素,输出$$0$$,
 - 队列不空,队列头存的是最小值的下标,用$$min_idx$$表示
   - 如果$$min_idx$$不在$$i$$的前$$m$$个数的范围内,也就是$$i-min_idx >m$$,那就弹出头,输出现在的头代表的值
   - 如果$$min_idx$$在$$i$$的前$$m$$个数的范围内,也就是$$i-min_idx <=m$$,那就输出现在的头代表的值


通用处理,把下标$$i$$加入队列,$$a[i]$$表示第$$i$$个元素的值,它是有可能对后面的元素有用的,如果把它加入队列中,因为它比较靠右,所以队列中所有比它大的元素都没有用了.

## 代码:单调队列

```c
#include <cstdio>

#define maxn 2000001

int q[maxn] = {0}; //双端单调队列
int a[maxn]={0}; //原数组
int head=0,tail=0; //队列头尾,tail指向最后一个元素的后面一个位置

bool empty(){
    return head == tail;
}
//加入队列
void push(int x){

    // 队列非空,删除比x大的元素
    while( a[ q[tail-1]] >= a[x] && !empty()) tail--;
    q[tail++] = x;
}

//弹出头
void pop(){ 
    if( !empty()) head++;
}

int front(){
    return q[head];
}


int main(){
    int i,n,m;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++){
        if( empty()) 
            printf("0\n");
        else {
            int min_idx = front();
            if( i - min_idx >m) pop();
            printf("%d\n",a[ front()] );
        }
        push(i);

    }
    return 0;
}
```
