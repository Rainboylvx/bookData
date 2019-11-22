#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,s,a,b,c,ans;
int w[30000];
int main(){
    scanf("%d%d%d%d",&n,&s,&a,&b);
    a+=b; //最大高度
    for(int i=1;i<=n;i++){
        scanf("%d%d",&b,&c); //过滤 留下能拿到的苹果
        if(b<=a) w[++m]=c;
    }
    sort(w+1,w+m+1); //排序
    for(int i=1;i<=m;i++){
        if(w[i]>s) break;
        s-=w[i];
        ++ans;
    }
    printf("%d\n",ans);
    return 0;
}
