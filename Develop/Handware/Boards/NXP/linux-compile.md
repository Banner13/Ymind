[TOC]

#### 源码编译
	1. 申明目标架构和编译链环境

```bash
export ARCH=arm64
export CROSS_COMPILE=arm-linux-gnueabihf-
export PATH=编译链路径:$PATH
```

	2. kernel配置
```bash
make xxx.defconfig
```

	3. 编译设备树
```bash
make dtbs
```

	4. 编译Image
```bash
LDFLAG="" CC="$CC"
make -j<N>
```
