### 重启Windows资源管理器
```powershell
> taskkill /f /im explorer.exe
> start explorer.exe
```



### 添加应用到右键快捷栏
1.  在 "运行"(Ctrl+R) 中输入 regedit 打开注册表编辑器
	在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\" 下，
	右击 "shell" 新建项, 命名 "应用名" ，添加该项后会显示在右键快捷菜单栏，但点击后无反应。

2.  在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\应用名\" 下，
	 右击 "应用名" 新建项,命名 "command" ，选中 "command" 后，修改默认值为应用的路径。
	 例如 "D:/msys2/msys2.exe"，此时右键便可打开 msys2 。

3.  在路径 "计算机\HKEY_CLASSES_ROOT\Directory\Background\shell\msys2\" 下，
	 右击 "msys2" 新建字符串值,命名 "Icon" ，修改 "Icon" 默认值为 msys2 的路径下的 "msys2.ico"。
	 为 msys2 添加图标。