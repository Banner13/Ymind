### 添加 git-bash 到鼠标右键菜单栏

参考[[develop/Environment/Windows/manual#添加应用到右键快捷栏|添加应用到右键快捷栏]]
1. 通过Windows+R快捷键可以打开“运行窗口”，在“窗口”中输入“regedit”，点击“确定”打开注册表
2. 在搜索栏“计算机”后输入"\HKEY_CLASSES_ROOT\Directory\Background"回车确定或者点击计算机图标逐级查找
3. 在“Background”目录下如果没有“shell”,则右键—新建项“shell”
4. 在“shell”目录下右键—新建项“open in Git”,其值为“Git Bash Here",此为右键菜单显示名称
5. 在“open in Git”目录下右键—新建—字符串值“Icon”,双击编辑，其值为“E:\Git\mingw64\share\git\git-for-windows.ico”。需要按照实际安装路径修改，此为菜单加图标
6. 在“open in git”目录下右键—新建—项“command”,其值为 "E:\Git\git-bash.exe"，需要按照实际路径修改
7. 右键菜单就可以看到“Git Bash Here”了