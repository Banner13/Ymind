（windows环境）
msys2

#####配置到右键快捷键
	在 运行 中输入 regedit 打开注册表编辑器^(1)^
	在路径
	“计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\”
	下新建项目  msys2 默认值   添加该项后会显示在右键菜单栏
	还可添加 值 Icon 图标显示
	还需添加想 command 为软件路径


#####msys2 跳转到打开的路径，如不设置  每次都会跳转到 msys2的家目录下
	D:\Tools\MSYS2\usr\bin\mintty.exe /bin/bash -lc 'cd "$(cygpath "%V")"; export CHERE_INVOKING=1; exec bash --login -i'
	
	new : msys2_shell.cmd -msys2 -defterm -here  -no-start



#####gitk
	pacman -S mingw-w64-x86_64-tk
	add /mingw64/bin/wish.exe to env
	run gitk

#####msys2 使用 windows 环境变量PATH
	新建变量 MSYS2_PATH_TYPE    值为 inherit

#####注解：
	1. windows下的软硬件配置信息，相当于管理整个计算机的数据库