# string��ʹ��

## string���hello world

```
#include <iostream>
#include <string>
using namespace std;

int main(){
	string s1("hello world 1");
	cout << s1 <<endl;
	string s2 = "hello world 2";
	cout << s2 <<endl;
	string s3;
	s3 = "hello world 3";
	cout << s3 <<endl;
	s3 = "hello world 4";
	cout << s3 <<endl;
	return 0;
}
```

## string����Ķ������ʼ��



|����|����|
|----|----|
|string s1|һ���յĶ��󣬳���Ϊ0|
|string s2(s1)|��s2��ʼ��Ϊs1�ĸ���|
|string s3("value")|��s3��ʼ��Ϊ����ֵ�ĸ���|
|string s4(n)|s4Ϊn��'c'�ĸ���|
|string s5(n,'c')|s4Ϊn��'c'�ĸ���|
## string�Ķ���

## string�Ĳ���


### ���ò���

|���� | ����|
|s.empty()|�Ƿ�Ϊ��|
|s.size()|�ַ�����|
|s1+s2|ƴ�ӣ�����һ���µ��ַ���|
|s1=s2|��ֵ|
|s1 == s2|�Ƿ����|
|!=,<,<=,>,>=|�ֵ���Ƚ�|


### ����1

```
#include <string>
#include <iostream>
using namespace std;

int main(){
	
	string s1;
	if( s1.empty())
		cout << "yes,empty"<<endl;
	//s1[1] ='c'; //�±���������ܸ�ֵ�������ڵĵط�
	s1 = "new string str";//����
	s1[1] ='c';//�±������ok
	return 0;
}
```

### ����2

```
#include <string>
#include <iostream>
using namespace std;

int main(){
	
	string s1(100,0);//��ʼ��100���ַ���ֵΪ0���ַ���
	
	int i;
	for(i=0;i<100;i++)
		s1[i]= 'c';
	cout <<  s1 <<endl;
	
	string::size_type x;
	for(x=0;x<s1.size();x++)
		s1[x]='d';
	cout <<  s1 <<endl;

	return 0;
}
```

## ps

### string::size_type


## �򵥵���Ŀ











