#include <bits/stdc++.h>
using namespace std;

int n;
int a[100005];

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
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    quicksort(1, n);
    for (i=1;i<=n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}
