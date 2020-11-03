struct Random {
    random_device rd;
    mt19937 engine{rd()};
    uniform_int_distribution<> dis;
    Random(){}
    Random(int l,int r){ dis = uniform_int_distribution<> (l,r); }
    int operator()(){ return dis(engine); }
};


struct Fhq {
    typedef struct {int val,fix,sz,c[2];} node;
    node tr[maxn];
    Random rnd;
    int root,x,y,z,idx=0,top=0,s[maxn];
    inline int &lc(int p){ return tr[p].c[0];}
    inline int &rc(int p){ return tr[p].c[1];}
    inline int &c(int p,int i){ return tr[p].c[i];}
    inline int &fix(int p){return tr[p].fix;}
    inline int &sz(int p){return tr[p].sz;}
    inline int &va(int p){return tr[p].val;}

    inline int New(int v){
        tr[++idx] = {v,rnd(),1,{0,0}};
        return idx;
    }

    inline void pushup(int p){
        sz(p) = sz(lc(p))+sz(rc(p))+1;
    }

    // 按v分裂
    void split(int p,int v,int &x,int &y){
        if( !p ) { x = y = 0; return; }
        //这个点应该在左边
        if(va(p) <= v)  split(rc(x=p),v,rc(p),y);
        else            split(lc(y=p),v,x,lc(p));
        pushup(p);
    }

    //合并
    int merge(int x,int y){
        if( !x || !y) return x+y;
        int u;
        if( fix(x) > fix(y) ) rc(u = x) = merge(rc(x), y);
        else lc(u = y) = merge(x,lc(y));
        pushup(u);
        return u;
    }

    //插入
    void ins(int v){
        split(root,v,x,y);
        root = merge(merge(x,New(v)), y);
    }
    void del(int v){
        split(root,v,x,z);
        split(x,v-1,x,y);
        y = merge(lc(y), rc(y));
        root = merge(merge(x,y),z);
    }
    int Rank(int v){
        split(root,v-1,x,y);
        int ans = sz(x)+1;
        root = merge(x,y);
        return ans;
    }
    int at(int p,int rank){
        while(p){
            if( sz(lc(p))+1 == rank) break;
            else if( sz(lc(p)) >= rank)  p = lc(p);
            else rank -= sz(lc(p))+1,p = rc(p);
        }
        return p;
    }

    int pre(int v){
        split(root, v-1, x, y);
        int p = at(x,sz(x));
        root = merge(x, y);
        return va(p);
    }

    int next(int v){
        split(root,v,x,y);
        int p = at(y,1);
        root = merge(x, y);
        return va(p);
    }
} fhq;
