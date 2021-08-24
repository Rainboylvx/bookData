template<int p = 8,typename F>
double bs(double l,double r,F check){
    double pc = std::pow(0.1,p); // pc = precision
    while ( r-l >= pc ) {
        double m = (l+r) / 2;
        if( check(m) )
            l = m; //注意这里不能写成 l+pc
        else
            r = m;
    }
    return l;
}
bool check(double m){
    //change here
}
