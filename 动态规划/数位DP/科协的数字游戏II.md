Description
 由于科协里最近真的很流行数字游戏。（= =！汗一个）某人又命名了一种取模数，这种数字必须满足各位数字之和 mod N为0。现在大家又要玩游戏了，指定一个整数闭区间[a,b]，问这个区间内有多少个取模数。

Input
题目有多组测试数据。每组只含3个数字a, b, n (1 <= a, b <= 2^31,1 <= n < 100)。
Output
每个测试用例输出一行，表示各位数字和 mod N为0 的数的个数。
Sample Input
1 19 9
Sample Output
2
Hint
Source
tclh123

todo!!??
```c
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int dp[100][111],bit[100],a,b,n;

int dfs(int pos,int res,bool limit)
{
    if(pos==-1)
        return res==0;
    if(!limit&&~dp[pos][res]) return dp[pos][res];
    int end=limit?bit[pos]:9;
    int ans=0;
    for(int i=0;i<=end;i++)
    {
        int newres=(res+i)%n;
        ans+=dfs(pos-1,newres,limit&&(i==end));
    }
    if(!limit)
        dp[pos][res]=ans;
    return ans;
}

int cal(int x)
{
    int len=0;
    while(x)
    {
        bit[len++]=x%10;
        x/=10;
    }
    return dfs(len-1,0,true);
}

int main()
{
    while(scanf("%d%d%d",&a,&b,&n)!=EOF)
    {
        memset(dp,-1,sizeof(dp));
        printf("%d\n",cal(b)-cal(a-1));
    }
    return 0;
}
```
