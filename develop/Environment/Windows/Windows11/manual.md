### windows11恢复windows右键菜单栏格式
切换到旧版右键菜单：
```powershell
reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve
```

恢复回Win11右键菜单：
```powershell
reg delete "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}" /f
```

然后[[develop/Environment/Windows/manual#重启Windows资源管理器|重启Windows资源管理器]]。



