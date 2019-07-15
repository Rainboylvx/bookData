#include <bits/stdc++.h>
using namespace std;

int n;
int a[100005];

int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);
    for (i=1;i<=n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}
