
## ʲô��STL

> STL = Standard Template Library����׼ģ��⣬����ʵ���ҿ�����һϵ�������ͳ�ơ�������Alexander Stepanov��Meng Lee��David R Musser�ڻ���ʵ���ҹ���ʱ�����������ġ��Ӹ�����˵��STL��һЩ���������ļ��ϣ���Щ����������list,vector,set,map�ȣ�STLҲ���㷨������һЩ����ļ��ϡ�����ġ����������㷨�ļ���ָ���������Ϻܶ�����˺ܶ���Ľ�����STL��Ŀ���Ǳ�׼������������Ͳ������¿���������ʹ���ֳɵ������STL������C++��һ���֣���˲��ö��ⰲװʲô��  -- �ٶȰٿ�


## Alexander Stepanov STL֮��

Alexander Stepanov��ʿ��adobe��˾����ϯ��ѧ�ң�Ҳ�Ǳ�׼ģ��⣨STL���Ĵ����ߣ���1995�����˵�һ��Dr. Dobb������ƽܳ�����

## һ������ʹ��STL�Ĵ���

```
/*
    ��򵥵�STL�Ĵ���
*/
#include <cstdio>
#include <vector>
using namespace std;

int main(){

	//����
	vector<int> vec;

	int i;
	for(i=0;i<1000;i++)//��ֵ 
		vec.push_back(i);
	
	vector<int>::iterator  ite;

	//���1 STL���
	for(ite=vec.begin();ite!=vec.end();ite++)
		printf("%d ",*ite);
	
	//���2 ���ǳ��÷��
	for(i=0;i<1000;i++)
		printf("%d",vec[i]);
	
	return 0;
}

```


## STL�������

 - ������Container��
 - �㷨��Algorithm��
 - ��������Iterator��
 - �º�����Function object��
 - ��������Adaptor��
 - �ռ���������allocator��


## STL�����㷨��

```
accumulate() Ԫ���ۼ�
adjacent_difference() ����Ԫ�صĲ��
adjacent_find() ��Ѱ���ڵ��ظ�Ԫ��
binary_search() ��Ԫ��Ѱ
copy() ����
copy_backward() ������
count() ����
count_if() ���ض������¼���
equal() �ж�������
equal_range() �ж������񣨴���һ�����������䷶Χ��
fill() ����Ԫ��ֵ
fill_n() ����Ԫ��ֵ��n ��
find() ��Ѱ
find_if() ���ض���������Ѱ
find_end() ��Ѱĳ�������е����һ�γ��ֵص�
find_first_of() ��ѰĳЩԪ�ص��״γ��ֵص�
for_each() �Է�Χ�ڵ�ÿһ��Ԫ��ʩ��ĳ����
generate() ��ָ�������������������ض���Χ�ڵ�Ԫ��
generate_n() ��ָ������������������ n ��Ԫ������
includes() �����
inner_product() �ڻ�
inplace_merge() �ϲ���ȡ������д��
iter_swap() Ԫ�ػ���
lexicographical_compare() ���ֵ����з�ʽ���Ƚ�
lower_bound() ����
max() ���ֵ
max_element() ���ֵ����λ��
min() ��Сֵ
min_element() ��Сֵ����λ��
merge() �ϲ���������
mismatch() �ҳ����Ǻϵ�
next_permutation() �����һ���������
�������㷨��Generic Algorithms���� Function Obje4 cts
nth_element() ���°��������е�n��Ԫ�ص���������
partial_sort() �ֲ�����
partial_sort_copy() �ֲ����򲢸��Ƶ�����
partial_sum() �ֲ��ܺ�
partition() �и�
prev_permutation() ���ǰһ���������
random_shuffle() �������
remove() �Ƴ�ĳ��Ԫ�أ�����ɾ����
remove_copy() �Ƴ�ĳ��Ԫ�ز���������Ƶ���һ�� container
remove_if() ���������Ƴ�ĳ��Ԫ��
remove_copy_if() ���������Ƴ�ĳ��Ԫ�ز���������Ƶ���һ�� container
replace() ȡ��ĳ��Ԫ��
replace_copy() ȡ��ĳ��Ԫ�أ�����������Ƶ���һ�� container
replace_if() ��������ȡ��
replace_copy_if() ��������ȡ��������������Ƶ���һ�� container
reverse() �ߵ�Ԫ�ش���
reverse_copy() �ߵ�Ԫ�ش��򲢽�������Ƶ���һ�� container
rotate() ��ת
rotate_copy() ��ת������������Ƶ���һ�� container
search() ��Ѱĳ��������
search_n() ��Ѱ���������� n �Ρ���������
set_difference() �
set_intersection() ����
set_symmetric_difference() �ԳƲ
set_union() ����
sort() ����
stable_partition() �и����Ԫ����Դ���
stable_sort() ���򲢱��ֵ�ֵԪ�ص���Դ���
swap() �û����Ե���
swap_range() �û���ָ����Χ��
transform() ����������Ϊ�������������ò�������������
unique() ���ظ���Ԫ��ߡ�����࣬ʹ��Ψһ
unique_copy() ���ظ���Ԫ��ߡ�����࣬ʹ��Ψһ�������Ƶ�����
upper_bound() ����
```
