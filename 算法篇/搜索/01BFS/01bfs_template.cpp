void _01bfs(int state,int sx,int sy){
    /* 清空标记 */
    memset(vis,0,sizeof(vis));
    typedef struct { int x,y,step; } node;
    deque<node> q;
    q.push_back({sx,sy,0}); //加入起点

    while( !q.empty()){
        node h = q.front();
        q.pop_front();
        if( vis[h.x][h.y])
            continue;
        vis[h.x][h.y] = 1; //标记

        dis[state][h.x][h.y] = h.step;

        int i;
        for(i = 0; i < 4;i++ ){
            int nx = h.x  + fx[i][0];
            int ny = h.y  + fx[i][1];
            if( in_map(nx,ny) && !vis[nx][ny] && _map[x][y] != '#' ){
                if( _map[x][y] == '0')
                    q.push_front({nx,ny,h.step});
                else
                    q.push_back({nx,ny,h.step+1})
            }
        }
    }
}
