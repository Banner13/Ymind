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

### ssh主机重复
```bash
#  强制重新生成
$  ssh-keygen -f "/home/sword/.ssh/known_hosts" -R "192.168.1.100"
```