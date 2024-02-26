    支持原创，转发请备注来源[src](https://github.com/Banner13/BannerHome)
[TOC]
# windows环境
## msys2
### msys2介绍
    msys2 是一种在 windows 平台上模拟 linux 环境的技术，
    如果你想在 windows 环境下运行 linux 应用，那它一定是一个好的选择。
    注：windows 环境下运行的 linux 应用，是 xxx.exe ,即该应用的 windows 版。

### msys2的优势
    类 linux 的开发环境，使用 pacman 包管理器，你可以简单轻松的获取许多工具(还解决的翻墙的苦恼)。
    常用工具如 linux下的 grep 、 find 等命令，还有 mingw64 、cmake 、 git 等。 部署简单易使用。


#### msys2配置到windows右键快捷方式
参考[[develop/Environment/Windows/manual#添加应用到右键快捷栏|添加应用到右键快捷栏]]
    
#### msys2在指定路径打开
    经过上述配置后，会发现每次打开 msys2 后，路径总是在主目录下即 "~/",
    但很多时候我们都想在打开 msys2 的地方进行操作，所以有两种策略可以实现:
    以下策略均是通过修改注册表中的 "msys2/command" 的默认值实现。

    1.  修改 "command" 值为 "D:/msys2/usr/bin/mintty.exe /bin/bash -lc 'cd "$(cygpath "%V")"; export CHERE_INVOKING=1; exec bash --login -i'"
    2.  修改 "command" 值为 "D:/msys2/msys2_shell.cmd -msys2 -here "
    注: 建议使用第二种方法

#### msys2使用 windows 的环境变量
    在 windows 环境变量中新建一个变量，命名为 "MSYS2_PATH_TYPE" , 值为 "inherit"

### 其他
    // 这个是笔者用于VScode的Shell终端 使用 "-msys2 -defterm -here -no-start"

### Msys2下常用软件
[[develop/ToolsChain/Pacman/tip#下载应用命令|Pacman下载]] git make cmake vim tree
