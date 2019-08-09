#include <bits/stdc++.h> 
using namespace std;

int n;
typedef multimap<int,int> MM;
MM mm;

#define MP(a,b) make_pair(a,b)

//attack point
int get_min_id(int ap){
    MM::iterator l = mm.lower_bound(ap);
    MM::iterator r = mm.upper_bound(ap);
    int _min = 0x7f7f7f7f;
    for( ; l != r ;l++){
        _min = min(_min,l->second);
    }
    return _min;
}

int main(){
    scanf("%d",&n);
    mm.insert(MP(1000000000,1));
    int i,t1,t2;
    MM::iterator iter1,iter2;
    for (i=1;i<=n;i++){
        scanf("%d%d",&t1,&t2);
        iter2 = mm.lower_bound(t2);

        if( iter2 == mm.end() ){
            int ans = get_min_id((--iter2)->first);
            printf("%d %d\n",t1,ans);
        }
        else if ( iter2 == mm.begin()){
            int ans = get_min_id(iter2->first);
            printf("%d %d\n",t1,ans);
        }
        else {
            iter1 = iter2;
            iter2--;
            int r = iter1->first - t2;
            int l = t2-iter2->first ;
            if( l < r ){
                int ans = get_min_id(iter2->first);
                printf("%d %d\n",t1,ans);
            }
            else if ( l > r ){
                int ans = get_min_id(iter1->first);
                printf("%d %d\n",t1,ans);
            }
            else {
                int ans1 = get_min_id(iter1->first);
                int ans2 = get_min_id(iter2->first);
                printf("%d %d\n",t1,min(ans1,ans2));
            }
        }
        mm.insert(MP(t2,t1));
    }
    return 0;
}
