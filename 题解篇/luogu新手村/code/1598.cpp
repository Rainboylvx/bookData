#include <cstdio>
#include <cstring>


char line[105];

char tongji[500][500];
int max_cnt = 0;
char maxn_c;
void add_char(char c){
    int p = c- 'A';
    int cnt = ++tongji[0][p];
    tongji[cnt][p] = '*';
    if( max_cnt < cnt){
        max_cnt= cnt;
        maxn_c = c;
    }
}

int main(){
    memset(tongji,' ',sizeof(tongji)); //全部置为空格
    memset(tongji,0,sizeof(tongji[0])); //第0行置为0


    int i,j;
    for(i=1;i<=4;i++){
        memset(line,0,sizeof(line));
        fgets(line,sizeof(line),stdin); //读取一行
        //printf("%s\n",line);
        int len = strlen(line);
        for(j=0;j<len;j++){
            if( line[j] >='A' && line[j] <='Z')
                add_char(line[j]);
        }
    }
    //printf("%d\n",max_cnt);
    //printf("%c%d\n",maxn_c,maxn_c);

    for(i=max_cnt;i>=1;i--){
        for(j=0;j<26;j++){
            printf("%c ",tongji[i][j]);
        }
        printf("\n");
    }

    for(i='A';i<='Z';i++){
        printf("%c ",i);
    }

    return 0;
}

