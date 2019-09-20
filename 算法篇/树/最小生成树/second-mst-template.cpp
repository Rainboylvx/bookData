/* 边集数组 */
struct _e{
    long long u,v,w,vis; //vis 是否是mst上的边
}e[maxm<<1];

//G[i] 表示集合i上的点
vector<int> G[maxn];

long long second_mst(){
    long long mst,second_mst=0x7fffffffffffffff;
    int i,j,k=0;
    /* 初始化 并查集 */
    for (i=1;i<=n;i++){
        fa_bcj[i] = i;
        G[i].push_back(i);
    }

    for(i=1;i<=m;i++){
        int f1 = find(e[i].u);
        int f2 = find(e[i].v);
        if( f1 != f2){
            mst += e[i].w;
            fa_bcj[f1] = f2;
            e[i].vis = 1; // 这条边在 MST 上

            /* 求maxd*/
            long long &u = e[i].u,&v = e[i].v,&w = e[i].w;

            for( auto x1 : G[f1]){
                for( auto x2 : G[f2]){
                    maxd[x1][x2] = maxd[x2][x1] = w;
                }
            }

            /* 把集和 f1 合并到f2 上,不在关心f1集合*/
            G[f2].insert( G[f2].end(),G[f1].begin(),G[f1].end());

            k++;
            if( k == n-1) break; //选n-1条边
        }
    }

    for(i=1;i<=m;i++){
        if( !e[i].vis){
            long long t = mst + e[i].w - maxd[e[i].u][e[i].v];
            second_mst = min(second_mst,t);
        }
    }
    return second_mst;
}
