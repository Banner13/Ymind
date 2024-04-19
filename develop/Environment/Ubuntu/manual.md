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

# 更新
$  sudo apt-get update
```
[清华开源链接](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)
