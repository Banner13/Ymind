###yocto构建：

	yocto 所需安装包(两个都进行安装  有的重复，但没关系)
    $ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential  chrpath socat  xterm sed cvs subversion \
     coreutils texi2html  docbook-utils  help2man make gcc g++ desktop-file-utils \
     mercurial autoconf automake groff curl lzop asciidoc \
     u-boot-tools  samba gitk cpio xz-utils debianutils iputils-ping   libegl1-mesa libsdl1.2-dev libgl1-mesa-dev libglu1-mesa-dev zstd \
     python python3  python3-pexpect  python3-pip python3-git python3-jinja2 pylint3  python-pysqlite2 \
     -y

	libncurses-dev
	libssl-dev

###下载repo
    #mkdir ~/bin
    #cd bin
    #curl https://mirrors.tuna.tsinghua.edu.cn/git/git-repo -o repo
    #chmod +x repo
###切换repo下载源
	# $sudo gedit ~/.bashrc

    ##repo
    export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/'
    source ~/.bashrc

###初始化仓库
    #repo init -u https://source.codeaurora.cn/external/imx/imx-manifest -b imx-linux-zeus -m imx-5.4.47-2.2.0.xml
    repo sync -jx
___
###yocto custom
######Image 　　就是由recipes烘烤完成的packeages
######recipe　　是一些构建packages的指令集
			从哪获取源代码以及加载哪些patch
			依赖关系（库和其他recipe）
			配置/编译选项
######layer  是代表core的recipes的逻辑集合、一个BSP或者一个应用栈

<<<<<<< HEAD:Markdown/Ubuntu/yocto.md

######层级
#######The Yocto Project and Poky
	User configuration
	Metadata (.bb + patches)
	Machine (BSP) configuration
	Policy configuration

#######Layers
	Develper-Specific Layer
	Commercial Layer (from OSV)
	UI-Specific Layer
	Hardware-Specific BSP
	Yocto-Specific Layer Metadata (meta-yocto)
	OpenEmbedded Core Metadata (oe-core)
___

###使用中遇到的问题：
	问题
		Can't find default configuration "arch/arm64/configs/imx_v8_defconfig"!
		scripts/kconfig/Makefile:94: recipe for target 'imx_v8_defconfig' failed
		make[1]: *** [imx_v8_defconfig] Error 1
		Makefile:616: recipe for target 'imx_v8_defconfig' failed
		make: *** [imx_v8_defconfig] Error 2
		banner@virtual-machine:~/share/OS_Set/linux-5.15.5$ cd ..
		banner@virtual-machine:~/share/OS_Set$ cd linux-imx/
		banner@virtual-machine:~/share/OS_Set/linux-imx$ cd ..
		banner@virtual-machine:~/share/OS_Set$ cd linux-imx/
		banner@virtual-machine:~/share/OS_Set/linux-imx$ make distclean
		banner@virtual-machine:~/share/OS_Set/linux-imx$ make imx_v8_defconfig
		// yaml.h: No such file or directory
	原因
		imx8编译基于 ubuntu20  所以缺少包
		the root case is the ubuntu 20.04 build server needs to install yaml by cmd :
	解决
    	sudo apt-get install libyaml-dev libpython2.7-dev
___
