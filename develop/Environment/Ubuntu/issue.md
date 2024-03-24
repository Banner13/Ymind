### 禁止键盘输入提示音
编辑 /etc/inputrc 文件
```bash
# 去除前面的#
#set bell-style none
set bell-style none
```

### 域名解析错误
临时修改(重启后无效): 直接在/etc/resolv.conf里添加：
```conf
nameserver 8.8.8.8
```

永久修改: 创建一个文件/etc/resolvconf/resolv.conf.d/tail，添加：
```conf
nameserver 8.8.8.8
```
然后进行[[develop/Environment/Ubuntu/issue#网络重启|网络重启]]。

### dpkg: error processing package stlink (--configure):
#### error
``` bash
$ sudo apt-get install -y linux-headers-generic
Reading package lists... Done
Building dependency tree
Reading state information... Done
linux-headers-generic is already the newest version (5.4.0.174.172).
0 upgraded, 0 newly installed, 0 to remove and 4 not upgraded.
1 not fully installed or removed.
After this operation, 0 B of additional disk space will be used.
Setting up stlink (1.8.0-1) ...
depmod: ERROR: could not open directory /lib/modules/5.10.16.3-microsoft-standard-WSL2: No such file or directory
depmod: FATAL: could not search modules: No such file or directory
dpkg: error processing package stlink (--configure):
 installed stlink package post-installation script subprocess returned error exit status 1
Errors were encountered while processing:
 stlink
E: Sub-process /usr/bin/dpkg returned an error code (1)
```

#### solve
``` bash
$ sudo rm /var/lib/dpkg/info/stlink*
$ sudo dpkg --configure -D 777 stlink
```