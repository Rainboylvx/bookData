---
_id: "0aa04ba924"
title: 软件安装
date: 2020-10-27 09:38
update: 2020-10-27 09:38
author: Rainboy
---

## 1. 设置网络与屏幕缩放

屏幕缩放

 - 点击屏幕右下角**应用程序**按钮
 - 找到**设置**点击
 - **显示器** 缩放 [[200%]]

无线网络: 点击右上角 wifi图标


## 2 打开终端与简单的使用


- [[ctrl]]+[[alt]]+[[t]]打开终端(terminal)
- [[右键]] --> [[首选项]] --> [[外观]] 改变字体与字体大小
- [[F11]] 全屏
- [[ctrl]] +[[shift]] + [[t]] 新建标签页
- 选中+[[右键]] 弹出的菜单上选复制 可以复制文字
- [[ctrl]] + [[shift]] +[[v]] 粘贴
- [[ctrl]] + [[+]]([[ctrl]]+[[shift]]+[[=]]) 放大终端字体
- [[ctrl]] + [[-]] 缩小终端字体

## 3 设置软件源与下载常用软件

软件源改成国内
```bash
sudo sed -i "s/cn.archive.ubuntu.com/mirrors.aliyun.com/g" /etc/apt/sources.list
sudo sed -i "s/archive.ubuntu.com/mirrors.aliyun.com/g" /etc/apt/sources.list
sudo apt update
```

下载常用的软件
```bash
sudo apt install -y git gcc g++ xsel curl wget cgdb tree trash-cli zsh lua5.3
```

## 4 解决不完整的语言支持

[[应用程序]]-->[[语言支持]]-->[[安装]]

下面的方法没有经过验证

```bash
sudo apt install language-pack-zh-han
sudo apt install $(check-language-support)
```

## 5 安装oh-my-zsh

目的：更好用的终端

```
sudo chsh -s /bin/zsh
```

安装oh-my-zsh

```
sh -c "$(curl -fsSL 'https://gitee.com/Rainboy/codes/p8trde79flmaj6kyuobqh63/raw?blob_name=ohmyzsh' | sed 's/\r//')"
```
安装相应的插件

- z.lua 目录快速跳转
- zsh-autosuggestions : 命令行命令键入时的历史命令建议
- zsh-syntax-highlighting: 命令行语法高亮插件

注意安装时，如果可能要`yes`，看提示

```bash
git clone --depth 1 git@git.zhlh6.cn:skywind3000/z.lua ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/z.lua
git clone --depth 1 git@git.zhlh6.cn:zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
git clone --depth 1 git@git.zhlh6.cn:zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
```

在`.zshrc`中修改，大概71行

```bash
plugins=(git z.lua zsh-syntax-highlighting zsh-autosuggestions)
```

## 6 输入法设定

- [[win]] + [[space]] 可以切换输入法
- [[应用程序]] --> [[设置]]-->[[键盘快捷键]]-->[[打字]] 可以设定输入法的切换快捷键 为 [[ctrl]] + [[space]]

## 7 工作区

 - [[ctrl]] + [[alt]] + [[方向键上下]] 切换工作区
 - 在最后一个工作区打开窗口，然后会新建一个新的工作区

## 8 安装 chrome

```
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb
```
## 安装 wps

自行搜索

## qq


```
git clone https://gitee.com/wszqkzqk/deepin-wine-for-ubuntu.git
cd deepin-wine-for-ubuntu
chmod +x install_2.8.22.sh
./install_2.8.22.sh
wget https://mirrors.aliyun.com/deepin/pool/non-free/d/deepin.com.qq.im/deepin.com.qq.im_9.1.8deepin0_i386.deb
sudo dpkg -i deepin.com.qq.im_9.1.8deepin0_i386.deb
# 默认安装完成后，打开QQ和微信时无法最小化，需结合Topicons plus使用。
sudo apt-get install gnome-shell-extension-top-icons-plus
```

[deepin wine for ubuntu](https://gitee.com/wszqkzqk/deepin-wine-for-ubuntu)

## 参考/引用

 - [写给工程师的 ubuntu20.04 最佳配置指南](https://sspai.com/post/60411)

