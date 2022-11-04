#####windows 设置 mingw64环境
    1. https://sourceforge.net/projects/mingw-w64/files/mingw-w64/ // 获取mingw64文件并解压到存放位置,无需安装
    2. 设置环境变量  右键 我的电脑/此电脑->属性->高级系统设置->高级->环境变量->用户变量->Path->编辑->新建->浏览->选择存放目录下的/bin->然后一路点确定
    3. 验证 windows窗口图标+R 打开运行   输入 cmd  跳出窗口后输入 gcc -v 无错误即可 
    // gcc -v 消息末尾   gcc version 8.1.0 (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project)
    4. make：  可将上述 /bin目录下的 mingw32-make 复制并重命名为 make 使用
