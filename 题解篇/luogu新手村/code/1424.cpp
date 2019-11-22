#include <cstdio>

int main(){
	
	int n,x;
	scanf("%d%d",&x,&n);
	
	int i;
	int cnt = 0; 
	for(i=1;i<=n;i++){
		int t = (x+i-1 ) % 7; // 星期几 
		if( t == 6 || t== 0)
			cnt++; //有几个周末 
	}
	int st = n -cnt;
	printf("%d",st*250);	


	return 0;
}