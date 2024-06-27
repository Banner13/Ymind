### [[develop/Environment/Windows/Msys2/tip|Msys2]]安装
[[develop/ToolsChain/Pacman/tip#下载应用命令|Pacman下载]] mingw64/mingw-w64-x86_64-arm-none-eabi-gcc

### ARM官网下载
[官网下载链接(Win10)](https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-win32.exe?rev=29bb46cfa0434fbda93abb33c1d480e6&hash=B2C5AAE07841929A0D0BF460896D6E52)

### Ubuntu
```shell
sudo apt install build-essential gcc-arm-none-eabi gdb-multiarch
```

```bash
sudo apt install gdb-arm-none-eabi
```

### 安装gcc-4.4
软件下载源:
[[develop/Environment/Ubuntu/manual#更新Ubuntu内软件下载源|Ubuntu]] 添加"deb http://dk.archive.ubuntu.com/ubuntu/ trusty main universe"

```
安装gcc/g++-4.4
```bash
sudo apt-get install -y gcc-4.4 g++-4.4 g++-4.4-multilib
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 4
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 7
sudo update-alternatives --config gcc
# 选择gcc-4.4对应的数字
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.4 4
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 7
sudo update-alternatives --config g++
# 选择g++-4.4对应的数字

# 查看版本
gcc -v
g++ -v
```
