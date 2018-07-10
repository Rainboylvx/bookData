# python对拍脚本

在ccf给我们提供的系统noilinux(ps: ubuntu 14.04),自带有`python3.4`,于是我们可以使用`python3`来写对拍脚本,比使用`shell语言`要简单的多.


## 组成

 - 随机数据生成的程序`r`(rand,srand的使用)
 - 脚本文件(`test.py`)
 - 一定正确的程序,但运行慢的程序`a`(基本是搜索)
 - 要提交的程序,但可能是错的`b`

### 一.随机数据生成
    
看我写的 随机数的用法

### 二.脚本讲解

```python
# coding:utf-8

import os
cnt=1
while True:
    os.system('./r >input')
    os.system('./a < input >output.a')
    os.system('./b < input >output.b')
    if os.system('diff output.a output.b') != 0:
        print("error ans !")
        exit(1)
    else:
        print("test right {}".format(cnt))
        cnt++
```


## [对拍demo 下载地址]

具体看下面的对拍demo
