#include <cstdio>
#include <cstring>

char str[10000];
int len;
char a;

int idx=1;
int read(int &n,bool &is_xi ,bool &is_left){
    int &x = n;
	x = 0;
	int flag = 1;
	if( idx > len) return idx;
	char ch = str[idx++];
	
	while( ch <'0' || ch >'9'){
		if( ch == '-')
			flag = -1;
		else if( ch == '='){
			is_left = false;
		} else if( ch >='a' && ch <= 'z'){
		    a = ch;
			is_xi = true;
			n = flag;
			return idx;
		}
		if( idx > len) return idx;
		ch = str[idx++];	
	}
	
	while( ch>='0' && ch <='9'){
		x = x*10 +ch-'0';
		if( idx > len) 
		{
		    x = x*flag;
		    return idx;
		}
		ch = str[idx++];
	}
	n = x*flag;
	if( str[idx-1] >='a' && str[idx-1] <='z'){
		a = ch;
		is_xi = true;
	}
	else if ( str[idx-1] == '=' || str[idx-1] == '-' ){
	    idx--;
	}

	return idx;
}

int main(){
	scanf("%s",str+1);
	len = strlen(str+1);
	
	bool is_left = true;
	int xi = 0;
	int c = 0;
	while(1){
		bool is_xi = false;
		int n;
		int stop = read(n,is_xi,is_left);
		if( is_left == false)
		 	n = -n;
        //printf("%d %d\n",n,is_xi);
		if( is_xi)
		    xi += n;
		else
		    c += n;
		if( stop > len)
			break;
	}
	double ans = -c*1.0/xi;

    if( ans == -0.0)
        ans = -ans;
	//printf("%c=%lf\n",a,ans);
	printf("%c=%0.3lf",a,ans);
	
	return 0;
}
