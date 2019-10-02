/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 09月 11日 星期三 15:25:38 CST
* problem: hdu-2610
*----------------*/
#include <bits/stdc++.h>
using namespace std;

int n,p;
int a[1005];
int choose[1005] ={0};
int choose_pos[1005] = {0};
int cnt=0; //已经输出的序列
bool find_flag;


/* dep 已经选了多少数
 * p 当前位置
 * length 要得到的长度
 * */
void dfs(int dep,int pos,int length){
    if( cnt >= p) return;   //输出的超过题目的要求

    if(dep-1 == length){      // 边界
        find_flag = true;
        int i;
        for (i=1;i<dep-1;i++){
            printf("%d ",choose[i]);
        }
        printf("%d\n",choose[dep-1]);
        cnt++;
        return; 
    }

    int i;
    for(i=pos;i<=n;i++){
        if( a[i] >= choose[dep-1] ){
            int j;
            bool flag = false;
            if( dep == 1){ //情况1
                for(j=1;j< i;j++){
                    if( a[j] == a[i]){
                        flag = 1;
                        break;
                    }
                }
            }
            else {
                for( j=choose_pos[dep-1]+1;j<i;j++){    //情况2
                    if( a[j] == a[i]){
                        flag = 1;
                        break;
                    }
                }
            }
            if( flag ) continue;
            choose[dep] = a[i];
            choose_pos[dep] = i;
            dfs(dep+1,i+1,length);
        }
    }
}

void init(){
    cnt = 0;
    memset(choose,0,sizeof(choose));
    choose[0] = -0x7f7f7f7f;
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
}
int main(){
    while (scanf("%d%d",&n,&p) != EOF) {
        init();
        int i;
        for (i=1;i<=n;i++){
            find_flag = false;
            dfs(1,1,i);
            /* 优化 */
            if( cnt >= p || !find_flag)
                break;
        }
        printf("\n");
    }
    return 0;
}
