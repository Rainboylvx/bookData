
## 说明

未完成

## 哈希表（散列表）的基本原理：


使用一个下标范围比较大的数组来存储元素，一般通过设计一个函数（哈希函数，即散列函数），使得每个元素经过hash散列之后得到一个特征值，将这个特征值作为数组下标，并在该下标位置存入这个元素。

**关键：如何构造这个散列函数？？？**


## 解决冲突

采用**取余法**构造，**链地址法处理冲突**


定义一个容器,还有链式前向星,trie树
```c
vector<user> head[M];
```

## 常用的hash函数

**ELFhash:**

```c
int ELFHash(char *key){
    unsigned long h=0;
    while(*key){
        /* 左移动4位 加上一个新的数字*/
        h=(h<<4)+(*key++);//注1
        /* 取最高4位 */
        unsigned int g=h&0Xf0000000L;
        /* 如果高4位非空*/
        /* h 和 h的高4位异或*/
        if(g) h^=g>>24;
        /* 把高4位清零 */
        h&=~g;
    }
    return h%ArrayLen;
}
```
**ELF Hash 原理:**

-  h左移动4位 加上一个新的数字
-  h取最高4位 
-  如果h高4位非空
-  h 和 h的高4位异或
-  把h高4位清零 



**BKDR hash:**

```c
unsigned int BKDRHash(char* str)
{
    /* 找一个种子,素数 */
    unsigned int seed = 131 ; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0 ;
    while (*str)//因为字符串的末尾为'\0'
    {
        /* 自己*seed + 当前值*/
        hash = hash*seed + (*str++ );
    }
    /* 保留正数, 对hash表长度取余*/
    return (hash & 0x7FFFFFFF )%ArrayLen;
}
```


## 例题

 - cojs65 字串变换


## 注

注1:

```c
#include <cstdio>
int a[] = {1,2,3,4,5};
int main(){
	int *b = a; //取数组开始地址
	printf("%d\n",*b++);//和下面的那句一样
	//printf("%d\b",*(b++)); //因为++ 的优先级比*高
	if(b == &a[1])
		printf("yes");
}
```

## 直接定址法

我们可以使用`vector<T> head[m]`这种STL的方式来实现一种类似表的结构的`hashTable`

当然我们可以使用数组来实现我们自己的`hashTable`

形像化的数据形式如下


```
        head                    数据表格
    记录当前行的长度          存原来的值
    下标就是hashValue
          V                         V
        +---+     +-------+-------+-------+-------+-------+-------+
        | 0 | --> | 数据1 | 数据2 | 数据3 | 数据4 | 数据5 | 数据6 |
        +---+     +-------+-------+-------+-------+-------+-------+
        | 0 | --> | 数据1 | 数据2 | 数据3 | 数据4 | 数据5 | 数据6 |
        +---+     +-------+-------+-------+-------+-------+-------+
        | 0 | --> | 数据1 | 数据2 | 数据3 | 数据4 | 数据5 | 数据6 |
        +---+     +-------+-------+-------+-------+-------+-------+
        | 0 | --> | 数据1 | 数据2 | 数据3 | 数据4 | 数据5 | 数据6 |
        +---+     +-------+-------+-------+-------+-------+-------+
        | 0 | --> | 数据1 | 数据2 | 数据3 | 数据4 | 数据5 | 数据6 |
        +---+     +-------+-------+-------+-------+-------+-------+
```




下面的代码是对`cojs65`题目代码`hashTable`数据结构的一个摘抄,完整代码看我写的题目




```c
#include <cstdio>
#include <cstring>

//类型宏定义
typedef char ch20[20];


ch20 hashTable[100000][100] = {0};
//记录每行数据长度
int hashTable_point[100000]={0};


char src[30];
char dst[30];

int src_state;
int dst_state;

char guize1[10][30];
char guize2[10][30];
int gz_s=0;//规则数

int cnt =0;


/* 往hashTable里存数据, */
/* 参数1: hashVaule */
/* 参数2: 原值 */
void hashTable_push(int state,char str[]){
    int &i =hashTable_point[state];
    strcpy(&hashTable[state][i][0],str);
    i++;
}

/* 在hashTable里找值,找到返true */
/* 参数1: hashVaule */
/* 参数2: 原值 */
bool hashTable_find(int state,char str[]){
    int &i =hashTable_point[state];//数量
    int j;
    for (j=0;j<i;j++){
        //是不是和原值一样
        if(strcmp(&hashTable[state][i][0],str) == 0)
            return true;
        else 
            return false;
    }

    return false;
}
```
