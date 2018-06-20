
## 树的定义

**树状图**是一种数据结构，它是由`n（n>=1）`个有限节点组成一个具有层次关系的集合。把它叫做“树”是因为它看起来像一棵倒挂的树，也就是说它是根朝上，而叶朝下的。它具有以下的特点：

每个节点有零个或多个子节点；没有父节点的节点称为根节点；每一个非根节点有且只有一个父节点；除了根节点外，每个子节点可以分为多个不相交的子树；


![树](/book/images/树.png)





树（tree）是包含`n（n>0）`个结点的有穷集，其中：

 - （1）每个元素称为结点（node）；
 - （2）有一个特定的结点被称为根结点或树根（root）。
 - （3）除根结点之外的其余数据元素被分为`m（m≥0）`个互不相交的集合T1，T2，……Tm-1，其中每一个集合`Ti（1<=i<=m）`本身也是一棵树，被称作原树的`子树(subtree)`。



树也可以这样定义：树是由根结点和若干颗子树构成的。树是由一个集合以及在该集合上定义的一种关系构成的。集合中的元素称为树的结点，所定义的关系称为父子关系。父子关系在树的结点之间建立了一个层次结构。在这种层次结构中有一个结点具有特殊的地位，这个结点称为该树的根结点，或称为树根。

我们可以形式地给出树的递归定义如下:

1.单个结点是一棵树，树根就是该结点本身。

2.设T1,T2,..,Tk是树，它们的根结点分别为n1,n2,..,nk。用一个新结点n作为n1,n2,..,nk的父亲，则得到一棵新树，结点n就是新树的根。我们称n1,n2,..,nk为一组兄弟结点，它们都是结点n的子结点。我们还称T1,T2,..,Tk为结点n的子树。

3.空集合也是树，称为空树。空树中没有结点。


## 树的相关术语

 - **节点的度**:一个节点含有的子树的个数称为该节点的度；
 - **叶节点或终端节点**:度为0的节点称为叶节点；
 - **非终端节点或分支节点**:度不为0的节点；
 - **双亲节点或父节点**:若一个节点含有子节点，则这个节点称为其子节点的父节点；
 - **孩子节点或子节点**:一个节点含有的子树的根节点称为该节点的子节点；
 - **兄弟节点**:具有相同父节点的节点互称为兄弟节点；
 - **树的度**:一棵树中，最大的节点的度称为树的度；
 - **节点的层次**:从根开始定义起，根为第1层，根的子节点为第2层，以此类推；
 - **树的高度或深度**:树中节点的最大层次；
 - **堂兄弟节点**:双亲在同一层的节点互为堂兄弟；
 - **节点的祖先**:从根到该节点所经分支上的所有节点；
 - **子孙**:以某节点为根的子树中任一节点都称为该节点的子孙。
 - **森林**:由m（m>=0）棵互不相交的树的集合称为森林；

------------

## 树的存储结构

------------

### 1.父亲表示法(重要)

这种方法是定义一个数组,每个数组元素为一个结构体类型,其结点的结构定义如下:

```c
const int m  =10005;//树的结点数
struct node {
    int data;//数据域
    int parent;//父结点
};
node tree[m]; //树数组
```

![父亲表示法](/book/images/父亲表示法.png)

利用了树中除根结点外的每个结点都有一个父亲结点的这个性质.很容易找到树的根,但是找孩子就是遍历整个线性表.

**并查集**用到了这种结构.



### 2.孩子表式法

所有的结点都存在一个数组中,数组元素为结构体类型,包括数据域和长度为n(n为该树的度)的数组,分别存储该结点的每一个孩子的下标


不使用指针:

```c
const int n=树的度,maxn=结点数上限;
struct node {
    int data;//数据域
    int ch[n];指向孩子的下标
};

node tree[maxn];//树数组
```

![孩子表式法](/book/images/孩子表式法1.png)


使用指针,(再加上动态化静态)


```c
const int m=10;
typedef struct node;
typedef node * tree;
struct node {
    int data;
    tree child[m];
};
tree t;
```



一个实际的样例

```c
#include <cstdio>

struct _node {
    int data;
    struct _node *p[2];
};

_node tree[10];

/* 动态化静态 */
int cnt =0;
_node * newnode(){
    _node *u = &tree[cnt++];
    u->p[0] = u->p[1]=NULL;
    return u;
}

/* 
 *     1
 *   2   3
 *  4  5    6
 * */

/*添加一个点,父亲为fa,数据为data */
void add_node_to_tree(_node *fa,int child,int data){
    fa->p[child] = newnode();
    fa->p[child]->data= data;

}
int main(){

    _node *tmp_node ;

    _node *root = newnode();
    root ->data = 1;

    tmp_node = root;
    add_node_to_tree(tmp_node,0,2);
    add_node_to_tree(tmp_node,1,3);

    tmp_node = root->p[1];
    add_node_to_tree(tmp_node,1,6);

    tmp_node = root->p[0];
    add_node_to_tree(tmp_node,0,4);
    add_node_to_tree(tmp_node,1,5);

}
```

**缺点**:只能从根(父亲)遍历到子结点,不能从某个结点返回到它的父结点.但程序中确实需要从某个结点返回到它的父结点时,就需要在结点中多定义一个指针变量存放父结点的信息.



### 3.树的父亲孩子表式法

比较**孩子表式法**多了一个父结点指针的信息

```c
const int m=10;//权的度

typedef struct node;
typedef node *tree;

struct node {
    int data;
    tree child[m];//指向孩子
    tree father;//指向父亲
};
tree t;
```

一个实际的代码


```c
#include <cstdio>

struct _node {
    int data;
    struct _node *p[2];
    struct _node *father;
};

_node tree[10];

/* 动态化静态 */
int cnt =0;
_node * newnode(){
    _node *u = &tree[cnt++];
    u->p[0] = u->p[1]= u->father=NULL;
    return u;
}

/* 
 *     1
 *   2   3
 *  4  5    6
 * */


/*添加一个点,父亲为fa,数据为data */
void add_node_to_tree(_node *fa,int child,int data){
    fa->p[child] = newnode();
    fa->p[child]->data= data;
    fa->p[child]->father = fa;
}
int main(){

    _node *tmp_node ;

    _node *root = newnode();
    root ->data = 1;

    tmp_node = root;
    add_node_to_tree(tmp_node,0,2);
    add_node_to_tree(tmp_node,1,3);

    tmp_node = root->p[0];
    add_node_to_tree(tmp_node,1,6);

    tmp_node = root->p[0];
    add_node_to_tree(tmp_node,0,4);
    add_node_to_tree(tmp_node,1,5);

}
```


## 树的遍历

在就用树的结构解决问题时,往往要求按照某种次序获得树中全部结点的信息,这种操作叫作树的遍历,遍历的方法有多种,这里主要说:


 - 先序(根)遍历
 - 中序(根)遍历
 - 后序(根)遍历

**代码如下:**

```c
#include <cstdio>

struct _node {
    int data;
    struct _node *p[2];
    struct _node *father;
};

_node tree[10];

/* 动态化静态 */
int cnt =0;
_node * newnode(){
    _node *u = &tree[cnt++];
    u->p[0] = u->p[1]= u->father=NULL;
    return u;
}

/* 
 *     1
 *   2   3
 *  4  5    6
 * */


/*添加一个点,父亲为fa,数据为data */
void add_node_to_tree(_node *fa,int child,int data){
    fa->p[child] = newnode();
    fa->p[child]->data= data;
    fa->p[child]->father = fa;
}

/* 先序 */
void first(_node *t){
    if(t == NULL) return;
    printf("%d",t->data);
    first(t->p[0]);
    first(t->p[1]);
}


/* 中序 */
void middle(_node *t){
    if(t == NULL) return;
    middle(t->p[0]);
    printf("%d",t->data);
    middle(t->p[1]);
}

/* 后序 */
void last(_node *t){
    if(t == NULL) return;
    last(t->p[0]);
    last(t->p[1]);
    printf("%d",t->data);
}

int main(){
    _node *tmp_node ;

    _node *root = newnode();
    root ->data = 1;

    tmp_node = root;
    add_node_to_tree(tmp_node,0,2);
    add_node_to_tree(tmp_node,1,3);

    tmp_node = root->p[1];
    add_node_to_tree(tmp_node,1,6);

    tmp_node = root->p[0];
    add_node_to_tree(tmp_node,0,4);
    add_node_to_tree(tmp_node,1,5);

    printf("先序遍历:");
    first(root);
    printf("\n");


    printf("中序遍历:");
    middle(root);
    printf("\n");

    printf("后序遍历:");
    last(root);
    printf("\n");
}
```
