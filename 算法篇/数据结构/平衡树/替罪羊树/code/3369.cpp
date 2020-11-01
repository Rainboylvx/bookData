// ScapeGoatTree 替罪羊模板
/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 10月 31日 星期六 09:36:04 CST */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量
int n,m;


struct ScapeGoatTree {
    //v 点值 | sz size 子树点数 | rs realsize 子树大小 | cn cnt当前点的数量 | c[2] child[2] 左右孩子
    typedef struct { int v,sz,rs,cn,c[2]; } node; 
    node tr[maxn];
    int root,idx=0,dc=0,top=0,sta[maxn]; // dc = delele count
    int fl[maxn],flcn=0;
    inline int &lc(int p) { return tr[p].c[0];}
    inline int &rc(int p) { return tr[p].c[1];}
    inline int &c(int p,int i){return tr[p].c[i];};
    inline int &sz(int p) { return tr[p].sz;}
    inline int &cn(int p) { return tr[p].cn;}
    inline int &va(int p) { return tr[p].v;}
    inline int &rs(int p) { return tr[p].rs;}

    inline void flpush(int p){ fl[++flcn] = p; }
    // 是否平衡
    bool Imb(int p){ return max(rs(lc(p)),rs(rc(p)))-5 > rs(p)*0.75; }
    //bool Imb(int p){ return max(rs(lc(p)),rs(rc(p)))-1 > rs(p)*0.6; }
    void New(int &p,int val){ tr[p = ++idx] = {val,1,1,1,{0,0}}; }
    //void New(int &p,int fa,int val){ tr[p = ++idx] = {val,1,1,1,fa,{0,0}}; }

    void pushup(int p){
        sz(p) = sz(lc(p)) + sz(rc(p)) + cn(p); 
        rs(p) = rs(lc(p)) + rs(rc(p)) + 1; 
    }
    void dfs(int p){
        if(!p) return;
        dfs(lc(p));
        if( cn(p)) sta[++top] = p;
        else dc--;
        dfs(rc(p));
    }
    void Build(int l,int r,int &p){
        if( l > r) { p = 0; return; };
        if( l == r) {
            p = sta[l];
            rs(p)=1;
            rc(p)=lc(p)=0;
            sz(p)=cn(p);
            return;
        }
        int m = (l+r) >> 1;
        p = sta[m];
        Build(l,m-1,lc(p));
        Build(m+1,r,rc(p));
        pushup(p);
    }
    void Rebuild(int &p){
        top = 0;
        dfs(p);
        Build(1,top,p);
    }
    int find(int v){
        int p = root; flcn =0;
        while(c(p,v > va(p))  && v != va(p) ){
            flpush(p);
            p = c(p,v > va(p));
        }
        flpush(p);
        return p;
    }
    void ins(int v){
        if(!root){
            New(root,v);
            return;
        }
        int p = find(v);
        if( va(p) == v) cn(p)++;
        else New(c(p,v>va(p)), v);

        int bba = -1;
        for(int i=flcn;i>=1;--i){
            pushup(fl[i]);
            if( Imb(fl[i])) bba = i;
        }
        if( ~bba){
            if( bba == 1) Rebuild(root);
            else {
                Rebuild( c(fl[bba-1],va(fl[bba]) > va(fl[bba-1])) );
                for(int i =bba-1;i>=1;--i) pushup(fl[i]);
            }
        }
    }

    void del(int v){
        int p = find(v);
        if(va(p) != v || !p ) return; //没有找到这个点
        if(!--cn(p)) dc++; //这个点删空了,计数
        if(dc> sz(root)) Rebuild(root);
        else  //更新链上的值
            for(int i = flcn ;i>=1;--i) pushup(fl[i]);
    }
    // 每一次向右走，排名都会增加
    // 边界1: va(p) != p 但已经不向下走了，
    //          还要加上lc(p)的数量
    //          如果va(p) < v 还加上cn(p)
    // 边界2: va(p) == v 还要加上lc(p)的数量
    int Rank(int v){ //得到v的排名
        int p = root , ans = 1;
        while( va(p) != v && c(p,v>va(p)) ){
            if( v > va(p)) ans += sz(lc(p)) + cn(p);
            p = c(p,v > va(p));
        }
        return ans + sz(lc(p)) + ( va(p) < v ? cn(p) : 0);
    }

    // 得到排名为k的值
    // 排名树的数量是 sz(lc(p))
    // 排名为k的数在左子树上： sz(lc(p)) >= k
    // 排名为k的数在右子树上： sz(lc(p)) + cn(p) < k
    // 排名为k的数在当前点上： 不满足上面的两个条件
    int at(int k){
        int p = root;
        while( p ){
            if( sz(lc(p)) >= k ) p = lc(p);
            else if ( sz(lc(p)) + cn(p) < k)
                k -= sz(lc(p)) + cn(p), p = rc(p);
            else break;
        }
        return p;
    }
    // pre  前趋
    // 得到v的排名k
    // 得到排名为k-1的数
    // 1 2 2 2 5
    // 1 2     5
    // rank(5) == rank(4) == rank(3)
    // at(rank(5-1)) = 5
    inline int pre(int v){
        return va(at(Rank(v)-1));
    }
    // next 后继
    // 得到的v+1的排名，
    // 1 2 2 2 5
    // 1 2     5 rank 显然应该Rank(v+1)
    // rank(2)+1 = 5
    // rank(3)+1 = 6
    // rank(4)+1 = 6
    // Rank(2) = 2 Rank(3) = 5 at(Rank(2)+1) = 2
    inline int next(int v){
        return va(at(Rank(v+1)));
    }
};

ScapeGoatTree scgt;

void print_scgt(){
    printf("root = %d\n",scgt.root);
    printf("%4s %10s %4s %4s %4s %4s %4s\n", "n", "va","sz", "rs","cn","lc","rc");
    for(int i=1;i<=scgt.idx;++i){
        printf("%4d %10d %4d %4d %4d %4d %4d\n",i,scgt.va(i),scgt.sz(i),scgt.rs(i),scgt.cn(i),scgt.lc(i),scgt.rc(i));
    }
}

int main(){
    scanf("%d",&n);
    int i,j,t;
    for(i=1;i<=n;++i){
        int o,t;
        scanf("%d%d",&o,&t);
        int d;
        switch(o){
            case 1:
                scgt.ins(t);
                break;
            case 2:
                scgt.del(t);
                break;
            case 3:
                d = scgt.Rank(t);
                printf("%d\n",d);
                break;
            case 4:
                d = scgt.at(t);
                printf("%d\n",scgt.va(d));
                break;
            case 5:
                d = scgt.pre(t);
                printf("%d\n",d);
                break;
            case 6:
                d = scgt.next(t);
                printf("%d\n",d);
                break;
        }

        //printf("%d\n",i);
        //print_scgt();
        //printf("=================\n");
    }
    return 0;
}
