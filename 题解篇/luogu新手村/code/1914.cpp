#include <cstdio>
#include <cstring>


int n;
char a[100];

char str[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

int main(){
    scanf("%d",&n);
    int i,j;
    /* 
     * 0->a
     * */
    scanf("%s",a);
    int len = strlen(a);
    for(i=0;i<len;i++){
        char c = a[i];
        int p  = c - 'a';
        p += n;
        p %= 26;
        printf("%c",str[p]);
    }


    return 0;
}

