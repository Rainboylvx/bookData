#include <cstdio>

int main() {
	double s,x;
	scanf("%lf%lf",&s,&x);
	
	double sum = 0;
	double sec = 7;
	while( sum < s-x ){	
		sum += sec;
		sec *= 0.98; // sec = sec *0.98;	
	}
	sum += sec*0.98;
	if( sum > s+x){
		printf("n");
	}
	else 
		printf("y");
	
	return 0;
}