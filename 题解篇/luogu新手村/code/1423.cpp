#include <cstdio>

int main(){
	double x;
	scanf("%lf",&x);
	int i;
	double one = 2;
	double sum = 0;
	
	for(i=1;1;i++){
	    sum = sum + one;
	    one = one *0.98;
	    if( sum >= x)
	        break;
	}
	printf("%d",i);
	return 0;
}
