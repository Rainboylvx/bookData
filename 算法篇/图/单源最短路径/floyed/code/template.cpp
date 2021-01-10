struct Floyed {
    int f[100][100]; //这里的大小自己设定,通常100夠用
    Floyed(){
        memset(f,0x1f,sizeof(f)); //初始化
    }
    void init(int u ,int v,int w){ //初始化
        f[u][v] = w;
        //f[v][u] = w; //无向图要去掉这个注释
    }
    void work(){
        for(int k=1;k<=n;++k){ //这里的n是全局的n
            for(int i=1;i<=n;++i){
                for(int j=1;j<=n;++j){
                    if(f[i][j] > f[i][k] + f[k][j]){
                        f[i][j] = f[i][k] + f[k][j];
                    }
                }
            }
        }
    }
} floyd;
