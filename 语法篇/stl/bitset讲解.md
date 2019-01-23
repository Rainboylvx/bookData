http://zh.cppreference.com
# bitset����

## bitset����

���ٵĶ�һ�������Ķ����Ƶ�λ�����в���,����`vector`,`bitset`��һ����ģ��.
biset���Ͷ�����������䳤�Ȳ���������.�ڶ���bitset��ʱ��Ҫ��ȷ���ж���λ,��������ֵ

��������


```c++
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main(){
    string s1("010101");
    cout << s1 << endl;//010101
    
    bitset<10> b1(s1);
    cout << b1 << endl;//0000010101

    bitset<5> b2(s1);
    cout << b2 << endl;//01010
    return 0;
}
```


## bitset�Ķ������ʼ��

|����|����|

|bitset<n> b;|b��nλ,ÿλΪ0|
|bitset<n> b(u);|b��unsigned long ��u��һ������|
|bitset<n> b(s);|b��string�����к���λ���ĸ���|
|bitset<n> b(s,pos,n)|b��s�еĴ�λ��pos��ʼ�ĸ�λ�ĸ���|
|bitset<n> b1(b1) | ��b��ʼ��b1|

## ����

### unsigned ��ʼ��bitset

```c++
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main(){
    //����
    bitset<16> b1(0xffff);
    cout << b1 << endl;//1111111111111111
    
    //���� ȡ��λ
    bitset<16> b2(0x0000ffff);
    cout << b2 << endl;//1111111111111111

    //��λû�е�ȡ0
    bitset<32> b3(0xffff);
    cout << b3 << endl;
    //bit0-15 set 1; bit 16-31 set 0
    
    //������ܴ�
    bitset<128> b4(0xffff);
    cout << b4 << endl;
    //bit 32-127 set 0
    
    int i = 123;
    bitset<32> b5(i);
    cout << b5 << endl;
    
    // ע������,Ϊʲô-1��Ӧ32��1
    i = -1;
    bitset<32> b6(i);
    cout << b6 << endl;
    return 0;
}
```


### string ��ʼ��bitset

 - ��`string`�������λ����ʱ��**���ҵ���**
 - string����С��bisetλ��ʱ,biset��λΪ0
 - string���ȴ���bisetλ��ʱ,ȡstring��ߵ�һ����
 - ֻ��string���Ӵ�
    - ʹ����������
    - ʡ�Ե���������
 
```
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main(){
    //���������
    string s1("10");
    bitset<4> b1(s1);
    cout << b1 << endl;//0010
    
    //string����С��bisetλ��ʱ,biset��λΪ0
    string s2("11");
    bitset<4> b2(s2);
    cout << b2 << endl;//0011
    	
    //string���ȴ���bisetλ��ʱ,ȡstring��ߵ�һ����
    string s3("01110101");
    bitset<4> b3(s3);
    cout << b3 << endl;//0111
    
    //ֻ��string���Ӵ�
    string s4("11110101");
    //str[0] ��ʼ��4���ַ�,����str[0]
    bitset<8> b4(s4,0,4);
    cout << b4 << endl;//00001111
    
    //ʡ��ÿ��������,��ʾһֱȡ�����һ���ַ�
    //s4[3]��s4[s4.size()-1]
    bitset<8> b5(s4,3);
    cout << b5 << endl;//00010101
    
    //ȡs4���4λ
    bitset<8> b6(s4,s4.size()-4);//
    cout << b6 << endl;//00000101
    return 0;
}
```

## bitset �����ϵĲ���

|����|����|

|b.any()|b���Ƿ����Ϊ1��λ|
|b.none()|b���Ƿ񲻴�Ϊ1��λ|
|b.count()|b��1�ĸ���|
|b.size()|b�ĳ���|
|b[pos]|b�е�posλ|
|b.test(pos)b�е�posλ�Ƿ�Ϊ1|
|b.set()|bȫ��1|
|b.set(pos)|b��posλ��1|
|b.reset()|bȫ��0|
|b.reset(pos)|b��posλ��0|
|b.flip()|b������λȡ��|
|b.flip(pos)|b��posλȡ��|
|b.to_ulong()|b��λת����һ��usigned long ����|
|os << b|��� |



����

```c++
#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main(){
    
    bitset<32> b1;//32��0
    
    if( b1.any()) //�Ƿ���1,any:�κ�һ��1 any 1
    	cout <<"exit 1"<< endl;
    else 
    	cout <<"all 0"<< endl;
    
    if( b1.none())//none:û���κ�1
    	cout <<"all 0"<< endl;
    else 
    	cout <<"exit 1"<< endl;
    
    
    bitset<32> b2(0xf0);//32��0
    if( b2.any()) //any:�κ�һ��1 any 1
    	cout <<"exit 1"<< endl;
    else 
    	cout <<"all 0"<< endl;
    
    if( b2.none())//none:û���κ�1
    	cout <<"all 0"<< endl;
    else 
    	cout <<"exit 1"<< endl;
    
    cout <<"numbers of 1 in b2:" << b2.count() << endl;
    
    string s3("1100");
    bitset<4> b3(s3);
    bitset<4> b4(b3);//����b3�ĸ���
    
    cout << "b4" << b4 << endl;
    
    cout << "b3 is:" << b3 << endl;
    
    cout << "set():"<< b3.set() << endl;
    cout << "reset():"<< b3.reset() << endl;
    b3 = b4;
    cout << "now b3: "<< b3 << endl;
    cout << "b3.set(0): " << b3.set(0) << endl;
    cout << "b3.resset(3): " << b3.reset(3) << endl;
    cout << "b3.flip(): " << b3.flip() << endl;
    cout << "b3.flip(1): " << b3.flip(1) << endl;
    cout << "b3.to_ulong(): " << b3.to_ulong()<<endl;
    
    cout << "b3[0]: " << b3[0] << endl;
    cout << "b3[3]: " << b3[3] << endl;
    //�±����
    b3[3] = 0;
    cout << "b3[3]: " << b3[3] << endl;
    
    //λ������
    cout << "b3: " << b3 << endl;
    cout << "b4: " << b4 << endl;
    cout << "b3|b4: " << (b3 | b4) <<endl;
    cout << "b3 & b4: " << (b3 & b4) <<endl;
    cout << "b4 << 1: " << ( b4 << 1) << endl;
    cout << "b4: " << b4 << endl;
    bitset<4> b5(b4 << 1);
    cout << "b5: " << b5 << endl;
    
    cout << "b4 >> 1: " << ( b4 >> 1) << endl;
    cout << "b4.size(): "<< b4.size()<<endl;
    return 0;
}
```
