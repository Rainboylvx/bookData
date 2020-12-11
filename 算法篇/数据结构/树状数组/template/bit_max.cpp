struct Bit_max {
    T a[maxn],c[maxn]; // a是原数组
    comp com;
    inline int lowbit(T x) { return x & -x;      }
    inline int fa(int p)   { return p+lowbit(p); }
    inline int left(int p) { return p-lowbit(p); }
    inline T g(T a ,T b) { return com(a,b) ? a : b;}
    void update_by_child(int p,T v){ //alias push
        c[p] = a[p] = v;
        int lb = lowbit(p);
        for(int i=1;i < lb ;i <<= 1)
            c[p] = g(c[p],c[p-i]);
    }

    void update(int p,T v){
        update_by_child(p, v);
        T t = c[p];
        for( p = fa(p); p<=N ; p = fa(p)){
            if( com(t,c[p]) ) c[p] = t;
            else break;
        }
    }

    T query(int l,int r){ // 求区间最值
        T ret = a[l];
        for( ; l <=r; ){
            int next = left(r)+1;
            if( next >= l ) ret = g(ret,c[r]) , r = next-1;
            else            ret = g(ret,a[r]) , r--;
        }
        return ret;
    }
};
Bit_max<ll> bit;
