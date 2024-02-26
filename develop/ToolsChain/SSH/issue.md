
### ssh 方式提示 no matching host key type found
    etc > ssh 文件夹下找到 ssh_config 文件
    添加
    # 注意这里的 xxx.com 是没有 https:// 的
    # 如 https://github.com/， 填写 github.com 即可（最后的斜杆也不能要）。
    Host xxx.com
    HostkeyAlgorithms +ssh-rsa
    PubkeyAcceptedAlgorithms +ssh-rsa

### ssh主机重复
```bash
#  强制重新生成
$  ssh-keygen -f "/home/sword/.ssh/known_hosts" -R "192.168.1.100"
```