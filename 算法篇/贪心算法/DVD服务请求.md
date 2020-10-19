## DVD服务请求

--------------
### 解析
方法是贪心，策略是每一次拔出的光盘是所有DVD机内最后再次被请求的那张光盘

ps:**我真的没有想明白为什么这样贪心?**

```c
#include<iostream>
#include<algorithm>
using namespace std;

typedef struct{
    int DVD, next;
}node;
bool comp( node x, node y ){//控制sort快排的顺序 
    return x.next < y.next;
}

int main(){
    int K, N, DO=0, in=0, cutin;//DO记录插盘次数，in记录有多少个DVD机内插了DVD 
    bool judge1, judge2;//1是判断是否需要进行插盘操作，2是判断该请求光盘是否还会再次被请求 
    cin >> K >> N;
    int order[N];//记录请求序列 
    node player[K];//记录DVD机内的DVD盘序号和该DVD光盘下次被使用的请求序列 
    for( int i = 0; i < N; i ++ )
        cin >> order[i];
    for( int i = 0; i < K; i ++ )
        player[i].DVD = player[i].next = 0;//player结构体初始化 
    for( int i = 0; i < N; i ++ ){
        if( in < K ) cutin = in;
        else cutin = in - 1;
        judge1 = false;//判断此次请求所需的光盘是否已在DVD机内 
        for( int j = 0; j < in; j ++ )
            if( order[i] == player[j].DVD ){
                judge1 = true;
                cutin = j;
                break;
            }
        judge2 = false;//判断该光盘是否还会被请求 
        for( int j = i + 1; j < N; j ++ )
            if( order[j] == order[i] ){//如果第j次请求是该光盘 
                player[cutin].next = j;
                judge2 = true;
                break;
            }
        if( judge1 == false ){//如果该光盘不在DVD机内，需要进行插盘操作 
            player[cutin].DVD = order[i];
            if( in != K ) in ++;
            DO ++;
        }
        if( judge2 == false ) player[cutin].next = N;//如果该光盘不会再被使用 
        sort( player, player + in, comp );//player排序 
    }
    cout << DO;
    return 0;
}
```
--------------
