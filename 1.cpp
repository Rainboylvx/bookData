/*============================================================================
* Title : 康托展开 ver1.0
* Author: Rainboy
* Time  : 2016-06-03 17:49
* update: 2018-04-15 09:54
* © Copyright 2016 Rainboy. All Rights Reserved.
*=============================================================================*/
#include <cstdio>
#include <cstring>

/* 在我们用char 类型的数组的时候,把它定义的比实际使用的大一点
  (不然有可能会出现各种莫名奇妙的错误),因为
    字符串的末尾是'\0' 实际长度比较长一个单位,
*/
char str[100] = {'3','1','2','4','5','6','7','8'};


// 有序的原数组,从小到大排序
char lx[100] = {'1','2','3','4','5','6','7','8'};
bool isExit[10];

// 存 阶乘的值
int fac[10];

//康托展开
/*str 字符串,strlen 总长度*/
int encoding(char str[],int len){
    int num =0,i,j;
    for(i=0;i<len;i++){
        int tmp = 0;
        for(j=i+1;j<len;j++)   //从后面一个数开始,计算有几个数
            if(str[j] < str[i])//比str[i]小,如果有0个比str[i]
                tmp++;         //str[i]就是第0小
        num += tmp*fac[len-i-1];
    }
    return num;
}

//逆展开
void decoding(int num,int len,char str[]){
    memset(isExit,0,sizeof(isExit));
    int i,j,cnt;
    for(i=0;i<len;i++){
        int y = num / fac[len-i-1];//需要找第y小的数
        num = num % fac[len-i-1];

        //从存在的数里找到
        cnt = -1; //找到一个数后,cnt++ == 0 表示第0小
        for(j=0;j<len;j++){
            if(isExit[j] == 0) { //存在
                cnt++;
                if(cnt == y) //
                    break;
            }
        }

        isExit[j] = 1;
        str[i] = lx[j];
    }
}

int main(){
    int i,j;
    fac[0] =1;
    for(i=1;i<=8;i++)
        fac[i] = fac[i-1]*i;
    int ans = encoding(str,8);
    printf("%d\n",ans);
    char tmp[10] ={0};
    decoding(ans,8,tmp);
    printf("%s",tmp);
    return 0;
}
