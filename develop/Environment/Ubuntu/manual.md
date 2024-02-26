### 网络重启
```bash
# method1
$ sudo /etc/init.d/networking restart

# method2
$ sudo nmcli networking off
$ sudo nmcli networking on

# method3
$ sudo systemctl start NetworkManager
$ sudo systemctl stop NetworkManager
$ sudo systemctl restart NetworkManager
```

### 软件安装
```bash
# deb包 安装
$ sudo dpkg -i xxx.deb

# 查看以安装软件
$ dpkg -l | grep "xxx"
```


