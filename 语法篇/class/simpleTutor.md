# 类的简单学习

类是C++的面向对象的部分,主要使用`class`关键字(`struct`也可以).类是对数据的抽象.简单的来说包含:**数据**和**方法**两个方面.

 - 对事物的数据抽象
 - 包含**数据**和**方法**两个部分


## 声明

现实生活中有一只猫,猫有名字颜色,重量,年龄等属性,同样也会跑,睡,叫等动作(方法),那我们就用C++的类来抽象一个猫.


### 使用struct

```c
#include <iostream>
using namespace std;

//声明猫类
struct _cat {
    string color;//颜色
    string name;
    int weight;//重复
    int postionX; //位置
    int postionY;

    void speak() {
        cout << "meao" << endl;
    }

    void  run(int x,int y){
        postionX += x;
        postionY += y;
    }

    void eat(int food){
        weight +=food;
        cout << "i am eating" << endl;
    }

};

int main(){

    //定义
    _cat Cat;

    //赋值
    Cat.color = "black";
    Cat.weight = 5;
    Cat.postionX = 0;
    Cat.postionY = 0;

    //使用方法
    Cat.speak();

    //调用方法:改变内部的值
    cout << "Cat now at " << Cat.postionX <<" " <<Cat.postionY << endl;
    Cat.run(5,4);
    cout << "Cat now at  " << Cat.postionX <<" " <<Cat.postionY << " after run" << endl;

    cout << "Cat's weight is " << Cat.weight << endl;
    Cat.eat(1);
    cout << "Cat's weight is " << Cat.weight << " after eat" <<endl;

    //手动改变内部的值
    Cat.weight = 10;
    cout << "Cat's weight is " << Cat.weight << endl;
    return 0;
}

```

### 使用class



`class`其时本质上和`struct`一样的,只是我们叫`class`这样可以显得更规范.

类有三种数据属性(其实有很多):

    - public:公有成员,可以被外部和自己访问
    - private:私有成员,不可以被外部访问,只能自己访问
    - protected:可以被派生类访问,不能被外部访问(了解即可)

如果一个数据成员没有被指明是哪种属性,struct默认是`public`,class默认是`private`

```c
#include <iostream>
using namespace std;

//声明猫类
class _cat {
    int speed; //默认为private,说明下面的数据不可以被外部访问
    public:  //这里要加上public,说明下面的数据可以被外部访问
        string color;//颜色
        string name;
        int weight;//重复
        int postionX; //位置
        int postionY;

        void speak() {
            cout << "meao" << endl;
        }

        void  run(int x,int y){
            postionX += x;
            postionY += y;
        }

        void eat(int food){
            weight +=food;
            cout << "i am eating" << endl;
        }
    private: //这里要加上private,说明下面的数据不可以被外部访问
        int year; // 年龄

};

int main(){

    //定义
    _cat Cat;

    //赋值
    Cat.color = "black";
    Cat.weight = 5;
    Cat.postionX = 0;
    Cat.postionY = 0;

    //使用方法
    Cat.speak();

    //调用方法:改变内部的值
    cout << "Cat now at " << Cat.postionX <<" " <<Cat.postionY << endl;
    Cat.run(5,4);
    cout << "Cat now at  " << Cat.postionX <<" " <<Cat.postionY << " after run" << endl;

    cout << "Cat's weight is " << Cat.weight << endl;
    Cat.eat(1);
    cout << "Cat's weight is " << Cat.weight << " after eat" <<endl;

    //手动改变内部的值
    Cat.weight = 10;
    cout << "Cat's weight is " << Cat.weight << endl;

    //error,不能访问private数据
    // cout << Cat.speed;
    // Cat.year = 3;
    return 0;

}
```


## 构造函数

创建一个类类型的对象的时候,编译器会自动使用一个构造函数来初始化该对象.

构造函数量一个特殊的,与类同名的成员函数.用于给每个数据成员设定适当的初始值.

 - 如果用户没有写构造函数,会自动添加一个默认的构造函数
 - 可以根据参数的不同自动选择不同的构造函数
    - 参数不同的原则:**参数列表的顺序与类型**


```c
#include <iostream>
#include <string>

using namespace std;

//声明猫类
struct _cat {

    _cat(){ // 空,不需要返回类型
    }

    _cat(string c){ // 一个参数
        color = c;
    }

    _cat(string c,int w){ // 两个参数
        color = c;
        weight = w;
    }
    int weight;
    string color;
};

int main(){
    _cat cat1("red");
    cout << "cat1.color:" << cat1.color << endl;

    _cat cat2("blue",3);
    cout << "cat2.color:" << cat2.color << endl;
    cout << "cat2.weight:" << cat2.weight << endl;

    _cat cat3; // 空 这样cat3()声明,是错的


    return 0;
}

```


### 构造函数初始化列表

构造函数初始化列表由成员名带括号的初始值组成，跟在构造函数的形参表之后，并以冒号开头.


```c
#include <iostream>
#include <string>

using namespace std;

//声明猫类
struct _cat {

    _cat(){}  //空的构造函数,你可以把这一句注释掉看看,想想为什么会出现这种错误注[1]
    _cat(int w):weight(w){}
    _cat(string c):color(c){}
    _cat(int w,string c):weight(w),color(c){}
    int weight;
    string color;
};

int main(){
    _cat cat1;
    _cat cat2(3);
    _cat cat3("red");
    _cat cat4(3,"red");

    return 0;
}

```

## 小的题目




## 注

注[1]:如果用户自己写了构造函数,编译器就不会提供默认的构造函数,即使是空的构造函数
