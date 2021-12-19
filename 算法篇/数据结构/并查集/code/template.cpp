template<int size>
struct DisjointSet {
    int fa[size+5];
    DisjointSet() { 
        for(int i=0;i<=size+4;++i)
            fa[i] = i;
    }
    int find(int u){
        if( u  == fa[u]) return u;
        return fa[u] = find(fa[u]);
    }
    inline void un(int u,int v){
        fa[find(u)] = find(v);
    }
};
