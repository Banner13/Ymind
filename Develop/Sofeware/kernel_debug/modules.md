[TOC]

<h2>kernel modules 调试</h2>

<h3
> kernel源码调试 </h3>

<h4
> 调试需要及环境 </h4>

<p><li
> kernel源码(5.10.72)
<li
> 编译器(交叉编译链)
<li
> 需要调试的module源码
<li
> 主机：Ubuntu20
<li
> 目标机器：imx8mp
</p>

<h4
> 原因 </h4>

<p
> 对于调试kernel的驱动来说，每次重新编译kernel是耗时耗力的事，所以我们将需要调试的功能作为模块加载调试，就会方便很多。</p>

<h4
> 具体步骤 </h4>

<p><b
> 配置编译环境 </b>

配置交叉编译环境。配置后，可通过环境变量查看是否成功，imx8mp ARCH为arm64,所使用的交叉编译链为aarch64-poky-linux-gcc(可能各有不同)。
查询结果如下图：</p>

```bash
huke@ThinkPad16:~/sourcecode/sys2-linux$ echo $ARCH
arm64
huke@ThinkPad16:~/sourcecode/sys2-linux$ echo $CC
aarch64-poky-linux-gcc -mcpu=cortex-a53 -march=armv8-a+crc+crypto -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/sys2-scanner/5.10-gatesgarth/sysroots/cortexa53-crypto-poky-linux
```

<p><b
> 以 hello,world驱动 为例：</b></p>

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbly, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

<p><b
> 编写相应的Makefile(注:Makefile中的Tab作为语法的一部分) </b></p>

```Makefile
# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
modules_name=hello

ifneq ($(KERNELRELEASE),)
	obj-m := $(modules_name).o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= ../../
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY := clean
clean:
	rm -rf .*cmd *.symvers *.mod* *.order *.o
```

执行后，生成一些列的文件，我们可以通过 make clean 删除不需要的文件。
最后得到了 hello.ko 文件。

<p><b
> 在开发板上进行测试 </b></p>

将ko文件传输至开发的 /tmp 目录下,并查看系统log，如下图。
```bash
root@sys-8mp: insmod /tmp/hello.ko
[524706.782172] Hello, world
root@sys-8mp: rmmod hello
[524749.367242] Goodbly, cruel world
```





