# 全新Ubuntu配置流程
## 选择清华源Ubuntu20镜像，最简安装。 //（https://mirrors.tuna.tsinghua.edu.cn/#） Desktop

***

### 1.更新Ubuntu内软件下载源为清华源

    1.1 sudo cp /etc/apt/sources.list /etc/apt/sources.list.default            // 源文件备份
    1.2 sudo gedit /etc/apt/sources.list  // 修改描述文件(https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)
    1.3 sudo apt-get update          // 更新下载源



    # https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/          20.04 LTS 
    # 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
    deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse
    deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse
    deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse
    deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse
    
    # 预发布软件源，不建议启用
    # deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse
    # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse

***

### 2.常用软件安装

    2.1 sudo apt-get install samba net-tools gitk graphviz openssh-server -y
    2.2 配置samba
    2.2.1 sudo smbpasswd -a 'username'  // 添加samba用户(用户需要是ubuntu已存在的用户，密码可以为空)
    2.3 选择需要共享的文件，右键开启共享
    2.4 windows下添加网络位置，验证使用samba用户信息即可

***

### 3.环境变量声明
    vi ~/.bashrc
    export PATH=xxx/xxx/xxx:$PATH
    alias ll='ls -l -h'
___
### 代理设置

	参考 https://zhuanlan.zhihu.com/p/102316528
		sudo apt-get install privoxy
		vim /etc/privoxy/config
		在最前面添加:
			listen-address 0.0.0.0:8118
			forward-socks5 / localhost:1080 .
		sudo /usr/sbin/privoxy /etc/privoxy/config
	
	function proxy_off(){
			unset http_proxy
			unset https_proxy
			unset ftp_proxy
			unset rsync_proxy
			unset HTTP_PROXY
			unset HTTPS_PROXY
			unset FTP_PROXY
			unset RSYNC_PROXY
			unset all_proxy
			unset ALL_PROXY
			git config --global http.proxy ""
			git config --global https.proxy ""
			echo -e "已关闭代理"
			curl cip.cc
			echo -e "已关闭代理"
	}

	function proxy_on() {
			export no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
			export http_proxy="http://127.0.0.1:1087" #注意，根据自己的配置设置有可能会是1080或1086
			export https_proxy=$http_proxy
			export ftp_proxy=$http_proxy
			export rsync_proxy=$http_proxy
			export HTTP_PROXY=$http_proxy
			export HTTPS_PROXY=$http_proxy
			export FTP_PROXY=$http_proxy
			export RSYNC_PROXY=$http_proxy
			echo -e "已开启代理"
	}
    new
    export https_proxy=$http_proxy \
    > export ftp_proxy=$http_proxy \
    > export rsync_proxy=$http_proxy \
    > export HTTP_PROXY=$http_proxy \
    > export HTTPS_PROXY=$http_proxy \
    > export FTP_PROXY=$http_proxy \
    > export RSYNC_PROXY=$http_proxy
___
### 使用问题
	修改目录下所有文件权限
	chmod -R 777 xxx/
___
#### 虚拟机使用
###### VMware Tools 不生效问题
	// sudo apt-get autoremove open-vm-tools
	// sudo apt-get install open-vm-tools
	sudo apt-get install open-vm-tools-desktop 单步生效
	重启

###### 千兆网卡
	ethernet0.virtualDev= "e1000"

###### 网络重启
```bash
sudo nmcli networking off
sudo nmcli networking on

sudo systemctl start NetworkManager
sudo systemctl stop NetworkManager
sudo systemctl restart NetworkManager
```
##### deb包 安装
	sudo dpkg -i xxx.deb

##### 查看以安装软件
	dpkg -l | grep '^ii'

##### 提供ssh服务
	sudo apt-get install openssh-server
	ssh免密登录, 将本地生成的 ~/.ssh/id_rsa.pub 复制到 服务器端的 ~/.ssh/authorized_keys

##### ssh生成已知主机
```bash
ssh-keygen -f "/home/sword/.ssh/known_hosts" -R "192.168.1.100"
```