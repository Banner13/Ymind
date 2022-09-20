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

### 获取msys2
    方式一: 官网链接[点击](https://www.msys2.org/)
    方式二: 国内镜像源[点击](https://mirrors.tuna.tsinghua.edu.cn/msys2/distrib/)
    注: 该软件即使不翻墙也能获取，如官网获取失败可从镜像源下载。

### 安装msys2
    双击安装包，一路点击 Next 即可。
    注：请注意安装的路径，后续配置需要引用改路径，本文采用 D:/msys2/ 为例。

### msys2的配置
#### msys2更新下载源
    国内用户在使用 pacman 时，若使用默认下载源，可能下载速度会十分感人，可跟随以下步骤切换到国内下载源。
    以下 "etc/" 路径均在 "D:/msys2/etc" 下。
    引用 清华大学开源软件镜像站->相关链接->使用帮助->msys2->MSYS2 镜像使用帮助[](https://mirrors.tuna.tsinghua.edu.cn/help/msys2/)
    {
        pacman 的配置
        编辑 /etc/pacman.d/mirrorlist.mingw32 ，在文件开头添加：
        Server = https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/i686
        编辑 /etc/pacman.d/mirrorlist.mingw64 ，在文件开头添加：
        Server = https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/x86_64
        编辑 /etc/pacman.d/mirrorlist.ucrt64 ，在文件开头添加：
        Server = https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/ucrt64
        编辑 /etc/pacman.d/mirrorlist.clang64 ，在文件开头添加：
        Server = https://mirrors.tuna.tsinghua.edu.cn/msys2/mingw/clang64
        编辑 /etc/pacman.d/mirrorlist.msys ，在文件开头添加：
        Server = https://mirrors.tuna.tsinghua.edu.cn/msys2/msys/$arch
        然后执行 pacman -Sy 刷新软件包数据即可。
    }

#### msys2配置到windows右键快捷方式
    1.  在 "运行"(Ctrl+R) 中输入 regedit 打开注册表编辑器
        在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\" 下，
        右击 "shell" 新建项, 命名 "msys2" ，添加该项后会显示在右键快捷菜单栏，但点击后无反应。

    2.  在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\msys2\" 下，
         右击 "msys2" 新建项,命名 "command" ，选中 "command" 后，修改默认值为 msys2 的路径。
         例如 "D:/msys2/msys2.exe"，此时右键便可打开 msys2 。

    3.  在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\msys2\" 下，
         右击 "msys2" 新建字符串值,命名 "Icon" ，修改 "Icon" 默认值为 msys2 的路径下的 "msys2.ico"。
         为 msys2 添加图标。
    
#### msys2在指定路径打开
    经过上述配置后，会发现每次打开 msys2 后，路径总是在主目录下即 "~/",
    但很多时候我们都想在打开 msys2 的地方进行操作，所以有两种策略可以实现:
    以下策略均是通过修改注册表中的 "msys2/command" 的默认值实现。

    1.  修改 "command" 值为 "D:/msys2/usr/bin/mintty.exe /bin/bash -lc 'cd "$(cygpath "%V")"; export CHERE_INVOKING=1; exec bash --login -i'"
    2.  修改 "command" 值为 "D:/msys2/msys2_shell.cmd -msys2 -here "
    注: 建议使用第二种方法

#### msys2使用 windows 的环境变量
    在 windows 环境变量中新建一个变量，命名为 "MSYS2_PATH_TYPE" , 值为 "inherit"

### 安装常用软件
#### git make cmake vim man
    pacman -S git make cmake vim
#### gitk
    pacman -S mingw-w64-x86_64-tk
    添加 "D:/msys2/mingw64/bin" 到环境变量 PATH , 可以通过在 ~/.bashrc 最后添加 "PATH=$PATH:D:/msys2/mingw64/bin" 实现。
    添加环境变量后重新打开 msys2 或，"source ~/.bashrc" 即可。
#### mingw64
    国内用户下载这个贼慢，在这里你只需要 "pacman -S mingw-w64-x86_64-toolchain" ,
    在 msys2 中输入 "gcc -v " 验证。
#### arm-gcc
    pacman -S mingw64/mingw-w64-x86_64-arm-none-eabi-gcc

### 其他
    // 这个是笔者用于VScode的Shell终端 使用 "-msys2 -defterm -here -no-start"

#### ssh 方式提示 no matching host key type found
    etc > ssh 文件夹下找到 ssh_config 文件
    添加
    # 注意这里的 xxx.com 是没有 https:// 的
    # 如 https://github.com/， 填写 github.com 即可（最后的斜杆也不能要）。
    Host xxx.com
    HostkeyAlgorithms +ssh-rsa
    PubkeyAcceptedAlgorithms +ssh-rsa

#### 下载应用命令
    pacman --help 获取帮助

