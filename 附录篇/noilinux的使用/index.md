---
_id: "d2d6eb524a"
title: "noilinux的配置"
date: 2020-11-05 19:19
update: 2020-11-05 19:19
author: Rainboy
video: ""
titleEmojiTag: ":tv:"
cover:  "/images/noiLinuxHead.png"
---

@[toc]

## 配置vim

### 说明
vim的配置有两种

 1. 默认的配置文件
 2. 用户配置文件:`~/.vimrc`

vim会先加载默认的配置，然后加载用户的配置（如果存在）

### 修改默认配置

1. 找到默认的配置文件的位置

 - [[ctrl]]+[[alt]]+[[t]] 打开终端，输入`vim`，回车，打开`vim`
 - 输入`:scriptnames`回车
 - 第一行显示的路径就是默认配置的路径，记住并退出vim（`:q`）

2. 输入`sudo vim <默认配置路径>`(noilinux的默认密码是`123456`),在文件末尾添加


```c
set nu                  " 开启行号
set rnu                 " 相对行号
set ts=4                " tab 占四个空格
set sw=4
set cin
colorscheme desert
im <c-l> <esc>A         " 到行尾 
im <c-h> <esc>I         " 到行首
ino ( ()<esc>i          " 括号自动补全
ino { {}<esc>i
ino [ []<esc>i
ino " ""<esc>i
ino ' ''<esc>i
```

改变终端字体为`Dejav Sans Mono`


## 修改`.bashrc`

在`~/.bashrc`的末尾添加

```bash
alias rm="echo not use rm"
function b(){
    g++ -g -o ${1%.*} $1
}
```
