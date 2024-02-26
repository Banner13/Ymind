### 配置samba
```bash
#  添加samba用户(用户需要是ubuntu已存在的用户，密码可以为空)
$  sudo smbpasswd -a 'username'
```

选择需要共享的文件，右键开启共享(带GUI的Ubuntu环境)
windows下添加网络位置，验证使用samba用户信息即可


