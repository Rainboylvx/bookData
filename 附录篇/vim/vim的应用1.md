---
_id: "ba1005548d"
title: newVim
date: 2020-09-27 11:16
update: 2020-09-27 11:16
author: Rainboy
cover: https://user-images.githubusercontent.com/21299158/34350122-484a64da-ea50-11e7-9576-97fd432a8d65.png
---



@[toc]

## 模式
什么时候可以看

- 把[vim手册](https://user-images.githubusercontent.com/21299158/34350122-484a64da-ea50-11e7-9576-97fd432a8d65.png) 的图片保存，并设为桌面壁纸
- 如果忘记了/想要查看某个快捷键，就查看[123](@@@./vimBetter.md@@@)



```viz-dot
graph g {
    node[shape=rect style=filled fillcolor=white colorscheme=accent8 ];
    edge[minlen=3]
    a--b[xlabel="v,V\nctrl-v"];
    b--c[style=dashed color=gray];
    a--c[label="i,a,o"];
    a--"cmd"[label=":" minlen=2];
    {
        rank=same;
        b,c;
    }
    {
        rank=same;
        a,cmd;
    }
    cmd[label="命令模式"]
    a[label="普通 normal"]
    b[label="可视 visual"]
    c[label="插入 insert"]
}
```

vim有以上的几种模式,每种模式的作用如下:

 - normal
 - command
 - visual
 - insert

## 写入与保存

输入命令: `vim 1.txt` 打开一个`1.txt`的文件

输入：[[i]] 进入插入模式,此时可以写文字了

输入一名话: `hello world`

按键：[[Esc]]进入normal模式

输入： [[:]] 然后输入[[w]] 保存,再输入[[q]]退出

- [[w]] write
- [[q]] quit

## 综合的应用

天下武功，唯快不破。

使用vim，在别人写一人份代码的时间下，你写了三份代码，那你将具有巨大的优势。

下面针对一个roj上的最短路的模板题目，给同学们讲解一下vim的应用


我们写一个代码到度用vim快在哪里？

ddp 交换两行
dw
r替换一个字符
5l
5w
gg 第一行
G 最后一行
5j 到下面的5行
5k 到上面的5行

f
;
F

w work
e end
b back
zt
zz
zb
u
c-u
c-f
'.
H
M
L
x
/ 搜索






## 常用的表

- h j k l -> ← ↓ ↑ →
- i -> insert 模式 插入文本 ESC 返回 Normal 模式 (该模式下所有按键都为功能键)
- a -> 在光标后插入
- x -> 删除当前光标所在的一个字
- v -> 按 v 键后 移动光标可选中文本
- d -> 删除当前光标文本 或选中的文本
- dd -> 删除当前行 并保存到剪切板
- D -> 删除当前光标到行末尾
- y -> 拷贝当前光标文本 或选中的文本
- yy -> 拷贝当前行
- y$ -> 拷贝当前光标到行尾
- p -> 小写 p 在光标之后插入拷贝项
- P -> 大写 P 在光标之前插入拷贝内容
- o -> 到当前行行尾 新建一行 插入
- O -> 到当前行行头 新建一行 插入
- zz -> 光标所在行垂直居中于屏幕
- zt -> 光标所在行置顶于屏幕
- gg -> 到文件第一行
- G -> 到文件行尾
- u -> 撤销操作
- w -> w(小写) 到下一个单词的开头
- e -> e(小写) 到下一个单词的结尾
- ve -> 快速选中一个单词
- b -> b (小写) 到上一个单词的词首
- / -> 快速检索文件内词组 回车键确定 n 匹配下一个 N 匹配上一个
- % -> 定位与光标所在括号相对应的另一半,(使用前要将光标定位在某个括号上)
- 0 -> 到行首
- ^ -> 到本行第一个不是blank字符的位置（所谓blank字符就是空格，tab，换行，回车等）
- $ -> 到行尾
- < > -> noraml 下光标选中的前后缩进
- r -> 替换光标所选中的字符
- R -> 替换光标所到之处的字符
- {} -> 快速跳转到上/下一个空行的位置
- cw -> 替换从光标所在位置后到一个单词结尾的字符
- ctl-f -> 向下翻页
- ctl-b -> 向后翻页

修改 N 个位置的单词 /搜索的单词 -> cgn (修改单词) -> . (输入点操作)
