//权值线段树
#include <bits/stdc++.h>
using namespace std;

#define N 100001
#define lson (rt)<<1
#define rson (rt)<<1|1
#define qwq 1e7
#define inf 0x7f7f7f7f

int n,opr;
long long *st;
struct {int opr;long long pos;}p[N];

vector<long long> v;

long long getidx(long long x){
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}

void prep(){
    sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
    st=new long long [v.size()<<2];
}

//add的值只有1/-1 表示添加或删除
void update(int add,int pos,int rt,int l,int r){
    if(r<pos or l>pos)return;
    if(l==r){
        st[rt]+=add;
        return;
    }
    int mid=(l+r)>>1;
    update(add,pos,lson,l,mid);
    update(add,pos,rson,mid+1,r);
    st[rt]=st[lson]+st[rson];
}

//查询第k小的值
long long kth(int k,int rt,int l,int r){
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(st[lson]>=k)return kth(k,lson,l,mid);
    return kth(k-st[lson],rson,mid+1,r);
}

long long rankk(long long pos,int rt,int l,int r){
    if(l==r and l==pos)return 0;
    if(r<pos)return st[rt];
    int mid=(l+r)>>1;
    int ruak=0;
    ruak+=rankk(pos,lson,l,mid);
    if(pos>mid+1)ruak+=rankk(pos,rson,mid+1,r);
    return ruak;
}

long long findpre(int rt,int l,int r){
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(st[rson])
        return findpre(rson,mid+1,r);
    return findpre(lson,l,mid);
}

long long pre(long long pos,int rt,int l,int r){
    if(r<pos){
        if(st[rt])return findpre(rt,l,r); 
        return 0;
    }
    int mid=(l+r)>>1;
    int pos_pre;
    if(pos>mid+1 and st[rson] and (pos_pre=pre(pos,rson,mid+1,r)))
        return pos_pre;
    return pre(pos,lson,l,mid);
}

long long findnex(int rt,int l,int r){
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    if(st[lson]!=0)
        return findnex(lson,l,mid);
    return findnex(rson,mid+1,r);
}

long long nex(int pos,int rt,int l,int r){
    if(l>pos){
        if(st[rt]!=0){
            return findnex(rt,l,r);
        }
        return 0;
    }
    int mid=(l+r)>>1;
    int pos_nex;
    if(pos<mid and st[lson]!=0 and (pos_nex=nex(pos,lson,l,mid)))
        return pos_nex;
    return nex(pos,rson,mid+1,r);
}

void init(){
    long long maxx=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%lld",&p[i].opr,&p[i].pos);
        if(p[i].opr!=4){
            v.push_back(p[i].pos);
        }
    }
    prep();
    maxx=v.size();
    memset(st,0,sizeof(st));
    long long x,ans;
    for(int i=1;i<=n;i++){ 
        x=p[i].pos;
        switch(p[i].opr){
            case 1:{
                       update(1,getidx(x),1,1,maxx);
                       break;
                   }
            case 2:{
                       update(-1,getidx(x),1,1,maxx);
                       break;
                   }
            case 3:{
                       ans=rankk(getidx(x),1,1,maxx)+1;//找的是x前面数的排名 所以最后+1才是 x的排名
                       printf("%lld\n",ans);
                       break;
                   }
            case 4:{
                       ans=v[(kth(x,1,1,maxx)-1)];
                       printf("%lld\n",ans);
                       break;
                   }
            case 5:{
                       ans=v[pre(getidx(x),1,1,maxx)-1];
                       printf("%lld\n",ans);
                       break;
                   }
            case 6:{
                       ans=v[nex(getidx(x),1,1,maxx)-1];
                       printf("%lld\n",ans);
                       break;
                   }
        }
    }
}

int main(){
    init();
    return 0;
}
