### 网络重启
```bash
# method1
$  sudo /etc/init.d/networking restart

# method2
$  sudo nmcli networking off
$  sudo nmcli networking on

# method3
$  sudo systemctl start NetworkManager
$  sudo systemctl stop NetworkManager
$  sudo systemctl restart NetworkManager
```

### 软件安装
```bash
# deb包 安装
$ sudo dpkg -i xxx.deb

# 查看以安装软件
$ dpkg -l | grep "xxx"
```

### 新增架构支持
```bash
# deb包 安装
$ sudo dpkg --add-architecture i386
$ sudo apt-get update

# 使用方式
$ apt-get install libc6:i386
```

### 更新Ubuntu内软件下载源
```bash
# 源文件备份
$  sudo cp /etc/apt/sources.list /etc/apt/sources.list.default

# 替换原有list文件
$  sudo cp new_sources.list /etc/apt/sources.list

# 新增软件下载源
$  sudo echo "deb http://dk.archive.ubuntu.com/ubuntu/ trusty main universe" >> /etc/apt/source.list

# 更新
$  sudo apt-get update
```
[清华开源链接](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)

### Ubuntu切换服务器IP
**1. 手动获取IP地址**
	通过多台服务器获取到的DNS解析情况来选择最优解，可以使用[Dns查询 - 站长工具 (chinaz.com)](https://link.juejin.cn/?target=https%3A%2F%2Ftool.chinaz.com%2Fdns%2F "https://tool.chinaz.com/dns/")查找TTL值最小的响应IP

**2. 编辑 `/etc/hosts` 文件**

	- 使用文本编辑器打开 `/etc/hosts` 文件，您需要 root 权限：
	- 在文件末尾添加以下内容，将 `20.205.243.166` 替换为您获取的 GitHub 的可用 IP 地址：
		20.205.243.166 github.com 
		20.205.243.166 assets-cdn.github.com 
		20.205.243.166 github.global.ssl.fastly.net

**3. 刷新 DNS 缓存**
- 修改 `/etc/hosts` 文件后，刷新 DNS 缓存。Linux 通常不需要手动刷新 DNS 缓存，但如果您的系统有 DNS 缓存服务，例如 `systemd-resolved`，可以通过以下命令刷新：
	sudo systemctl restart systemd-resolved