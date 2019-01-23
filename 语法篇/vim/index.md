# vim 编辑器之神

vim配置地址: [https://rainboylvx.github.io/simple-vim-config/](https://rainboylvx.github.io/simple-vim-config/)

## 前言

`ccf`官方提供的IDE`GUIDE`很难用,有着各种的**BUG**,NOIP2016多个省份更是出现使用`GUIDE`不能调试的巨大BUG.

我们必须要有一个成熟的IDE来打代码,它必须有以下的特点:

 - 代码高亮
 - 括号补全
 - 括号匹配
 - 单词补全(这个可以不要)
 - 稳定高效

在`noilinux`(其时只是对ubuntu的简单封装)下,符合上面的条件的有(只适合C++语言):

 - Gedit
 - vim
 - Emacs

**Gedit**是一个很好的选择,开箱即用,只经过的简单的配置,就可以达到很好用的程度,但是有以下的问题

 - 不联网安装插件的话,不能使用括号匹配(noip考试时没有网络)
 - 效率低下,删除文字需要使用鼠标
 - 只有一种高亮(默认)

在经过一番权衡之后(多天),还是决定抛弃**Gedit**,选用更强大的**vim**.

**vim**和**Emacs**在程序员界,一个被称为**编辑器之神**,一个被称为**神之编辑器**,不仅是说明它们的强大,也是指要学习使用它们的难度.

在这里我们选用**vim**的原因有:

 - 作者(Rainboy),使用**vim**,对vim比较熟悉
 - **vim**只要很少的(`<100行`)配置,就可以完全满足我们打代码的需求
 - **vim**自带的高亮很好看,还很多
 - 省略100条

那么下面我们就开始时行**vim**的学习,我们将从以下的方面学习**vim**

 - vim的简单介绍与简单入门
 - vim的快键键讲解
 - vim的综合讲解

## 学习建议

VIM本身是一个非常难以完全掌握的软件，但是当你学会(基本可以使用)的时候,VIM会非常的好用.没有比这更好的编辑器了.

我们先要认清以下两个方面:

**VIM很难**:如果你以完全掌握VIM为目的的话.

**对我们来说VIM不难:**我们这里只要学习和平常打代码可以用到的VIM的知识.这并没有很多.但是你要做的就是坚持和思考.记住:VIM会成为你以后(高中时期)的唯一编辑器.

## FAQ

### 1.老师你讲的太多了,跟本记不住

> 我用自然选择的方法来学习vim，就是先用起来，如果想用什么功能就翻一下手册，当年基本使用熟练以后，整体的学习一下vim手册，你就会发现，很多东西一下子记住了，剩下没有记住的基本是你不需要的功能，因为每个人需要的功能都不完全一样，不需要掌握所有的功能，当你有一定的基础后，就可以自动识别出你需要的功能

> 玩游戏，vim-adventures这个网站就是一个在线游戏，通过游戏让你学习vim

### 2.我可以不用VIM吗

可以!如果你已经对某个编辑器十分的熟悉(打代码非常高效).


## vim 学习路线

```
                 +----------+
                 | 尝试vim  |
                 +----+-----+
                      |
                      v
                 +----------+
                 | vim游戏  |
                 +----+-----+
                      |
                      v
                 +----------+
                 | vim进阶  |
                 +----+-----+
                      |
                      v
   +----------------------------------------+
   | 平常使用vim,把vim当作唯一的文本编辑器  | <-----+
   +------------------+---------------------+       |
                      |                             |
                      |                             |
                      v                             |
                +-----------+                       |
                | vim超能力 +-----------------------+
                +-----------+
```

## 视频: 使用VIM前言

```video
[vim](vim-1.mp4)
```

## Learn Vim

Visit the following sites to learn more about Vim:

* [Learn Vim Progressively](http://yannesposito.com/Scratch/en/blog/Learn-Vim-Progressively/)
* [Vim Adventures](http://vim-adventures.com/)
* [Vimcasts](http://vimcasts.org)
* [Using Vim as a Complete Ruby on Rails IDE](http://biodegradablegeek.com/2007/12/using-vim-as-a-complete-ruby-on-rails-ide/)
* [Why, oh WHY, do those #?@! nutheads use vi?](http://www.viemu.com/a-why-vi-vim.html)
* [Byte of Vim](http://www.swaroopch.com/notes/Vim)
* [Screencast "17 tips for Vim" (in portuguese)](http://blog.lucascaton.com.br/?p=1081)
* [MinuteVim Tricks](https://www.youtube.com/user/MinuteVimTricks)
* [Join the Church of Vim, and you too can be a saint!](http://www.avelino.xxx/2015/03/church-vim)
* [Vim para noobs (in portuguese)](https://woliveiras.com.br/vimparanoobs/)
* [Vimbook (in portuguese)](https://cassiobotaro.gitbooks.io/vimbook/content/
