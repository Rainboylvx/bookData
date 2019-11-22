// 细节太多 要自己造数据
#include <cstdio>
#include <cstring>



char t[50];
int len;


int flagPos(char s){
    int i;
    for(i=0;i<len;i++)
        if(t[i] == s)
            return i;
    return -1;  // 表示没有
}

void print(int p1,int p2){
    if( p2 == p1)       // 只有一位的时候 直接输出
    {
        printf("%c",t[p1]);
        return ;
    }

    bool flag = false;
    int i;
    for(i=p2;i>=p1;i--){
        if( t[i] != '0') flag = true;
        if( flag) printf("%c",t[i]);
    }

    if(flag == false)
        printf("0");

}


int main(){
    scanf("%s",t);
    len = strlen(t);

    int isX = flagPos('.');
    if( isX != -1){

        print(0,isX-1);
        printf(".");

        // 去除开始的 0
        int i;
        for(i=isX+1;i<=len-1;i++)
            if( t[i] != '0')
                break;

        print(i,len-1);
        return 0;
    }

    int isF = flagPos('/');
    if( isF != -1){
        print(0,isF-1);
        printf("/");
        print(isF+1,len-1);
        return 0;
    }

    if( t[len-1] == '%'){
        print(0,len-2);
        printf("%%");
        return 0;
    }

    print(0,len-1);
    return 0;
}
