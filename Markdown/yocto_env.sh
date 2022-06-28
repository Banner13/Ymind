#init ypcto env
#.sh
sudo cp /etc/cp /etc/apt/sources.list /etc/apt/sources.list.bak \
cp ~/.bashrc ~/.bashrc.bak 

sudo echo "# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释 " > /etc/apt/sources.list 
sudo echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "  " >> /etc/apt/sources.list 
sudo echo "# 预发布软件源，不建议启用 " >> /etc/apt/sources.list 
sudo echo "# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse " >> /etc/apt/sources.list 
sudo echo "# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse hello" >> /etc/apt/sources.list 