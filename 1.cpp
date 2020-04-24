namespace AC {

    //trie树,每个单词出现的次数,失配指针
    int trie[maxn][26],cntword[maxn],next[maxn],tot=1;
    int bo[maxn]; // 是否是单词

    void ac_init(){
        tot=1;
        memset(bo,0,sizeof(bo));
        memset(trie,0,sizeof(trie));
        memset(next,0,sizeof(next));
    }

    void build_trie(char *s){  // 建立trie树
        int len = strlen(s), u = 1;
        for(int i=0; i<len; ++i){
            int c = s[i] -'a';
            if( !trie[u][c]) trie[u][c] = ++tot;
            u = trie[u][c];
        }
       bo[u]++;
    }
    void  bfs_next(){
        for(int i =0;i<=25;++i) trie[0][i] = 1;
        queue<int> q; q.push(1); //队列
        next[1] = 0;             //根的失配指针
        while( !q.empty()){
            int u = q.front(); q.pop();
            for(int i = 0;i <= 25; ++i){
                if( !trie[u][i]) trie[u][i] = trie[next[u]][i]; // 优化
                else {
                    q.push(trie[u][i]);
                    int v = next[u]; 
                    next[ trie[u][i] ] = trie[v][i];
                }
            }
        }
    }

    void find( char *s){
        int u = 1, len=strlen(s);
        for(int i = 0; i <=len ;++i){
            int c = s[i] - 'a';
            int k = trie[u][c];
            while( k > 1){
                ans += bo[k];
                bo[k] = 0;
                k = next[k];
            }
            u = trie[u][c];
        }
    }
}
