//luogu-2234
#include <bits/stdc++.h>
using namespace std;

#define N 32768
#define qwq 1000000 //开一个常数 把负值转化为正值
#define lson (rt<<1)
#define rson (rt<<1)|1

int n,p[N],cnt[qwq<<2];
int *st;

//根据题意可以发现 我们只需要update进行添加操作就好
void update(int pos,int rt,int l,int r){
    if(pos<l or pos>r)return;
    if(l==r){
        st[rt]++;
        return;
    }
    int mid=(l+r)>>1;
    update(pos,lson,l,mid);
    update(pos,rson,mid+1,r);
    st[rt]=st[lson]+st[rson];

}

int get_rank(int pos,int rt,int l,int r){
    if(pos>r)return st[rt];
    int mid=(l+r)>>1;
    int pos_rank=0;
    pos_rank+=get_rank(pos,lson,l,mid);
    if(pos>mid+1)
        pos_rank+=get_rank(pos,rson,mid+1,r);
    return pos_rank;
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
        if(st[rt])
            return findpre(rt,l,r); 
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
    if(st[lson]!=0)//左子树非空
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

int main(){
    scanf("%d",&n);
    int maxx=-1;
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        p[i]+=qwq;
        maxx=max(p[i],maxx);
    }
    //printf("%d\n",maxx);
    st=new int [maxx<<2];
    int ans=p[1]-qwq;
    cnt[p[1]]++;
    update(p[1],1,1,maxx);
    for(int i=2;i<=n;i++){
        cnt[p[i]]++;
        if(cnt[p[i]]<=1)//手动去重
            update(p[i],1,1,maxx);
        if(cnt[p[i]]>1){//如果以前出现过和现在一样的营业额 那一定是最小的
            continue;
        }
        int rank_p=get_rank(p[i],1,1,maxx)+1;
        if(rank_p==1){//如果它是最小的 就找它的后继
            ans+=abs( (p[i]-qwq)-(nex(p[i],1,1,maxx)-qwq) );
            //printf("nex %d\n",nex(p[i],1,1,maxx)-qwq);
            continue;
        }
        else{//否则就是它的前驱与后继的最小值
            //printf("pre %d\n",pre(p[i],1,1,maxx)-qwq);
            int pos_pre=pre(p[i],1,1,maxx)-qwq;//这个点的前驱值
            int pos_nex=nex(p[i],1,1,maxx)-qwq;//这个点的后继值
            if(abs(p[i]-qwq-pos_pre)  <  abs(p[i]-qwq-pos_nex)){
                ans+=abs(p[i]-qwq-pos_pre)  ;
            }
            else {
                ans+=abs(p[i]-qwq-pos_nex);
            }
        }
    }
    //for(int i=1;i<=n;i++)printf("%d ",cnt[p[i]]);
    printf("%d\n",ans);
    return 0;
}
