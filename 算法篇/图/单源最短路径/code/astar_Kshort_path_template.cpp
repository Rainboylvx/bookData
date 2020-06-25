const int maxn = 1e5+5;
int dis[maxn];
struct node_for_astar_k {
    int v,w;
    friend bool operator<(const node_for_astar_k &a,const node_for_astar_k &b){
        return a.w+dis[a.v] >  b.w+dis[b.v];
    }
};

int astart_Kshort_path(int s,int t){

    /* 起点和终点相同是 */
    if( s == t){
        k++;
    }
    q.push(qnode(s,0));
    while(!q.empty()){

        qnode h = q.top();
        q.pop();

        int now = h.v;
        if( now ==t){
            cnt++;
            if( cnt == k ) return h.w;
        }

        int i;
        for(i = head[now]; i!= -1;i = e[i].next){
            int &v = e[i].v;
            int &w = e[i].w;
            q.push(qnode(v,w+h.w));
        }

    }

    return -1;
}
