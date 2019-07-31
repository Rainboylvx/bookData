//查找范围是[l,r), a[r] 永远 > key
template <typename T>
int first_g(T key,T a[],int l,int r){
    int m;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        if( a[m] <= key ) //表示 [m+1,r) 满足条件
            l = m+1;
        else
            r = m;
    }
    return l;
}
