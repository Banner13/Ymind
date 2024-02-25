```bash
# ModuleNotFoundError: No module named '_lzma'
# 手动编译安装Python 可能回遇到该问题
# 原因:手动编译Python时确实该库
# 解决方案: 安装该库,重新编译安装Python
$ sudo apt-get install liblzma-dev
```

#### Ref
[[WSL1/Python3.9/install|Python3.9 install]]