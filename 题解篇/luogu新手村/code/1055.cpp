#include <cstdio>
#include <cstring>

char isbn[100];

int char2num(char a){
    return a-'0';
}


int main(){
    scanf("%s",&isbn[0]);
    int ans = 0;
    ans += char2num(isbn[0]) * 1;
    ans += char2num(isbn[2]) * 2;
    ans += char2num(isbn[3]) * 3;
    ans += char2num(isbn[4]) * 4;
    ans += char2num(isbn[6]) * 5;
    ans += char2num(isbn[7]) * 6;
    ans += char2num(isbn[8]) * 7;
    ans += char2num(isbn[9]) * 8;
    ans += char2num(isbn[10]) * 9;
    int code;
    if( isbn[12] == 'X')
        code = 10;
    else 
        code = char2num(isbn[12]);

    if( code == ans % 11){
        printf("Right");
        return 0;
    }

    isbn[12] = '\0';
    printf("%s",isbn);

    if( ans % 11 == 10)
        printf("X");
    else
        printf("%d\n",ans%11);
    return 0;
}
