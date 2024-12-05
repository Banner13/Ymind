


### 分析repo init
	repo init -u https://source.codeaurora.org/external/imx/imx-manifest -b imx-linux-zeus -m imx-5.4.47-2.2.0.xml
	在-b imx-linux-zeus的 目录下仅仅存放了许多xxx.xml文件，内容是源码存放的地址、版本信息
	repo sync 时，会去读取 imx-5.4.47-2.2.0.xml 的内容，然后获取源码

### 声明修改repo更新源
	export REPO_URL='https://mirrors.tuna.tsinghua.edu.cn/git/git-repo'