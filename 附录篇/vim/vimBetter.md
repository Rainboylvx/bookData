---
_id: "vimBetter"
title: vimBetter
date: 2020-09-27 12:21
update: 2020-09-27 12:21
author: Rainboy
---

# vim进阶

学会了基本的命令后,我们来学习更复杂一点vim命令,我们按分类来学习

记住,下面所有的命令都是在normal模式下使用,如果不知道自己在哪种模式下,按几下Esc键.

## 移动

| 操作    | 模式   | 含义                   |
|---------|--------|------------------------|
| `hjkl`  | normal | 移动,左下上右          |
| `0`     | normal | 到行首                 |
| `^`     | normal | 到行首(非空白)         |
| `$`     | normal | 到行尾                 |
| `g_`    | normal | 到行尾(非空白)         |
| `:n/nG` | normal | 到第n行行首            |
| `n+`    | normal | 下移n行                |
| `n-`    | normal | 上移n行                |
| `gg`    | normal | 第一行                 |
| `G`     | normal | 最后一行               |
| `w/W`   | normal | 下一个单词的开头       |
| `b/B`   | normal | 上一个单词的开头       |
| `e/E`   | normal | 下一个单词的结尾       |
| `)`     | normal | 到句首                 |
| `(`     | normal | 到句尾                 |
| `}`     | normal | 到段首                 |
| `{`     | normal | 到段首                 |
| `%`     | normal | 到另一个匹配的括号处   |
| `fx/Fx` | normal | 当前向前/向后查找字符x |
| `\.`    | normal | 跳到最后一次修改的地方 |
| `'.`    | normal | 跳到最后一次修改行     |
| `H`     | normal | 到屏幕顶部             |
| `M`     | normal | 到屏幕中部             |
| `L`     | normal | 到屏幕底部             |
| `nH`    | normal | 到屏幕顶部下的n行      |
| `nL`    | normal | 到屏幕底部上的n行      |

## 视频:移动

```video
[vim](vim4-1-移动.mp4)
```

## 插入

| 操作 | 模式   | 含义                                   |
|------|--------|----------------------------------------|
| i    | normal | 在当前字符前插入                       |
| I    | normal | 在当前行首(非空白)前插入               |
| a    | normal | 在当前字符后插入                       |
| A    | normal | 在当前行尾前插入                       |
| o    | normal | 在下面插入一行                         |
| O    | normal | 在上面插入一行                         |
| r    | normal | 替换当前字符                           |
| R    | normal | 进入替换模式                           |
| gR   | normal | 进入虚拟替换模式                       |
| s    | normal | 删除光标后的一个字符，然后进入插入模式 |
| S    | normal | 删除光标所在的行，然后进入插入模式     |
| cw   | normal | 删除一个word,并进入插入模式            |
| cc   | normal | 删除一行,并进入插入模式,等S            |


## 视频:插入

```video
[vim](vim4-2-插入.mp4)
```

## 复制

| 操作 | 模式   | 含义                        |
|------|--------|-----------------------------|
| yy   | normal | 复制一行                    |
| ye   | normal | 复制一个单词                |
| yw   | normal | 复制到下一个单词的开头前    |
| yl   | normal | 复制一个字符                |
| y$   | normal | 复制到到行尾                |
| y^   | normal | 复制到到行首,不包括空白字符 |
| y0   | normal | 复制到到行首,包括空白字符   |


### 更强的复制

| 操作     | 模式   | 含义                                                               |
|----------|--------|--------------------------------------------------------------------|
| y        | normal | 复制在可视模式下选中的文本。                                       |
| yy or Y  | normal | 复制整行文本。                                                     |
| y[n]w    | normal | 复制一(n)个词。                                                    |
| y[n]l    | normal | 复制光标右边1(n)个字符。                                           |
| y[n]h    | normal | 复制光标左边1(n)个字符。                                           |
| m,ny<cr> | normal | 复制m行到n行的内容。                                               |
| y1G或ygg | normal | 复制光标以上的所有行。                                             |
| yG       | normal | 复制光标以下的所有行。                                             |
| yaw和yas | normal | 复制一个词和复制一个句子，即使光标不在词首和句首也没关系。         |
| P        | normal | 在光标之后粘贴。                                                   |
| p        | normal | 在光标之前粘贴。                                                   |

总结:

```
y[数字][范围]
[数字]y[范围]
```

## 视频:复制

```video
[vim](vim4-3-复制.mp4)
```


## 替换/删除

| 操作     | 模式   | 含义                                                               |
|----------|--------|--------------------------------------------------------------------|
| R        | normal | 替换模式                                                           |
| r        | normal | 替换字符                                                           |
| d        | normal | 删除（剪切）在可视模式下选中的文本。                               |
| dd       | normal | 删除1行                                                            |
| dw       | normal | 删除1个单词(到下一个单词开头)
| de       | normal | 删除1个单词(到本单词结尾)
| d2j      | normal | 向下删除2行                                                        |
| d2k      | normal | 向上删除2行                                                        |
| d2l      | normal | 向左删除2个字符                                                    |
| d$ or D  | normal | 删除（剪切）当前位置到行尾的内容。                                 |
| d[n]w    | normal | 删除（剪切）1(n)个单词                                             |
| d[n]l    | normal | 删除（剪切）光标右边1(n)个字符。                                   |
| d[n]h    | normal | 删除（剪切）光标左边1(n)个字符。                                   |
| d0       | normal | 删除（剪切）当前位置到行首的内容                                   |
| [n]dd    | normal | 删除（剪切）1(n)行。                                               |
| `:m,nd<cr>` | normal | 剪切m行到n行的内容。                                               |
| d1G或dgg | normal | 剪切光标以上的所有行。                                             |
| dG       | normal | 剪切光标以下的所有行。                                             |
| daw和das | normal | 剪切一个词和剪切一个句子，即使光标不在词首和句首也没关系。         |
| dff  | normal | 这是一个比较高级的组合命令，它将删除当前位置 到下一个f之间的内容。 |

```
d[范围]
```
 - `:s/old/new` - 用new替换当前行第一个old。
 - `:s/old/new/g` - 用new替换当前行所有的old。
 - `:n1,n2s/old/new/g` - 用new替换文件n1行到n2行所有的old。
 - `:%s/old/new/g` - 用new替换文件中所有的old。
 - `:%s/^/xxx/g` - 在每一行的行首插入xxx，^表示行首。
 - `:%s/$/xxx/g` - 在每一行的行尾插入xxx，$表示行尾。
 - 所有替换命令末尾加上c，每个替换都将需要用户确认。 如：%s/old/new/gc，加上i则忽略大小写(ignore)。

```
:[范围]/strA/strB/
```
还有一种比替换更灵活的方式，它是匹配到某个模式后执行某种命令，
语法为 `:[range]g/pattern/command`
例如 `:%g/^ xyz/normal dd`。
表示对于以一个空格和xyz开头的行执行normal模式下的dd命令。
关于range的规定为：

如果不指定range，则表示当前行。
m,n: 从m行到n行。

 - 0: 最开始一行（可能是这样）。
 - $: 最后一行
 - .: 当前行
 - %: 所有行

## 视频:删除

```video
[vim](vim4-4-删除.mp4)
```

## 卷屏

| 操作  | 模式   | 含义            |
|-------|--------|-----------------|
| c-u   | normal | 上翻半屏        |
| c-d   | normal | 下翻半屏        |
| c-b   | normal | 上翻一屏        |
| c-f   | normal | 下翻一屏        |
| c-e   | normal | 向上一行        |
| c-y   | normal | 向下一行        |
| (n)zt | normal | (n)当前行到顶部 |
| (n)zz | normal | (n)当前行到中部 |
| (n)zb | normal | (n)当前行到底部 |

## 视频:卷屏

```video
[vim](vim4-5-卷屏.mp4)
```


## 查找

| 操作   | 模式   | 含义                   |
|--------|--------|------------------------|
| */#    | normal | 向前/向后查找当前单词  |
| fx/Fx  | normal | 当前向前/向后查找字符x |
| :/word | normal | 查找word单词           |
| n/N    | normal | 向前/向后查找/的单词   |

 - /something: 在后面的文本中查找something。
 - ?something: 在前面的文本中查找something。
 - /pattern/+number: 将光标停在包含pattern的行后面第number行上。
 - /pattern/-number: 将光标停在包含pattern的行前面第number行上。
 - n: 向后查找下一个。
 - N: 向前查找下一个

## 视频:查找

```video
[vim](vim4-6-查找.mp4)
```

## 打开/保存/退出

| 操作         | 模式   | 含义               |
|--------------|--------|--------------------|
| vim filename |        | 打开/新建 filename |
| :w           |        | 保存               |
| :w filename  |        | 保存+文件名        |
| ZZ           | normal | 保存退出           |

## 视频:打开/保存/退出

```video
[vim](vim4-7-打开-保存-退出.mp4)
```

## 缩进

| 操作 | 模式   | 含义             |
|------|--------|------------------|
| ==   | normal | 对齐             |
| >>   | normal | 向右缩进一个宽度 |
| <<   | normal | 向左缩进一个宽度 |


## 其它


| 操作 | 模式   | 含义 |
|------|--------|------|
| ==   | normal | 对齐 |
