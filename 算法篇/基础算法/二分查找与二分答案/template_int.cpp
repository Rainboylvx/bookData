/* 使用: 首先定义check函数 
 * bs(int l,int r,check)            二分
 *
 * bs 区间[l,r) 内第一个不满足check()的位置
 *  if check(mid) => mid < key 则找到第一个 >=key 的位置 
 *  if check(mid) => mid <=key 则找到第一个 >key  的位置 
 *  核心思想:[l,r)是满足check的区间,不停缩小[l,r)
 * */
template<typename F>
int bs(int l,int r,F check){
    while (l != r) {
        double m = (l+r)>>1;
        if( check(m) )
            l = m+1; //舍弃m
        else
            r = m;   //保留m
        // 区间[l,r) 内第一个不满足check()的位置
    }
}
bool check(int m){
    //change here
}
