### 删除文件时，提示文件正在使用
```powershell
tasklist /m 文件路径
```

### depmod: ERROR
depmod: ERROR: could not open directory /lib/modules/5.10.16.3-microsoft-standard-WSL2: No such file or directory

#### solve
``` bash
sudo apt-get install -y linux-headers-generic
```
