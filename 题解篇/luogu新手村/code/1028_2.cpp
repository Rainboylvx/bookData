#include <cstdio>
int n;
int ans[1005];
int chai(int n){
	if( n == 1)
		return 1;
	if( ans[n] != 0){ // 记忆化 
		return ans[n];
	}
	int i,s = 0;
	for(i=1;i<=n/2;i++){
		s += chai(i);
	}
	ans[n] = s+1;// 记忆化
	return s+1;
}
int main(){
	scanf("%d",&n);
	int a = chai(n);
	printf("%d",a);
	return 0;
}
