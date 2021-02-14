/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 02月 08日 星期一 21:32:24 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
class Base {
    public:
        int pub_mem;
    protected:
        int prot_mem;
    private:
        int priv_mem;
};

class Pub_Derv : public Base {
    int f() { return prot_mem; }
    //int g(){ return }
};

class Pri_Derv : private Base {
    int f() { return prot_mem; } // ok , can access protected
    //int g() { return priv_mem;} //fail ,can not access private
    //int g(){ return }
};

int main(){
    Base b1;
    b1.pub_mem = 1; // ok accessable
    //b1.prot_mem = 1; // fail

    Pub_Derv pub;
    Pri_Derv pri;

    pub.pub_mem = 1;// ok
    pri.pub_mem = 1; // fail 

    return 0;
}
