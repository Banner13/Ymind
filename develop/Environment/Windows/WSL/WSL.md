[TOC]


### 家庭版windows10安装 Hyper-V脚本
	Hyper-V.cmd

### manual
编辑 ~/.profile 文件
最后添加 export LESS="$LESS -R -Q"




### git error
<p>server certificate verification failed. CAfile: none CRLfile: none
解决办法：
略過或關閉 SSL 憑證檢查
export GIT_SSL_NO_VERIFY=1
如果你信任該伺服器，可以直接設定環境變數，讓 git 略過憑證的驗證：
git config --global http.sslVerify false
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

### WSL2使用串口
[官方文档](https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb)
	WSL1可以直接映射，WSL2需要使用其他工具
[指导原文](https://blog.csdn.net/qq_28695769/article/details/125202748)
#### window配置
1.下载 [usbipd-win_2.3.0](https://github.com/dorssel/usbipd-win/releases)
#### wsl2配置
[链接](https://github.com/dorssel/usbipd-win/wiki/WSL-support)
```bash
sudo apt install linux-tools-virtual hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20
```
#### 使用方法
windows端
```cmd
usbipd wsl list #列出所有的已经连接到windows的usb设备
usbipd wsl attach --busid 设备的busid号 #讲usb设备连接到WSL2下的Ubuntu

#usbipd wsl list的现象
#PS C:\Users\Admin> usbipd wsl list
#BUSID  VID:PID    DEVICE                                                        STATE
#1-4    13d3:5415  Integrated Camera                                             Not attached
#2-2    046d:c52f  USB 输入设备                                                  Not attached
#3-3    06cb:00bd  Synaptics UWP WBDI                                            Not attached
#3-4    8087:0029  英特尔(R) 无线 Bluetooth(R)                                   Not attached
#5-3    1a86:7523  USB-SERIAL CH340 (COM5)                                       Attached

#以下其他命令，看需要使用
usbipd wsl detach --busid 设备的busid号  #断开usb设备的连接和直接拔出一个效果
lsusb #在Ubuntu下使用，作用：列出当前连接的usb设备
usbipd wsl list #在Windows下使用，作用：和lusb一致
```

备注：
当设备断开之后如何重新连接，操作方式如下两种：
1、见以上2、
2、在Ubuntu下进行如下操作即可：
```bash
usbip list -r $HOSTNAME.local #用于查看已经usbip连接过的设备
sudo usbip attach -r $HOSTNAME.local -b 设备的busid号 #进行设备连接
```


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

