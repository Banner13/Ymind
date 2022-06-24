

    1. https://sourceforge.net/projects/mingw-w64/files/mingw-w64/ // 获取mingw64文件并解压到存放位置,无需安装
    2. 设置环境变量  右键 我的电脑/此电脑->属性->高级系统设置->高级->环境变量->用户变量->Path->编辑->新建->浏览->选择存放目录下的/bin->然后一路点确定
    3. 验证 windows窗口图标+R 打开运行   输入 cmd  跳出窗口后输入 gcc -v 无错误即可 
    // gcc -v 消息末尾   gcc version 8.1.0 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project)
    4. make：  可将上述 /bin目录下的 mingw32-make 复制并重命名为 make 使用


###添加 git-bash 到鼠标右键菜单栏
	1. 通过Windows+R快捷键可以打开“运行窗口”，在“窗口”中输入“regedit”，点击“确定”打开注册表
	2. 在搜索栏“计算机”后输入"\HKEY_CLASSES_ROOT\Directory\Background"回车确定或者点击计算机图标逐级查找
	3. 在“Background”目录下如果没有“shell”,则右键—新建项“shell”
	4. 在“shell”目录下右键—新建项“open in Git”,其值为“Git Bash Here",此为右键菜单显示名称
	5. 在“open in Git”目录下右键—新建—字符串值“Icon”,双击编辑，其值为“E:\Git\mingw64\share\git\git-for-windows.ico”。需要按照实际安装路径修改，此为菜单加图标
	6. 在“open in git”目录下右键—新建—项“command”,其值为 "E:\Git\git-bash.exe"，需要按照实际路径修改
	7. 右键菜单就可以看到“Git Bash Here”了


###windows11恢复windows右键菜单栏格式
	切换到旧版右键菜单：
	reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve
	
	恢复回Win11右键菜单：
	reg delete "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
	
	重启Windows资源管理器生效：
	taskkill /f /im explorer.exe
	start explorer.exe
	
