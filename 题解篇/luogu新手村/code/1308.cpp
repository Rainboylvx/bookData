#include <cstdio>
#include <cstring>

char word[100];
char word2[100000];
int idx = 0;
int pos= 0;
int cnt = 0;
bool first_flag = false;
int first;
char _tolower(char c){
    if( c >='A' && c <='Z')
        return c-'A' +'a';
    else if(c >='a' && c <='z')
        return c;
    else
        return ' ';
}
void tolower(char a[]){
    int l = strlen(a);
    int i;
    for (i=0;i<l;i++){
        if( a[i] >='A' && a[i] <='Z')
            a[i] = a[i]-'A' +'a';
    }
}
char tmp[1000];
int p = 0;
int next_word(){
    memset(tmp,0,sizeof(tmp));
    bool is_begin_blank = true;
    int tmp_idx = 0;
    while(1){
        char c = word2[p];
        if( c == ' ' && is_begin_blank){
            p++;
            continue;
        }
        if( p >= idx) return -1;
        if( c == ' ' && !is_begin_blank ){
            break;
        }
        if( c != ' '){
            tmp[tmp_idx++] = word2[p++];
            is_begin_blank=  false;
        }
    }
    return p-1;
}

int main(){
    scanf("%s",word);
    tolower(word);
    char t;
    scanf("%c",&t);
    while( scanf("%c",&t) !=EOF){
        if( t == '\n'){
            word2[idx++] = ' ';
            break;
        }
        word2[idx++] = _tolower(t);
    }
    int i,j;

    int pos = -1;
    while(1){
        int ans = next_word();
        if( ans == -1)
            break;
        if(strcmp(word,tmp) == 0){
            cnt++;
            if( pos == -1){
                int l = strlen(tmp);
                pos = ans-l+1;
            }
        }
    }
    if( cnt == 0)
        printf("-1");
    else
        printf("%d %d",cnt,pos);
    return 0;
}
