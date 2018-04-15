#include <cstdio>
#include <cstring>

char str[100];
char dest[10] = { '1', '2', '3', '8', '0', '4', '7', '6', '5','\0'};
int dest_num;
char lx[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
bool isExit[10];

bool vis[400000] = {0};

int fx[4][2] ={ {1,0}, {0,1}, {-1,0}, {0,-1} };
int fac[10];


// 找到0的位置
void find0(char map[4][4],int &x,int &y){
    int i,j;
    for(i=1;i<=3;i++)
        for(j=1;j<=3;j++){
            if( map[i][j] == '0'){
                x = i,y = j;
                return ;
            }
        }
}

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



struct _node {
    int state; //存的康托展开后的数字
    int step;
};


//-------------- 队列操作
#define qsize 1000000
_node queue[qsize]; //因为不知道最大步数,使用循环队列
int idx=0;
int head=0,tail =0;

void push(_node t){
    queue[tail]= t;
    tail = (tail+1) % qsize; //tail 最大 qsize-1
}

void pop(){ head = (head+1) % qsize; }
_node front(){ return queue[head];}
bool empty(){ return head == tail;}
//-------------- 队列操作 --- end

bool inmap(int x,int y){
    if(x >=1 && x <=3 && y>=1 && y<=3)
        return true;
    return false;
}
//进行四种操作 state 数字表示的状态,op 表示那个操作,0,1,2,3
int opt(char s[],int op){
    char st[4][4];
    char sst[9];
    int i,j;
    for(i=1;i<=3;i++)
     for(j=1;j<=3;j++)
         st[i][j] = s[(i-1)*3+(j-1)];
    int x,y;
    find0(st,x,y);
    
    int nx = x +fx[op][0];
    int ny = y +fx[op][1];

    if( inmap(nx,ny)){
        char t = st[nx][ny];
        st[nx][ny] = st[x][y];
        st[x][y] = t;
        for(i=1;i<=3;i++)
            for(j=1;j<=3;j++)
                sst[(i-1)*3+(j-1)] =  st[i][j];
        return encoding(sst,9);
    }
    return -1;
}



int bfs(){
    _node first ;

    first.state = encoding(str,9);
    first.step = 0;
    push(first); //加入起点
    vis[first.state]  =1;

    while( !empty()){ //非空
        _node t = front(); pop(); //取出头

        int i;
        int state = t.state;
        int step = t.step;
        char tmp[10];
        decoding(state,9,tmp);
        for(i=0;i<4;i++){
            int tn = opt(tmp,i);
            if( tn != -1){ // 返回一个正常的操作后的状态
                if( tn == dest_num) //找到结果
                    return step+1;
                if ( vis[tn] == 0){ //没有被vis过
                    _node tnode;
                    tnode.state = tn;
                    tnode.step = step+1;
                    push(tnode);
                    vis[tn] = 1;
                }
            }
        }
    }
    return -1; //表示无解
}


int main(){
    fac[0] = 1;
    int i;
    for(i=1;i<=9;i++) fac[i] =  fac[i-1]*i;
    scanf("%s",str);
    if(strcmp(str,dest)==0){
        printf("0");
        return 0;
    }
    dest_num = encoding(dest,9);
    int ans = bfs();

    printf("%d",ans);
    return 0;
}
