#include <iostream>
using namespace std;
int n,k;
int a[100000];
int ans = 0;
bool su(int n){
	int i;
	for(i=2;i<=n-1;i++){
		if( n % i == 0)
			return false;
	}		
	return true;
}

void choose(int pre,int dep,int sum){
	if( dep == k+1 ){
		if( su(sum))
			ans++;
		return ;
	}
	int i;
	for(i=pre+1 ; i<= n ;i ++){
		choose(i,dep+1,sum+a[i]);
	}
}

int main(){
	cin >> n >> k;
	int i;
	for(i=1;i<=n;i++)
		cin >> a[i];
	choose(0,1,0);
	cout << ans;
	return 0;
}
