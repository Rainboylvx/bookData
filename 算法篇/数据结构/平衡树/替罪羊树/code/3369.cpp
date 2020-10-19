#include <bits/stdc++.h>
using namespace std;

/* ======= 全局变量 =======*/
const int maxn = 1e5+5;
const double alpha = 0.75;//α
const double del_alpha = 0.3;
const int base_node = 5;
int n,m;

/* ======= 全局变量 END =======*/
void init(){
}


/* ======= 替罪羊树 ======= */
struct Node {
    int l,r,val; //左右孩子,值
    int size,fact;//大小,实际大小
    bool exist; //是否存在/删除
};
Node tzy[maxn]; //树结点
int cnt,root;
/* 加入新的结点 */
void newnode(int &now,int val){
    now = ++cnt;
    tzy[now].val = val;
    tzy[now].size = tzy[now].fact=1;
    tzy[now].exist = true;
}

/* 是否平衡 */
bool imbalence(int now){
    if(     max(tzy[tzy[now].l].size , tzy[tzy[now].r].size) > tzy[now].size*alpha + base_node
        ||tzy[now].size - tzy[now].fact > tzy[now].size*del_alpha +5)
        return true;
    return false;
}

vector<int> v;
/* 中序遍历 */
void middle_sort(int now){
    if(!now ) return;
    middle_sort(tzy[now].l);
    if( tzy[now].exist)
        v.push_back(now);
    middle_sort(tzy[now].r);
}

/* 分治重建 */
void lift(int l,int r,int &now){
    if(l == r){ //叶子结点
        now = v[l];
        tzy[now].l = tzy[now].r = 0;
        tzy[now].size = tzy[now].fact = 1;
        return ;
    }
    int m =(l+r)>> 1;

    /* >=key 放右方 */
    while( l < m && tzy[v[m]].val == tzy[v[m-1]].val) m--;
    now=v[m];
    /* 如果左区间还存在 */
    if( l < m ) lift(l, m-1, tzy[now].l);
    else tzy[now].l = 0;
    /* 右区间一定存在 */
    lift(m+1,r,tzy[now].r);

    tzy[now].size = tzy[ tzy[now].l ].size + tzy[ tzy[now].r ].size+1;
    tzy[now].fact = tzy[ tzy[now].l ].fact + tzy[ tzy[now].r ].fact+1;
}

/* 重建 */
void rebuild(int &now){
    v.clear(); // 清空中序序列
    middle_sort(now);
    if( v.empty()){ //中序后,为空
        now = 0;
        return;
    }
    lift(0,v.size()-1,now);
}

/* 更新一条链 */
void update(int now,int end){
    if(!now) return;
    if( tzy[end].val < tzy[now].val){
        update(tzy[now].l, end);
    }
    else update(tzy[now].r, end);
    tzy[now].size = tzy[ tzy[now].l ].size + tzy[ tzy[now].r ].size+1;
}

void check(int &now,int end){
    if( now == end) return;
    if( imbalence(now)){
        rebuild(now);
        update(root, now);
        return;
    }
    if( tzy[end].val < tzy[now].val)
        check(tzy[now].l, end);
    else check(tzy[now].r, end);
}

/* 插入 */
void ins(int &now,int val){
    if(!now){
        newnode(now, val);
        check(root,now);
        return;
    }
    tzy[now].size++;
    tzy[now].fact++;
    if( val < tzy[now].val)
        ins(tzy[now].l,val);
    else
        ins(tzy[now].r,val);
}

/* 删除 */
void del(int now,int val){
    if(tzy[now].exist && tzy[now].val == val){
        tzy[now].exist = false;
        tzy[now].fact--;
        check(root, now);
        return;
    }
    tzy[now].fact--;
    if( val < tzy[now].val)
        del(tzy[now].l,val);
    else
        del(tzy[now].r,val);
}

/* 得到排名 */
int getrank(int val){
    int now  = root,rank=1;
    while(now) {
        if( val <= tzy[now].val)
            now = tzy[now].l;
        else{
            rank+= tzy[now].exist + tzy[ tzy[now].l ].fact;
            now = tzy[now].r;
        }
    }
    return rank;
}

/* 得到排名 rank的 值 */
int getnum(int rank){
    int now = root;
    while(now) {
        if( tzy[now].exist && tzy[ tzy[now].l ].fact + tzy[now].exist == rank)
            break;
        else if( tzy[tzy[now].l].fact >= rank)
            now = tzy[now].l;
        else {
            rank -= tzy[tzy[now].l].fact + tzy[now].exist;
            now = tzy[now].r;
        }
    }
    return tzy[now].val;
}

/* ======= 替罪羊树 END======= */


int main(){
    clock_t program_start_clock = clock(); //开始记时
    //===================
    int t;
    scanf("%d",&t);
    while (t--) {
        int opt,x;
        scanf("%d%d",&opt,&x);
        int ans;
        switch(opt){
            case 1:
                ins(root, x);
                break;
            case 2:
                del(root,x);
                break;
            case 3:
                ans = getrank(x);
                printf("%d\n",ans);
                break;
            case 4:
                ans = getnum(x);
                printf("%d\n",ans);
                break;
            case 5:
                ans = getnum( getrank(x)-1);
                printf("%d\n",ans);
                break;
            case 6:
                ans = getnum( getrank(x+1));
                printf("%d\n",ans);
                break;
        }
    }

    //=================== 
    fprintf(stderr,"\n Total Time: %lf ms",double(clock()-program_start_clock)/(CLOCKS_PER_SEC / 1000));
    return 0;
}
