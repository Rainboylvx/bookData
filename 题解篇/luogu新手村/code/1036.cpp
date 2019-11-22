#include <cstdio>
int n,k;
int a[5000005];
int ans = 0;
bool is_prime(int x){
	int i;
	for(i=2;i<=x-1;i++)
		if( x % i == 0)
			return 0;
	return 1;
}

void dfs(int dep,int pre,int sum){
	if( dep == k+1){
		if( is_prime(sum))	ans++;
		return ;
	}
	int i;
	for(i=pre+1;i<=n+dep-k;i++){
		sum += a[i];
		dfs(dep+1,i,sum);
		sum -= a[i];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	int i,j;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dfs(1,0,0);
	printf("%d",ans);
	
	return 0;
}