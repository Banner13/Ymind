
####STM32F103开发环境(SDK)^(1)^搭建
开发工具（VS Code / SI^(2)^ + STM32CubeMx + ARM编译器^(3)^ + Openocd + MingG-w64）
___
工具用途：
 - STM32CubeMx　　　STM官方工具，高效生成基本的源代码
 - VS Code / SI　　　　代码编辑器
 - ARM编译器　　　　将源代码编译成可执行文件
 - Openocd  　　　　　调试工具
 - MingG-w64  　　　　Windows下gcc编译链，(SDK需要使用该项目下的mingw32-make)
___
获取工具包：
以下全部工具安装包　　　 [百度网盘链接：　提取码SDKs](https://pan.baidu.com/s/13Xn5jRx2dA_AOu9-vTngMg "Title")
注：百度网盘中可能使用的不是最新版本，需要最新版本请移步官网下载

 - STM32CubeMx　　　 [官网下载链接](https://www.st.com/zh/development-tools/stm32cubemx.html#get-software "Title")
 - VS Code　　　　　　[官网下载链接](https://code.visualstudio.com/Download# "Title")
 -  SI  　　　　　　　　 [官网下载链接](https://www.sourceinsight.com/download/ "Title")
 -  ARM编译器  　　　　 [官网下载链接](https://launchpad.net/gcc-arm-embedded/+download "Title")
 -  Openocd  　　　　 　 [官网下载链接](https://gnutoolchains.com/arm-eabi/openocd/ "Title")
 -  MingG-w64　　　　　[官网下载链接](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/ "Title")

注：以上下载后有的是安装包，有的是可执行文件的压缩包
___
安装工具：
安装目录以　D:\Toolchain\STM32_SDK\ 为例，可根据自己需要更改

	exe文件请按照提示安装，安装目录 D:\Toolchain\STM32_SDK\xxx
	注：xxx 可以自定义，不建议安装路径中包含中文、空格等特殊字符，尽量只使用字母、下划线、数字

	例如：
	SI 安装目录 D:\Toolchain\STM32_SDK\SI
	STM32CubeMx 安装目录 D:\Toolchain\STM32_SDK\STM32CubeMx
　　
  
	压缩文件解压到　D:\Toolchain\STM32_SDK\　目录下即可
	例如：
	Openocd  D:\Toolchain\STM32_SDK\openocd-20211118
___
设置环境变量^(4)^：

	需要配置环境变量的软件：
		MingG-w64　　 验证　mingw32-make -v
		Openocd　　 　验证　openocd -v
		ARM编译器	 验证　arm-none-eabi-gcc -v

	步骤：
		右键点击我的电脑或此电脑选择　属性
		点击　高级系统设置
		点击　高级
		点击　环境变量
		选中 Path
		点击 编辑
		点击 新建
		点击 浏览
		找到可执行文件所在的目录 例如 gcc 在 D:\Toolchain\STM32_SDK\mingw64\bin目录下
		然后一直点确定完成设置
		
	环境变量验证：
		windows图标 + R 或者搜索 运行 来打开运行
		运行窗口输入 cmd 打开命令行窗口
		输入 gcc -v 若无错误 最后一行会显示 gcc 版本
		例如 gcc version 8.1.0 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project)

软件配置：
	VS Code 使用到的插件 Cortex-Debug 、 Cortex-Debug: Device Support Pack - STM32F1 、 Arm Assembly

 



注释：
	1：Software development kit -------- 软件开发套件
	2：Source Insight -------- 简单、高效的代码阅读、编辑器 (不是免费的！！！)
	3：arm-none-eabi-gcc等 -------- ARM GCC 编译链
	4：环境变量 -------- 告诉计算机软件存放的位置
	不同于在桌面使用应用，一般命令行使用应用需要指明应用所在的路径，
	例如 gcc main.c -o main.exe 通常 gcc.exe 和 main.c 不在同一文件夹，
	此时需要 D:\Toolchain\STM32_SDK\mingw64\bin\gcc.exe main.c -o main.exe 才能执行，
	不然会出现错误警告： 'gcc' 不是内部或外部命令，也不是可运行的程序或批处理文件。

爬坑：
	VScode openocd 下载bin文件到芯片
    "-f stlink ..."
    需要配置为
    "-f",
    "stlink.."
    其次，需要采用 openocd share 绝对路径下的文件
    
    例如
    {
        "label": "download",
        "type": "shell",
        "command": "openocd",
        "args": [
            "-f",
            "D:\\Jie_ProgramFiles\\Tools\\Msys2\\mingw64\\share\\openocd\\scripts\\interface\\stlink.cfg",
            "-f",
            "D:\\Jie_ProgramFiles\\Tools\\Msys2\\mingw64\\share\\openocd\\scripts\\target\\stm32f1x.cfg",
            "-c init",
            "-c halt",
            "-c flash write_image erase ./build/${workspaceFolderBasename}.bin 0x08000000",
            "-c reset",
            "-c shutdown"
        ]
    }

	lunch.json

        {
            "name": "Cortex Debug",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/${workspaceFolderBasename}.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "openocd",
            "preLaunchTask": "build",
            "device": "STM32F103C6",
            "configFiles": [
                "${workspaceFolder}\\openocd.cfg"
            ],
            "svdPath": "D:\\Users\\Administrator\\Downloads\\Firefox_Download\\cmsis-svd-master\\cmsis-svd-master\\data\\STMicro",
            "svdFile": "STM32F103xx.svd"
        },