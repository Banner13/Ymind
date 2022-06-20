

   yocto构建：
   所需安装包
    #sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \ 
    build-essential  chrpath socat libsdl1.2-dev libsdl1.2-dev xterm sed cvs subversion \ 
    coreutils texi2html  docbook-utils python-pysqlite2 help2man make gcc g++ desktop-file-utils \
    libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc \
    u-boot-tools python3-pip
    
    yocto所需安装包
    $ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
    xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev \
    pylint3 xterm
    
    
repo下载
    #mkdir ~/bin
    #cd bin
    #curl https://mirrors.tuna.tsinghua.edu.cn/git/git-repo -o repo
    #chmod +x repo
下载源更新
	# $sudo gedit ~/.bashrc
    
    ##repo
    export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo/'
    source ~/.bashrc
    
初始化仓库
    #repo init -u https://source.codeaurora.cn/external/imx/imx-manifest -b imx-linux-zeus -m imx-5.4.47-2.2.0.xml
    
    repo sync -jx
    
代码书写原则：
    #TDD 是测试驱动开发（Test-Driven Development），它同样也是敏捷开发的一种方法论。
    TDD 是再开发代码之前，先编写单元测试用例，用测试的代码确定要编写什么样的代码。
    它的整个思路就是通过测试来驱动整个软件开发的进度，当然这对测试人员来说是一个更高的要求和标准。

    TDD 三大原则：
        You are not allowed to write any production code unless it is to make a failing unit test pass.
        You are not allowed to write any more of a unit test than is sufficient to fail; and compilation failures are failures.
        You are not allowed to write any more production code than is sufficient to pass the one failing unit test.

    翻译：
        除非是为了测试失败的单元测试通过，否则不允许编写任何生产代码
        在一个单元测试中，只允许编写刚好能够导致失败的内容（编译错误也算失败）
        只允许编写刚好能够使一个失败的单元测试通过的产品代码