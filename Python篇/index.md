从生苦短，我用python


- python3 68个内置函数
- python3 常用对象
    - dict
    - list
- python3 dfs bfs
- iterools 包
- 自己的封装的常用的代码
- 一句话代码片断
- 一个整数一个整数的读取

https://www.zybuluo.com/diyer22/note/310572

切片
在同一个切片操作中，不要同时使用start、end和stride尽量使用stride为正数，且不要带start和end索引的切割操作

PEP 08 https://python.freelycode.com/contribution/detail/47

## 内置函数

内置函数

|--------------------------------|------------------------------------|
| `abs()`                        | 绝对值                             |
| `all()`                        | 全部为真                           |
| `any()`                        | 至少有一为真                       |
| `ascii()`                      | 无用，返回一个对象可打印字符串     |
| `bin()`                        | 转成二进制字串                     |
| `bool()`                       | 测试一个对象的真假                 |
| `breakpoint()`                 | 调试用，断点                       |
| `bytearray()`                  | 返回一个新的 bytes 数组            |
| `bytes()`                      | bytes 是 bytearray 的不可变版本    |
| `callable()`                   | 测试对象是否可call                 |
| `chr()`                        | 返回对应的字符                     |
| `classmethod()`                | 不会，把一个方法封装成类方法       |
| `compile()`                    | 无用                               |
| `complex()`                    | 复数                               |
| `delattr()`                    | 删除指定属性                       |
| `dict()`                       | 根据参数,创建一个新的字典          |
| `dir()`                        | 返回该对象的有效属性列表           |
| `divmod()`                     | 结果和 (a // b, a % b) 一致        |
| `enumerate()`                  | 返回一个枚举对象，可指定start      |
| `eval()`                       | 计算一个表达式                     |
| `exec()`                       | 动态执行python代码                 |
| `filter(function,iterable)`    | 过滤                               |
| `float()`                      | 返回浮点数                         |
| `format()`                     | 格式化字符串                       |
| `frozenset()`                  | 返回一个frozenset对象              |
| `getattr()`                    | 返回对象命名属性的值               |
| `globals()`                    | 返回表示当前全局符号表的字典       |
| `hasattr(object,str)`          | 对象是否有str属性                  |
| `hash()`                       | 返回对象的hash值                   |
| `help([object])`               | 内置的帮助系统                     |
| `hex()`                        | 转成16进制的字符串                 |
| `id()`                         | 返回对象的“标识值”                 |
| `__import__()`                 |                                    |
| `input()`                      | 输入                               |
| `int()`                        | 转成整数                           |
| `isinstance(object,classinfo)` | 是否是对象实例                     |
| `issubclass(object,classinfo)` | 直接、间接或 虚拟) 子类则返回 True |
| `iter()`                       | 返回一个 迭代器对象                |
| `len()`                        | 长度                               |
| `list()`                       | 转成列表                           |
| `locals()`                     | 局部变量                           |
| `map()`                        | 映射                               |
| `max()`                        | 最大                               |
| `memoryview()`                 | 无用                               |
| `min()`                        | 最小                               |
| `next()`                       | 无用                               |
| `object()`                     | 无用                               |
| `oct()`                        | 8进制                              |
| `open()`                       | 打开文件                           |
| `ord()`                        | 返回字符对应的数字                 |
| `pow(bow,exp,mod)`             | 次幂                               |
| `print()`                      | 输出                               |
| `property()`                   |                                    |
| `range(start,stop,step)`       |                                    |
| `repr()`                       |                                    |
| `reversed()`                   | 反向                               |
| `round()`                      | 舍入到小数                         |
| `set()`                        | 集合                               |
| `setattr()`                    | 无用                               |
| `slice(start,stop,step)`       | 分割                               |
| `sorted()`                     | 排序                               |
| `staticmethod()`               |                                    |
| `str()`                        |                                    |
| `sum()`                        |                                    |
| `super()`                      | 元组                               |
| `tuple()`                      |                                    |
| `type()`                       |                                    |
| `vars()`                       |                                    |
| `zip()`                        | 聚合                               |


map
reduce
filter
