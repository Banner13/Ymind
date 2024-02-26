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

### 提供ssh服务
```bash
#  安装openssh服务
$  sudo apt-get install openssh-server
```
ssh免密登录, 将本地生成的 ~/.ssh/id_rsa.pub 复制到 服务器端的 ~/.ssh/authorized_keys


