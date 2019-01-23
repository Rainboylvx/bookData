
## 题目

题目地址:[hdu 3652 B-number](https://vjudge.net/problem/HDU-3652)

题意：找出1~n范围内含有13并且能被13整除的数字的个数

思路：使用记忆化深搜来记录状态，配合数位DP来解决

todo!!!

先找规律

$$f[i][j][k]$$表示位数为$$i$$,最低位为$$j$$且对13的余数为$$k$$的数字的个数.

```math
f[i][j][k] = \sigma (f[i-x][l][a] &&f[x][m][b]),f[i]
```

## 代码


```c
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
int bit[15];
int dp[15][15][3];
//dp[i][j][k]
//i:数位
//j:余数
//k:3种操作状况，0：末尾不是1,1：末尾是1,2：含有13
 
int dfs(int pos,int mod,int have,int lim)//lim记录上限
{
    int num,i,ans,mod_x,have_x;
    if(pos<=0)
        return mod == 0 && have == 2;
    if(!lim && dp[pos][mod][have] != -1)//没有上限并且已被访问过
        return dp[pos][mod][have];
    num = lim?bit[pos]:9;//假设该位是2，下一位是3，如果现在算到该位为1，那么下一位是能取到9的，如果该位为2，下一位只能取到3
    ans = 0;
    for(i = 0; i<=num; i++)
    {
        mod_x = (mod*10+i)%13;//看是否能整除13，而且由于是从原来数字最高位开始算，细心的同学可以发现，事实上这个过程就是一个除法过程
        have_x = have;
        if(have == 0 && i == 1)//末尾不是1，现在加入的是1
            have_x = 1;//标记为末尾是1
        if(have == 1 && i != 1)//末尾是1，现在加入的不是1
            have_x = 0;//标记为末尾不是1
        if(have == 1 && i == 3)//末尾是1，现在加入的是3
            have_x = 2;//标记为含有13
        ans+=dfs(pos-1,mod_x,have_x,lim&&i==num);//lim&&i==num，在最开始，取出的num是最高位，所以如果i比num小，那么i的下一位都可以到达9，而i==num了，最大能到达的就只有,bit[pos-1]
    }
    if(!lim)
        dp[pos][mod][have] = ans;
    return ans;
}
 
int main()
{
    int n,len;
    while(~scanf("%d",&n))
    {
        memset(bit,0,sizeof(bit));
        memset(dp,-1,sizeof(dp));
        len = 0;
        while(n)
        {
            bit[++len] = n%10;
            n/=10;
        }
        printf("%d\n",dfs(len,0,0,1));
    }
 
    return 0;
}
```

