---
_id: "e3f68024f0"
title: pythonic
date: 2020-12-03 16:51
update: 2020-12-03 16:51
author: Rainboy
---

@[toc]
## list

### divide

```
from math import ceil
lst = [1,2,3,4,5]
size = 2
[lst[i*size : (i+1)*size] for i in range(0,ceil(len(lst) / size))]
# [[1,2],[3,4],[5]]
```

### 过滤false

```
lst  =[None, '',1,False,[]]
r = list(filter(bool,lst))
```

### 最长的序列

```
r= max([1],[1,2],[1,2,3],key = lambda v : len(v))
```

### 出现次数最多的元素

```
r = max([1,1,1,2,3],key = lambda v: lst.count(v))
```

### 按条件进行分组

```
l = [1,2,3,4]
r = [ [ i for i l if i < x] , [ i for i in l if not i < x]]
```

- 等分`[ lst[i * size:(i+1)*size] for i in range(0,ceil(len(lst)/size))]`

## 字典 Dick

### 字典键值颠倒


```python
d = {y:x for x,y in dict1.items()}
```

### 合并

```
{**dict1,**dict2}
```

### 转换为Dict

```python
dict(zip(['a','b'],[1,2]))
dict([('a',1),('b',2)])
```

## 数学 Math

 - `divmod(10,3) => (3,1)`
 - 计算表达式`eval('1+2+3')`
 - `hash("123")`,`hash([1,2,3])`
 - `int(x,base=10)`
 - `pow(a,n,mod) => a^n % mod`
 - `num ** 0.5`


## 其它

 - 切片对象 `a=[1,2,3,4]; a[slice(0,5,2)]`
 - `sort(a,reverse=True)`
 - `sort(a,key=lambda : xx)`
 - flatten ?

## 参考
 - [20个python小例子 zhihu](https://zhuanlan.zhihu.com/p/142258159)
- [列表和字典，30个进阶用法](https://mp.weixin.qq.com/s?__biz=MzUzMjczMDQ5OA==&mid=2247487288&idx=1&sn=b79102918047a63789237de7575dafce&exportkey=AQ%2B6oJY%2Fi2%2F%2F8VgNlYkmzsA%3D&pass_ticket=IUoEhUsObSzVHcANDehBXLIGUnXkYpyD4BGaK6SzDY2zbKKHl4NhUErKLrrFO%2FKi&wx_header=0)
