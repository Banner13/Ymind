### 禁止WSL加载Windows环境变量
在 /etc/wsl.conf 中添加：
```conf
[interop]
enable = false
appendWindowsPath = false
```
[[develop/Environment/Windows/WSL/manual#WSL重启|WSL重启]]

### WSL使用systemd 和 snap包管理
在 /etc/wsl.conf 中添加：
```conf
[boot]
ststemd = true
```
[[develop/Environment/Windows/WSL/manual#WSL重启|WSL重启]]

### WslRegisterDistribution failed with error: 0x800701bc
需要更新内核
[内核更新文件下载链接](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)









