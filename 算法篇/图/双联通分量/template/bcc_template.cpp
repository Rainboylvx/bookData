int dfn[maxn],low[maxn];
int idx,bcc_cnt;
stack<int> sta; //栈,存边的编号
//点的颜色,就是点属于哪个bcc
//防止bbc含有一个点多次
int color[maxn]; 
vector<int> bcc[maxn];//属于某个bcc的点有哪些

void tarjan(int u){
    dfn[u]=low[u] = ++idx;
    int i;
    for(int i=head[u];~i;i=e[i].next){
        int v=  e[i].v;
        if( !dfn[v]){ //没有访问过
            sta.push(i); //存边入栈
            tarjan(v);
            low[u] = min(low[u],low[v]);
            //!!!!注意:
            //这里没有判断u!=root
            if( low[v] >=dfn[u]){
                bcc_cnt++;
                while(1){
                    int i = sta.top(); sta.pop();
                    int uu = e[i].u,vv = e[i].v;
                    if(color[uu] != bcc_cnt){
                        bcc[bcc_cnt].push_back(uu);
                        color[uu] = bcc_cnt;
                    }
                    if(color[vv] != bcc_cnt){
                        bcc[bcc_cnt].push_back(vv);
                        color[vv] = bcc_cnt;
                    }
                    if( uu == u && vv == v) break;
                }
            }
        }
        else low[u] = min(low[u],dfn[v]);
    }

}
void find_bcc(){
    int i;
    for( i =1;i<=n;i++)
        if( !dfn[i]) tarjan(i);
}
