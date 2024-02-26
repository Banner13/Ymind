[TOC]



### imx8mm 记录
pip版本过低，更新失败
e.

缺少依赖工具
e.
```bash
sudo apt-get install default-jdk libssl-dev libtinfo5 genext2fs mtd-utils scons gcc-arm-none-eabi gcc-arm-linux-gnueabi
```

ERROR at //device/soc/nxp/hardware/display/BUILD.gn:50:5: Unable to load "/home/huke/Harmony/utils/memory/libdmabufheap/BUILD.gn".
[OHOS INFO]     "//utils/memory/libdmabufheap:libdmabufheap",
e.找到 libdmabufheap/BUILD.gn的路径，修改 display/BUILD.gn 的内容。
