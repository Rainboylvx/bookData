## 题目地址
 [poj 1201 Intervals](https://vjudge.net/problem/poj-1201)

## 题意

有$$n$$个如下形式的条件:

$$a_i,b_i,c_i$$,表示在区间$$[a_i, b_i]$$内**至少**要选择$$c_i$$个整数点.

问你满足$$n$$个条件的情况下,最少需要选多少个点?

## 解析

差分约束系统.


令$$s[x]$$表示从区间$$[0,x]$$中选择的整数点个数.那么对于条件$$[ai, bi]$$选数$$>=ci$$个,就是$$s[bi]-s[ai-1]>=ci$$. 即$$s[ai-1]<=s[bi]+ (-ci)$$

假设有下面两个条件:

```
1 2 3
5 6 3
```
那么我们自然得出了$$s[2]-s[0]>=3$$ 且$$s[6]-s[4]>=3$$.

如果$$s[2]=3,s[0]=0,s[6]=3,s[4]=0$$ 是满足上面不等式的.但是其实是不合题意的.因为s[4]必然要>=s[2]和s[0]的.所以我们需要把s的相对值也联系起来.

这样就需要添加下面的边. 假设我们令输入读取的区间最大值为$$max_v$$. 那么对于所有 $$0<i<=max_v$$的值来说,有

$$0<=s[i]-s[i-1]<=1$$ .转换一下即是: $$s[i]<=1+s[i-1]$$ && $$s[i-1]<=0+s[i]$$.
根据上面的分析,我们要建的有向图是一个具有$$max_v+1$$个点的图.其中的边有:
$$n$$条$$s[bi]-s[ai-1]>=ci$$条件构成的从$$bi$$到$$(ai-1)$$的长$$-ci$$的边.
还有所有 $$0<i<=max_v$$的值构成的$$i到i-1的长0的边和$$i-1$$到$$i$$的长$$1$$的边.所以这样我们就形成了一个具有点$$[0,max_v]$$的有向图.在原图处理时,为了避免ai-1==-1,我们令所有ai与bi都自增了10.所以我们形成了一个具有点[9,max_v]的有向图(其实就是差分约束系统).我们的目标是令$$S[max_v]-S[9]$$的值最小.(切记这里不是仅使S[max_v]的值最小,因为我们这里只有从9
 ,10,11,…max_v 的值构成了一个差分约束系统.max_v的值和0号点的值是不在一个系统的. 0号点是超级源点,它的值与系统中其他点的值是无关的.)
       
然后我们上面已经知道了希望让系统中S[max_v]和S[9]的值差距尽量小.(构成差分约束系统时,1.如果在所有点外添加一个超级源0号点,并使得超级源到所有其他点的距离为0,那么最终求出的0号点到其他所有原始点的最短距离就是本系统的一个可行解,且可行解之间的差距最小.      2.如果初始时不添加超级源,只是将原始点的初始距离设为INF,且令其中一个原始点的初始距离为0,然后求该点到其他所有点的最短距离,那么最短距离的集合就是一个可行解,且该可行解两两之间的差距最大.注意方案2只能在该问题一定存在解的时候即肯定不存在负权环的时候用.否则从1号点到其他点没有路,但是其他点的强连通分量中有负权环,这样根本探测不到错误)
 所以我们需要采取方案1.



## 代码

```c
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn= 50000+10;
const int maxm=500000+10;
#define INF 1e9
 
struct Edge
{
    int from,to,dist;
    Edge(){}
    Edge(int f,int t,int d):from(f),to(t),dist(d){}
};
 
struct SPFA
{
    int n,m;
    int head[maxn],next[maxm];
    Edge edges[maxm];
    int d[maxn];
    bool inq[maxn];
 
    void init()
    {
        m=0;
        memset(head,-1,sizeof(head));
    }
 
    void AddEdge(int from,int to,int dist)
    {
        edges[m]=Edge(from,to,dist);
        next[m]=head[from];
        head[from]=m++;
    }
 
    int spfa()
    {
        memset(inq,0,sizeof(inq));
        for(int i=0;i<n;i++) d[i]= i==0?0:INF;
        queue<int> Q;
        Q.push(0);
 
        while(!Q.empty())
        {
            int u=Q.front(); Q.pop();
            inq[u]=false;
 
            for(int i=head[u];i!=-1;i=next[i])
            {
                Edge &e=edges[i];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    if(!inq[e.to])
                    {
                        inq[e.to]=true;
                        Q.push(e.to);
                    }
                }
            }
        }
        return d[n-1]-d[9];
    }
}SP;
 
int main()
{
    int n,max_v=-1;
    scanf("%d",&n);
    SP.init();
    while(n--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        b+=10,a+=10;//所有值都加10了,以免a-1成为-1
        max_v=max(max_v,b);
        SP.AddEdge(b,a-1,-c);
    }
    for(int i=10;i<=max_v;i++)//从该循环可看出,本差分约束的点编号为:[9,max_v](未包含超级源0号点)
    {
        SP.AddEdge(i,i-1,0);
        SP.AddEdge(i-1,i,1);
        SP.AddEdge(0,i,0);
    }
    SP.AddEdge(0,9,0);
    SP.n=max_v+1;
    printf("%d\n",SP.spfa());//注意最终结果是d[max_v]-d[9]的值,而不是d[max_v]的单独值
    return 0;
}
```
