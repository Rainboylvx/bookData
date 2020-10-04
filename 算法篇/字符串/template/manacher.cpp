#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n,m;
char ma[maxn<<1];
int p[maxn<<1];

void Manacher(char s[],int len){
    int l =0;
    ma[l++] = '$';
    ma[l++] = '#';
    for(int i = 0;i<len;i++){
        ma[l++] = s[i];
        ma[l++] = '#';
    }
    ma[l] = 0; //末尾
    int mx = 0,id = 0;
    for(int i =0;i<l;++i){
        p[i] = mx > i ? min(p[2*id-i],mx-i) : 1;
        while( ma[i+p[i]] == ma[i-p[i]]) p[i]++;
        if( i + p[i] > mx){
            mx = i+p[i];
            id = i;
        }
    }

}

int main(){
    char s[]="12212";
    int len = strlen(s);
    Manacher(s,len);
    int ans = 0;
    for(int i=0;i<2*len+2;++i) printf("%c",ma[i]);
    printf("\n");
    for(int i=0;i<2*len+2;++i) printf("%d",p[i]);
    printf("\n");
    for(int i=0;i<2*len+2;++i){
        ans = max(ans,p[i]-1);
    }
    printf("%d\n",ans);
    return 0;
}
