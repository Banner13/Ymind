### Ubuntu更新cmake
```bash
# upgrade cmake
# 更新cmake
$  sudo apt remove cmake -y
$  pip install cmake --upgrade
```

### cmake使用toolchain.cmake
	3.24版本后可通过环境变量CMAKE_TOOLCHAIN_FILE=xxx 指定交叉编译环境文件路径
