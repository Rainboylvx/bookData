#include <cstdio>
 
int main(){
	char a;
	int b;
	float c;
	double d;
	scanf("%c",&a);
	scanf("%d",&b);
	scanf("%f",&c);
	scanf("%lf",&d);//lf == long float
	printf("%c %d %0.6f %0.6lf",a,b,c,d);
	return 0;
 }