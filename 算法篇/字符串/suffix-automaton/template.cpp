
struct suffix_automatong {
    struct Node {
        int ch[26],len,fa;      //边, 当前点的最大maxlen,fa父亲节点
        Node(){ memset(ch,0,sizeof(ch)); len = fa= 0; }
    } node[maxn<<1]; //开两倍的点
    int last = 1; // 最长前缀所属节点的编号
    int tot= 1;// tot当前sam节点总数

    //增加
    void add(int c){
        int p  = last;
        int np = last= ++tot;
        node[np].len = node[p].len+1;
        for( ; p && node[p].ch[c] == 0 ; p = node[p].fa )
            node[p].ch[c] = np;
        if( !p ) node[np].fa = 1; // above case 1
        else {
            int q = node[p].ch[c];
            if( node[q].len == node[p].len+1) 
                node[np].fa = q; // above case 2
            else {
                int nq = ++tot;
                node[nq]     = node[q]; //nq是q的复制,继承了q的出边
                node[nq].len = node[p].len+1; // 求出len
                node[q].fa   = node[np].fa = nq; //全部指向分享出来的nq
                for(;p&&node[p].ch[c] == q; p = node[p].fa)
                    node[p].ch[c] = nq; // above case 3
            }
        }
    }
} sam;
