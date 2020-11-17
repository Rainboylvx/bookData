无穷循环

- count(start,[step]),数数
- cycle([p]) 循环
- repeat(p,[p]) 重复

高效for
根据最短输入序列长度停止的迭代器：


- accumulate([],func) 累积
- chain([],[]) 链接
- chain.from_iterbale([],[]) 链接
- compress([d],[s]),  d[0] if s[0] 压缩
- dropwhile(pred, seq)  seq[n], seq[n+1], ... 从pred首次真值测试失败开始
- fliterfalse(pred, seq)  seq中pred(x)为假值的元素，x是seq中的元素
- groupby([],key) 分组
- starmap map()函数的*a版本
- takewhile(pred, seq ) seq[0], seq[1], ..., 直到pred真值测试失败
- tee
- zip_longest()

排列组合


迭代器

实参

结果

|---------------------------------|----------------------------------------------------|
| product()                       | p, q, ... [repeat=1] 笛卡尔积，相当于嵌套的for循环 |
| permutations()                  | p[, r]                                             | 长度r元组，所有可能的排列，无重复元素 |
| combinations()                  | p, r                                               | 长度r元组，有序，无重复元素           |
| combinations_with_replacement() | p, r                                               | 长度r元组，有序，元素可重复           |

```
product('ABCD', repeat=2)
AA AB AC AD BA BB BC BD CA CB CC CD DA DB DC DD
```

```
permutations('ABCD', 2)
AB AC AD BA BC BD CA CB CD DA DB DC
```

```
combinations('ABCD', 2)
AB AC AD BC BD CD
```

```
combinations_with_replacement('ABCD', 2)
AA AB AC AD BB BC BD CC CD 
```
