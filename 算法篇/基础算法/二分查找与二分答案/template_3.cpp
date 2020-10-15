// EF::work3(double l,double r)     三分,凸性函数机值问题,例如一元二次方程
// 核心思想：好点(更优点)与答案在坏点的同一侧,
//			所以新的区间舍弃掉坏点
namespace EF_3 {
    double f(double v);
    double work3(double l,double r){
        double eps = 1e-8;
        while(r-l >= eps){
            double m1 = l+(r-l)/3 ,m2 = r-(r-l)/3;
            if( f(m1) <f(m2)) l = m1;
            else r = m2;
        }
        return r;
    }
}
bool EF_3::f(double m){
    //TODO:
}
