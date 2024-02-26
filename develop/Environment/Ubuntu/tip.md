### 2.常用软件安装

    2.1 sudo apt-get install samba net-tools gitk graphviz openssh-server -y

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

