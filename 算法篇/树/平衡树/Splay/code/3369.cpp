/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 17日 星期日 15:26:49 CST problem:  luogu-3369
*----------------*/
#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e5+5;
int n;
/* ======= 全局变量 END =======*/

/* ========== 快读 ========== */
void in(int &a){
    a = 0;
    int flag = 1;
    char ch = getchar();
    while( ch < '0' || ch > '9'){ if( ch == '-') flag = -1; ch = getchar(); }
    while( ch >= '0' && ch <= '9'){ a = a*10 + ch-'0'; ch = getchar(); }
    a = a*flag;
}
/* ========== 快读 END ========== */

struct Node
{
    int fa,ch[2],val,cnt,size;  //ch[0]是左儿子，ch[1]是右儿子
}spl[maxn];
int cnt,root; //内存池计数,根编号

//新建节点，要注意fa指针的初始化
void newnode(int &now,int fa,int val)
{
    spl[now=++cnt].val=val;
    spl[now].fa=fa;
    spl[now].size=spl[now].cnt=1;
}

bool ident(int x,int f){ return spl[f].ch[1] == x; }

void connect(int x,int fa,int ch){
    spl[x].fa = fa;
    spl[fa].ch[ch] = x;
}

inline void push_up(int x){
    spl[x].size=spl[spl[x].ch[0]].size+spl[spl[x].ch[1]].size+spl[x].cnt;
}

void rotate(int x)      //合二为一的旋转
{
    // f:父亲,ff:祖父,k:x是父亲的那个孩子
    int f=spl[x].fa,ff=spl[f].fa,k=ident(x,f);
    connect(spl[x].ch[k^1],f,k);        //x的孩子作为父亲f的孩子
    connect(x,ff,ident(f,ff));          //x作为祖父的孩子
    connect(f,x,k^1);                   //f作为x的孩子
    push_up(f),push_up(x);                //别忘了更新大小信息
}

void splaying(int x,int top)//代表把x转到top的儿子，top为0则转到根结点
{
    // !top => top == 0
    if(!top) 
        root=x; //改变根结点
    while(spl[x].fa!=top) //
    {
        int f=spl[x].fa,ff=spl[f].fa;
        //祖父不是目的结点,要旋转两次,因为有三个点
        if(ff!=top) 
            rotate( ident(f,ff)^ident(x,f)? x : f );
            //直线:旋转父亲
            //之字:旋转自己
        rotate(x);      //最后一次都是旋转自己
    }
}

// fa默认为0,now默认为root
void ins(int val,int &now=root,int fa=0)    //递归式，要传fa指针
{
    if(!now) //当前是空结点,建立,伸展到root
        newnode(now,fa,val),splaying(now,0);
    else if(val<spl[now].val) //去左子树
        ins(val,spl[now].ch[0],now);
    else if(val>spl[now].val) //去右子树
        ins(val,spl[now].ch[1],now);
    else //相等,计数+1,伸展到root
        spl[now].cnt++,splaying(now,0);
}

void delnode(int x)
{
    splaying(x,0);//把x伸展到root
    if(spl[x].cnt>1) spl[x].cnt--;//计数-1
    else if(spl[x].ch[1]) //存在右子树
    {
        int p = spl[x].ch[1];//p 右子树编号
        //p 右子树中的最小值
        while(spl[p].ch[0]) p=spl[p].ch[0];
        splaying(p,x);//p 伸展到 x的孩子

        //x的左孩子,变p的左孩子
        connect(spl[x].ch[0],p,0);
        root=p;//根变p
        spl[p].fa=0;//根的父亲
        push_up(root);//更新size
    } // 只存在左子树,直接做
    else root=spl[x].ch[0],spl[root].fa=0;
}

void del(int val,int now=root)
{
    if(val==spl[now].val) delnode(now);
    else if(val<spl[now].val) del(val,spl[now].ch[0]);
    else del(val,spl[now].ch[1]);
}

//以下与替罪羊树同

//得到值val的rank(排名)
int getrank(int val)
{
    int now=root,rank=1;
    while(now)
    {
        if(val ==spl[now].val){
            rank+=spl[spl[now].ch[0]].size;
            splaying(now,0);
            break;

        } //去左子树
        else if(val<spl[now].val)
            now=spl[now].ch[0]; 
        else //去右子树
        {
            rank+=spl[spl[now].ch[0]].size+spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return rank;
}

//得到rank(排名)的值
int atrank(int rank)
{
    int now=root;
    while(now)
    {
        int lsize = spl[spl[now].ch[0]].size;
        if( rank >= lsize+1 &&  rank <= lsize+spl[now].cnt){
            splaying(now, 0);
            break;
        }

        else if(lsize>=rank) // 在左边
            now=spl[now].ch[0];
        else // 在右边
        {
            rank-= lsize+ spl[now].cnt;
            now=spl[now].ch[1];
        }
    }
    return spl[now].val;
}


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    in(n);
    int opt,x;
    while(n--){
        in(opt),in(x);
        switch(opt){
            case 1: //insert
                ins(x);
                break;
            case 2: //del
                del(x);
                break;
            case 3: //getrank
                printf("%d\n",getrank(x));
                break;
            case 4: //atrank
                printf("%d\n",atrank(x));
                break;
            case 5: //pre
                printf("%d\n",atrank(getrank(x)-1));
                break;
            case 6: //nxt
                printf("%d\n", atrank(getrank(x+1)));
                break;
        }
    }
    

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
