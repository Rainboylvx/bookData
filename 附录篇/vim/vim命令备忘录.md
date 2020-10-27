---
_id: "68bea82c7f"
title: vim命令备忘录
date: 2020-10-25 18:01
update: 2020-10-25 18:01
author: Rainboy
video: ""
titleEmojiTag: ":tv:"
---

@[toc]
## 如何保存退出

|-----------------------|---------------------------------------------|
| [[:q&#91;uit&#93; ]]  | 退出vim。进行更改后，此操作将失败。         |
| [[:q&#91;uit&#93;! ]] | 退出而不写。                                |
| [[:w]]               | 写入当前文件并退出。                        |
| [[:wq]]               | 写入当前文件并退出。                        |
| [[:wq!]]              | 写入当前文件并始终退出。                    |
| [[:wq {file}]]        | 写入{file}。如果不编辑最后一个则退出        |
| [[:wq!{文件}]]        | 写入{file}并始终退出。                      |
| [[ZZ]]                | 写入当前文件（如果已修改），然后退出。      |
| [[ZQ]]                | 退出当前文件并退出（与":q!"相同）。         |

## 进入插入模式

|----|-----------------------------------------------|
| [[a]]  | 在光标后附加文本[count]次。                   |
| [[A]]  | 在[count]次行的末尾附加文本。                 |
| [[i]]  | 在光标[count]次之前插入文本。                 |
| [[I]]  | 在[count]行中的第一个非空白之前插入文本。     |
| [[o]]  | 在光标下方开始新行并插入文本，重复[count]次。 |
| [[O]]  | 在光标上方换行并插入文本，重复[count]次。     |

## 删除文字
|---------------------------------|------------------------------------------------------|
| [[x]]                           | 删除光标下方和之后的[count]个字符                    |
| [[X]]                           | 删除光标前的[count]个字符                            |
| [[d {motion}]]                  | 删除{motion}移动的文本                               |
| [[dd]]                          | 删除[count]行                                        |
| [[d]]                           | 删除光标下方的字符，直到行尾                         |
| [[{Visual} x]]或 [[{Visual} d]] | 删除突出显示的文本（关于{Visual}，请参见选择文本）。 |
| [[{Visual} CTRL-H或             |
| [[{Visual}                      | 在选择模式下:删除突出显示的文本                      |
| [[{Visual} X或                  |
| [[{Visual} D                    | 删除突出显示的行                                     |
| [[:[range] d [elete]            | 删除[范围]行（默认:当前行）                          |
| [[:[range] d [elete] {count}    | 删除{count}行，以[range]开头                         |

## 更改（或替换）文本

r {char}	用{char}替换光标下的字符。
[R	进入插入模式，替换字符而不是插入
~	切换光标下方字符的大小写并将光标向右移动。如果给出[count]，则输入那么多字符。
~{动作}	switch case of {motion} text.
{Visual}~	Switch case of highlighted text

## Substituting

:[range]s[ubstitute]/{pattern}/{string}/[c][e][g][p][r][i][I] [count]	For each line in [range] replace a match of {pattern} with {string}.
:[range]s[ubstitute] [c][e][g][r][i][I] [count] :[range]&[c][e][g][r][i][I] [count]	Repeat last :substitute with same search pattern and substitute string, but without the same flags. You may add extra flags
The arguments that you can use for the substitute commands:
[c]  Confirm each substitution.  Vim positions the cursor on the matching
  string.  You can type:
      'y'      to substitute this match
      'n'      to skip this match
         to skip this match
      'a'      to substitute this and all remaining matches {not in Vi}
      'q'      to quit substituting {not in Vi}
      CTRL-E  to scroll the screen up {not in Vi}
      CTRL-Y  to scroll the screen down {not in Vi}.
[e]     When the search pattern fails, do not issue an error message and, in
  particular, continue in maps as if no error occurred.  
[g]  Replace all occurrences in the line.  Without this argument,
  replacement occurs only for the first occurrence in each line.
[i]  Ignore case for the pattern.  
[I]  Don't ignore case for the pattern.  
[p]  Print the line containing the last substitute.
Copying and Moving Text
"{a-zA-Z0-9.%#:-"}	Use register {a-zA-Z0-9.%#:-"} for next delete, yank or put (use uppercase character to append with delete and yank) ({.%#:} only work with put).
:reg[isters]	Display the contents of all numbered and named registers.
:reg[isters] {arg}	Display the contents of the numbered and named registers that are mentioned in {arg}.
:di[splay] [arg]	Same as :registers.
["x]y{motion}	Yank {motion} text [into register x].
["x]yy	Yank [count] lines [into register x]
["x]Y	yank [count] lines [into register x] (synonym for yy).
{Visual}["x]y	Yank the highlighted text [into register x] (for {Visual} see Selecting Text).
{Visual}["x]Y	Yank the highlighted lines [into register x]
:[range]y[ank] [x]	Yank [range] lines [into register x].
:[range]y[ank] [x] {count}	Yank {count} lines, starting with last line number in [range] (default: current line), [into register x].
["x]p	Put the text [from register x] after the cursor [count] times.
["x]P	Put the text [from register x] before the cursor [count] times.
["x]gp	Just like "p", but leave the cursor just after the new text.
["x]gP	Just like "P", but leave the cursor just after the new text.
:[line]pu[t] [x]	Put the text [from register x] after [line] (default current line).
:[line]pu[t]! [x]	Put the text [from register x] before [line] (default current line).
Undo/Redo/Repeat
u	Undo [count] changes.
:u[ndo]	Undo one change.
CTRL-R	Redo [count] changes which were undone.
:red[o]	Redo one change which was undone.
U	Undo all latest changes on one line. {Vi: while not moved off of it}
.	Repeat last change, with count replaced with [count].

## Moving Around

Basic motion commands:

```
        k              
      h   l          
        j             
```
|-------------|-------------------------------------------------|
| [[0]]       | 到行首。                                        |
| [[^]]       | 到行首第一个非空白字符。                        |
| [[$]]       | 到行尾 或 到下`[count - 1]` 行尾。              |
| [[f{char}]] | 到右边第`[count]`个`{char}` 字符上。            |
| [[F{char}]] | 到左边第`[count]`个`{char}` 字符上。            |
| [[;]]       | 重复最后一次`f,F` `[count]` 次。                |
| [[,]]       | 反向重复最后一次`f,F` `[count]` 次。            |
| [[-]]       | 到**下**`[count]`行的行首非空白字符             |
| [[+]]       | 到**上**`[count]`行的行首非空白字符             |
| [[G]]       | 到第`[count]`行, 默认第一行, 行首非空白字符。   |
| [[gg]]      | 到第`[count]`行, 默认最后一行, 行首非空白字符。 |
| [[w]]       | 到后边`[count]`单词开头                         |
| [[W]]       | 到后边`[count]`字串开头                         |
| [[b]]       | 到前边`[count]`单词开头                         |
| [[B]]       | 到前边`[count]`字符开头                         |
| [[e]]       | 到后边`[count]`单词结尾                         |
| [[E]]       | 到后边`[count]`字串结尾                         |
| [[ge]]      | 后退到单词的末尾[count]                         |
| [[gE]]       | 后退到WORD [count]的末尾                        |

这些命令移到单词或单词上。
单词由字母，数字和下划线组成，或由其他非空白字符组成，并用空格（空格，制表符， ）。可以使用" iskeyword"选项更改。

WORD由一系列非空白字符组成，并用空格分隔。空行也被认为是单词和单词。

## Screen movement commands

|----|--------------------------------------------------|
| zz | Center the screen on the cursor                  |
| zt | Scroll the screen so the cursor is at the top    |
| zb | Scroll the screen so the cursor is at the bottom |

## 搜索

/{pattern}[/]	Search forward for the [count]'th occurrence of {pattern}
/{pattern}/{offset}	Search forward for the [count]'th occurrence of {pattern} and go {offset} lines up or down.
/<CR>	Search forward for the [count]'th latest used pattern
//{offset}<CR>	Search forward for the [count]'th latest used pattern with new. If {offset} is empty no offset is used.
?{pattern}[?]<CR>	Search backward for the [count]'th previous occurrence of {pattern}
?{pattern}?{offset}<CR>	Search backward for the [count]'th previous occurrence of {pattern} and go {offset} lines up or down
?<CR>	Search backward for the [count]'th latest used pattern
??{offset}<CR>	Search backward for the [count]'th latest used pattern with new {offset}. If {offset} is empty no offset is used.
n	Repeat the latest "/" or "?" [count] times.
N	Repeat the latest "/" or "?" [count] times in opposite direction.
Selecting Text (Visual Mode)
To select text, enter visual mode with one of the commands below, and use motion commands to highlight the text you are interested in. Then, use some command on the text.

The operators that can be used are:
  ~  switch case
  d  delete
  c  change
  y  yank
  >  shift right 
  <  shift left 
  !  filter through external command 
  =  filter through 'equalprg' option command 
  gq  format lines to 'textwidth' length 
v	start Visual mode per character.
V	start Visual mode linewise.
<Esc>	exit Visual mode without making any changes
How to Suspend
CTRL-Z	Suspend Vim, like ":stop". Works in Normal and in Visual mode. In Insert and Command-line mode, the CTRL-Z is inserted as a normal character.
:sus[pend][!] or
:st[op][!]	Suspend Vim. If the '!' is not given and 'autowrite' is set, every buffer with changes and a file name is written out. If the '!' is given or 'autowrite' is not set, changed buffers are not written, don't forget to bring Vim back to the foreground later!

Daniel Gryniewicz / dang@fprintf.net
## 说明
翻译自[Vim Commands Cheat Sheet](http://www.fprintf.net/vimCheatSheet.html),有删减


