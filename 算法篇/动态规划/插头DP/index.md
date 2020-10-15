---
_id: "1b5a45deee"
title: "插头DP"
date: 2020-05-16 09:38
update: 2020-05-16 09:38
author: Rainboy
---

 [入门题目 luogu P5056 【模板】插头dp](https://www.luogu.org/problemnew/show/P5056)
## 题目

 - [uva-11270 Tiling Dominoes](<%- USER.pcs_site %>uva-11270)

## 模板
<!-- template start -->
最小表示法
```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define for0(a, n) for (int (a) = 0; (a) < (n); (a)++)
#define for1(a, n) for (int (a) = 1; (a) <= (n); (a)++)
#define mem(a,x)  memset(a,x,sizeof a)
using namespace std;
const int maxn=12;
const int mod=19993;
typedef long long ll;
typedef pair<ll ,ll>pll;
int cur,nn,mm,n,m,a[maxn+3][maxn+3];
ll ans;
struct Hash
{
    vector<pll>G[mod+3];
    void init()  { for0(i,mod) G[i].clear();}
    void insert(ll s,ll val) //s =state,val数值
    {
        int p=s%mod;
        for0(i,G[p].size())
        {
            if(G[p][i].first==s)  {
                G[p][i].second+=val;return;
            }
        }
        G[p].push_back(make_pair(s,val));
    }

}hashmap[2];

struct Code
{
    int bit[15],tot;
    int ch[15];
    ll s;
    void init(ll x)
    {
        tot=0;
        for0(i,m+1)
        {
           bit[i]=x&7;
           tot=max(tot,bit[i]);
           x>>=3;
        }
        tot++;
    }
    void normalize()
    {
        mem(ch,-1);
        ch[0]=0;tot=1;
        s=0;
        for(int i=m;i>=0;i--)
        {
            if(~ch[bit[i]])  bit[i]=ch[bit[i] ];
            else{
                bit[i]=ch[bit[i] ]=tot++;
            }
            s=(s<<3)+bit[i];
        }
    }
    void color(int a,int b)//a to b
    {
        for0(i,m+1) if(bit[i]==a) bit[i]=b;
    }
    void shift()
    {
        for(int i=m;i>=1;i--) bit[i]=bit[i-1];
        bit[0]=0;
    }

}code;


void updateBlock(int x,int y,ll state,ll val)
{
        if(y==m) code.shift();
        code.normalize();
        hashmap[cur].insert(code.s,val);
}

void updateBlank(int x,int y,ll state,ll val)
{

        const int p=code.bit[y-1];
        const int q=code.bit[y];
        if(!p&&!q)
        {
            if(a[x][y+1]&&a[x+1][y])
            {
                code.bit[y-1]=code.bit[y]=code.tot++;
                code.normalize();
                hashmap[cur].insert(code.s,val);
            }
        }
        else  if(p&&!q||!p&&q)
        {
            int t=p+q;
            if(a[x][y+1])
            {
                code.bit[y-1]=0,code.bit[y]=t;
                code.normalize();
                hashmap[cur].insert(code.s,val);
            }
            if(a[x+1][y])
            {
                code.bit[y-1]=t,code.bit[y]=0;
                if(y==m)  code.shift();
                code.normalize();
                hashmap[cur].insert(code.s,val);
            }
        }
        else
        {
            if(p==q)
            {
                if(x==nn&&y==mm)
                {
                    code.bit[y-1]=code.bit[y]=0;
                    if(y==m)  code.shift();
                    code.normalize();
                    hashmap[cur].insert(code.s,val);
                    ans+=val;
                }
            }
            else
            {
                code.color(p,q);
                code.bit[y-1]=code.bit[y]=0;
                if(y==m)  code.shift();
                code.normalize();
                hashmap[cur].insert(code.s,val);
            }
        }

}
void solve()
{
    ans=cur=0;
    hashmap[cur].init();
    hashmap[cur].insert(0,1);
    for1(i,n)
    {
        for1(j,m)
        {
            cur^=1;hashmap[cur].init();
            for0(k,mod) {
                for0(l,hashmap[cur^1].G[k].size()){
                    pll now=hashmap[cur^1].G[k][l];
                    ll state=now.first,val=now.second;
                    code.init(state);
                    if(a[i][j])  
                        updateBlank(i,j,state,val);
                    else
                        updateBlock(i,j,state,val);
                }
            }
        }
    }
    cout<<ans<<endl;
}
int main()
{
    while(cin>>n>>m)
    {
       mem(a,0);nn=mm=-1;
       char ch;
       for1(i,n) for1(j,m) {
           cin>>ch;
           if(ch=='.')  {
                a[i][j]=1;
                nn=i,mm=j;
           }
       }
       if(nn==-1) {
        puts("0");
        continue;
       }
       solve();
    }
    return 0;
}
/*
2 2
..
..
2 3
...
...
3 2
..
..
..
12 12
............
............
............
............
............
............
............
............
............
............
............
............
*/
```
括号表示法
```c
//括号表示法
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define for0(a, n) for (int (a) = 0; (a) < (n); (a)++)
#define for1(a, n) for (int (a) = 1; (a) <= (n); (a)++)
#define mes(a,x,s)  memset(a,x,(s)*sizeof a[0])
#define mem(a,x)  memset(a,x,sizeof a)
#define ysk(x)  (1<<(x))
typedef long long ll;
typedef pair<ll, ll> pll;
const int INF =0x3f3f3f3f;
const int maxn=12    ;
const int maxV=1e6    ;
const int mod=19993;
int n,m,nn,mm;
int a[maxn+10][maxn+10];
int cur;
int state[2][maxV];
ll sum[2][maxV];
int tot[2],HASH[maxV];
int pre[maxn+10];

void pr()
{
    pre[0]=1;
    for1(i,maxn+3)
    {
        pre[i]=ysk((i<<1));
    }
}

void insert(int S,ll nu)
{
    int p=S%mod;
    while(~HASH[p])
    {
        if(state[cur][HASH[p]]==S)
        {
            sum[cur][HASH[p]]+=nu;
            return;
        }
        if(++p==mod) p=0;
    }
    HASH[p]=tot[cur];
    state[cur][tot[cur]]=S;sum[cur][tot[cur]++]=nu;
}

void show(ll s)
{
    cout<<"show"<<s<<endl;

    for(int i=0;i<=m;i++)
    {
       ll x=s/pre[i];
       x%=4;
       cout<<x;
    }
    cout<<endl;
}
void solve()
{
    ll ans=0;
    cur=0;
    mem(state[cur],0);
    mem(sum[cur],0);
    tot[cur]=0;
    mem(HASH,-1);
    tot[cur]=1;sum[cur][0]=1;
    state[cur][0]=0;

    for1(i,n)
    {
        for1(j,m)
        {
            cur^=1;
            mem(state[cur],0);
            mem(sum[cur],0);
            tot[cur]=0;
            mem(HASH,-1);
//            printf("i=%d,j=%d,tot^1=%d\n",i,j,tot[cur^1]);
            for0(k,tot[1^cur])
            {
                int S=state[1^cur][k];
                ll nu=sum[1^cur][k];
                int p=(S/pre[j-1])%4;
                int q=(S/pre[j])%4;
//                printf("p=%d,q=%d,S=%lld\n",p,q,S);
//                show(S);

                if(!a[i][j])
                {
                     if(!p&&!q) insert(S,nu);
                     continue;
                }

                int S2;
                if(!p&&!q)
                {
                    if(a[i][j+1]&&a[i+1][j])
                    {
                       S2=S+pre[j-1]+2*pre[j] ;
                       insert(S2,nu);
                    }
                }
                else if(!p&&q)// left不存在,up存在
                {
                   if(a[i][j+1]) insert(S,nu); //◳
                   if(a[i+1][j]) //下方的格子存在 ◫
                   {
                      S2=S-q*pre[j]+q*pre[j-1];
                      insert(S2,nu);
                   }

                }
                else if(p&&!q) //left 存在 up不存在
                {
                    if(a[i+1][j])  insert(S,nu); // ◱
                    if(a[i][j+1]) //⊟
                    {
                        S2=S-p*pre[j-1]+p*pre[j];

                        insert(S2,nu);
                    }

                }
                else if(p==1&&q==1) // left,up 都存在 都是（
                {
                    int cnt=1;
                   for(int pp=j+1;pp<=m;pp++) // 修改q对应的）为（
                   {
                       if( (S/pre[pp])%4 ==1  )  cnt++;
                       if( (S/pre[pp])%4 ==2  )  cnt--;
                       if(cnt==0)
                       {
                           S2=S-2*pre[pp]+1*pre[pp];
                           break;
                       }
                   }
                   S2=S2-pre[j-1]-pre[j]; // □
                   insert(S2,nu);
                }
                else if(p==2&&q==2) //都是）
                {
                   int cnt=1;
                   for(int pp=j-2;pp>=0;pp--)// p对应的（ 改成）
                   {
                       if( (S/pre[pp])%4 ==1  )  cnt--;
                       if( (S/pre[pp])%4 ==2  )  cnt++;
                       if(cnt==0)
                       {
                           S2=S+2*pre[pp]-1*pre[pp];
                           break;
                       }
                   }
                   S2=S2-2*pre[j-1]-2*pre[j]; //□
                   insert(S2,nu);

                }
                else if(p==2&&q==1)
                {
                     S2=S-2*pre[j-1]-pre[j]; //□
                     insert(S2,nu);
                }
                else if(p==1&&q==2) // 只有最后一个非障碍格子可以
                {
                    if(i==nn&&j==mm) ans+=nu;
                }


              }

        }
         for(int k=0;k<tot[cur];k++)
         {
             state[cur][k]<<=2;
             while(state[cur][k]>=pre[m+1]) state[cur][k]-=pre[m+1];
         }
    }
    cout<<ans<<endl;

}
int main()
{
   std::ios::sync_with_stdio(false);
   char ch;
   pr();
   while(cin>>n>>m)
   {
       mem(a,0);
       for1(i,n)
       {
           for1(j,m)
           {
               cin>>ch;
               a[i][j]=ch=='.'?1:0;
               if(a[i][j])
               {
                   nn=i,mm=j;
               }
           }
       }
       solve();
   }
   return 0;
}
/*
4 4
**..
....
....
....
*/
/*
1 4
....


1 1
.

1 2
..
2 2
..
..
*/
```
<!-- template end -->

## 参考/引用

 - 基于连通性状态压缩的动态规划问题 长沙市雅礼中学 陈丹琦 
 - [头插DP指北](https://fancydreams.ink/2018/06/20/%E5%A4%B4%E6%8F%92dp%E6%8C%87%E5%8C%97)
