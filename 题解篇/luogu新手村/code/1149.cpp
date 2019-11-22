#include <cstdio>

int a[] = {6,2,5,5,4,5,6,3,7,6};
int n;
int chai(int x){
	if( x == 0)
		return a[0];
	int sum = 0;
	while( x != 0){
		int t = x % 10;
		sum += a[t];
		x = x /10;
	}
	return sum;
}
int main(){
	int cnt = 0;
	scanf("%d",&n);
	n -= 4;
	int i,j;
	for(i=0;i<=999;i++)
		for(j=0;j<=999;j++)
		{
			if( chai(i)+chai(j) + chai(i+j) == n){
				cnt++;
				//printf("%d %d %d\n",i,j,i+j);
				//printf("\t %d % d %d\n",chai(i),chai(j) , chai(i+j));
			}
				
		}
	printf("%d",cnt);
	return 0;
}