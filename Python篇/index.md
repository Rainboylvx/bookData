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

`abs()`                     绝对值
`all()`     全部为真
`any()`         至少有一为真
`ascii()`       无用，返回一个对象可打印字符串
`bin()` 转成二进制字串
`bool()`    测试一个对象的真假
`breakpoint()` 调试用，断点
`bytearray()`  返回一个新的 bytes 数组
`bytes()`   bytes 是 bytearray 的不可变版本
`callable()` 测试对象是否可call
`chr()`     返回对应的字符
`classmethod()` 不会，把一个方法封装成类方法
`compile()` 无用
`complex()` 复数
`delattr()` 删除指定属性
`dict()`    根据参数,创建一个新的字典
`dir()`     返回该对象的有效属性列表
`divmod()`  结果和 (a // b, a % b) 一致
`enumerate()` 返回一个枚举对象，可指定start
`eval()`  计算一个表达式
`exec()` 动态执行python代码
`filter(function,iterable)` 过滤
`float()` 返回浮点数
`format()` 格式化字符串
`frozenset()` 返回一个frozenset对象
`getattr()` 返回对象命名属性的值
`globals()`  返回表示当前全局符号表的字典
`hasattr()`
`hash()`
`help()`
`hex()`
`id()`
`__import__()`
`input()`
`int()`
`isinstance()`
`issubclass()`
`iter()`
`len()`
`list()`
`locals()`
`map()`
`max()`
`memoryview()`
`min()`
`next()`
`object()`
`oct()`
`open()`
`ord()`
`pow()`
`print()`
`property()`
`range()`
`repr()`
`reversed()`
`round()`
`set()`
`setattr()`
`slice()`
`sorted()`
`staticmethod()`
`str()`
`sum()`
`super()`
`tuple()`
`type()`
`vars()`
`zip()`
