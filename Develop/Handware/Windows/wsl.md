[TOC]

[wsl](https://docs.microsoft.com/zh-cn/windows/wsl/about)


### windows下的linux 开发环境

	获取 ubuntu发行版安装包
	解压到安装位置
	双击.exe文件进行安装(如果显示找不到路径，可能是因为之前安装卸载过)
	输入用户、密码即可
	rootfs 路径在，安装位置的磁盘中
	wsl --shutdown 命令终止所有 WSL 实例
	wsl.exe --list --all (列出所有的linux系统(可能之前注册了没有取消注册))
	wsl.exe --unregister (上面所列出的名字)


### 家庭版windows10安装 Hyper-V脚本
	Hyper-V.cmd

### 禁止WSL加载Windows环境变量
<p>在wsl 的 ubuntu中编辑/etc/wsl.conf，输入：
[interop]
enable = false
appendWindowsPath = false
重启
</p>

### 禁止WSL提示音
编辑 /etc/inputrc 文件
取消 “set bell-style none”前面的#注释

### 禁止vim提示音
编辑 /etc/vim/vimrc 文件
最后添加 “set visualbell” 和 “set vb t_vb=”

### manual
编辑 ~/.profile 文件
最后添加 export LESS="$LESS -R -Q"


### 网址解析错误
<p>
1）临时修改（重启后无效）：
直接在/etc/resolv.conf里添加：
nameserver 8.8.8.8

2）永久修改
创建一个文件/etc/resolvconf/resolv.conf.d/tail，添加：
nameserver 8.8.8.8

3.重启网络
sudo /etc/init.d/networking restart
</p>

### git error
<p>server certificate verification failed. CAfile: none CRLfile: none
解决办法：
略過或關閉 SSL 憑證檢查
export GIT_SSL_NO_VERIFY=1
如果你信任該伺服器，可以直接設定環境變數，讓 git 略過憑證的驗證：
git config --global http.sslVerify false
</p>



#### Yocto build fail with exit code '134'
<p>构建目录下 local.conf 文件里添加
PSEUDO_IGNORE_PATHS_append = ",/run/"
</p>

#### gedit error
<p>
<li>D-Bus library appears to be incorrectly set up; failed to read machine uuid: UUID file '/etc/machine-id' should contain a hex string of length 32, not length 0, with no other text
sudo  dbus-uuidgen --ensure

<li>failed to commit changes to dconf: Failed to execute child process "dbus-launch" 
sudo apt install dbus-x11

<li>Set document metadata failed: Setting attribute metadata::gedit-position not supported
可以忽略
</p>


### 调整虚拟磁盘大小

	若要将最大 VHD 大小扩展到超过 256GB，请执行以下操作：
		使用 wsl --shutdown 命令终止所有 WSL 实例
		查找你的分发版安装包名称（“PackageFamilyName”）
		• 使用 PowerShell（其中，“distro”是分发版名称）输入以下命令：
		• Get-AppxPackage -Name "<distro>" | Select PackageFamilyName
		找到 WSL 2 安装使用的 VHD 文件 fullpath，这将是你的 pathToVHD：
		• %LOCALAPPDATA%\Packages<PackageFamilyName>\LocalState<disk>.vhdx
		通过完成以下命令调整 WSL 2 VHD 的大小：
		• 以管理员权限打开 Windows 命令提示，然后输入：
		• diskpart
		• Select vdisk file="<pathToVHD>"
		• expand vdisk maximum="<sizeInMegaBytes>"
		sizeInMegaBytes为更改后的大小，单位MB

	这下面很重要

		启动 WSL 分发版（例如 Ubuntu）。
		通过从 Linux 分发版命令行运行以下命令，让 WSL 知道它可以扩展其文件系统的大小：
		• sudo mount -t devtmpfs none /dev
		• mount | grep ext4
		• 复制此项的名称，该名称类似于：/dev/sdXX（X 表示任何其他字符）
		• sudo resize2fs /dev/sdXX
		• 使用前面复制的值。 可能还需要安装 resize2fs：apt install resize2fs


	作者：playAndroid
	链接：https://www.jianshu.com/p/2348dc7e9aef
	来源：简书
