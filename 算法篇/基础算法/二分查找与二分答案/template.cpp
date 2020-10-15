/* 使用: 首先定义EF::check函数 
 * EF::work(int l,int r)            二分
 * EF::work(double l,double r)      二分-double
 *
 * EF::work 区间[l,r) 内第一个不满足check()的位置
 *  if check(mid) => mid < key 则找到第一个 >=key 的位置 
 *  if check(mid) => mid <=key 则找到第一个 >key  的位置 
 *  核心思想:[l,r)是满足check的区间,不停缩小[l,r)
 * */
namespace EF {
    bool check(int mid);    //函数声明
    int work(int l,int r){
        while( l != r){
            int mid = (l+r)>>1;
            if( check(mid) ) l = mid+1;
            else r = mid;
        }
        return l;
    }
    /*
     *bool check(double mid); // double 型二分
     *double work(double l,double r){
     *    double eps = 1e-8;
     *    while(r-l >eps){
     *        double mid = (l+r) /2;
     *        check(mid) ? l = mid : r = mid;
     *    }
     *    return r;
     *}
     */
}
bool EF::check(int mid){
    //TODO:
}
