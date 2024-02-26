### Yocto build fail with exit code '134'
在[[WSL]]环境下构建可能会出现该问题
解决方法：构建目录下 local.conf 文件里添加
```conf
PSEUDO_IGNORE_PATHS_append = ",/run/"
```
