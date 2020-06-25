namespace AC {

    //trie树,每个单词出现的次数,失配指针
    int ch[maxn][26],cntword[maxn],next[maxn],tot=1;
    int bo[maxn]; // 是否是单词

    void ac_init(){ 
        tot=1;  //结点从1开始编号
        memset(bo,0,sizeof(bo));
        memset(ch,0,sizeof(ch));
        memset(next,0,sizeof(next));
    }

    void build(char *s){  // 建立ch树
        int len = strlen(s), u = 1;
        for(int i=0; i<len; ++i){
            int c = s[i] -'a';
            if( !ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
       bo[u]++;
    }
    void  bfs_next(){
        for(int i =0;i<=25;++i) ch[0][i] = 1;
        queue<int> q; q.push(1); //队列
        next[1] = 0;             //根的失配指针
        while( !q.empty()){
            int u = q.front(); q.pop();
            for(int i = 0;i <= 25; ++i){
                if( !ch[u][i]) ch[u][i] = ch[next[u]][i]; // 优化
                else {
                    q.push(ch[u][i]);
                    int v = next[u]; 
                    next[ ch[u][i] ] = ch[v][i];
                }
            }
        }
    }

    void find( char *s){
        int u = 1, len=strlen(s);
        for(int i = 0; i <=len ;++i){
            int c = s[i] - 'a';
            int k = ch[u][c];
            while( k > 1){
                ans += bo[k];
                bo[k] = 0;
                k = next[k];
            }
            u = ch[u][c];
        }
    }
}
