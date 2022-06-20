    ***
    *** Can't find default configuration "arch/arm64/configs/imx_v8_defconfig"!
    ***
    scripts/kconfig/Makefile:94: recipe for target 'imx_v8_defconfig' failed
    make[1]: *** [imx_v8_defconfig] Error 1
    Makefile:616: recipe for target 'imx_v8_defconfig' failed
    make: *** [imx_v8_defconfig] Error 2
    banner@virtual-machine:~/share/OS_Set/linux-5.15.5$ cd ..
    banner@virtual-machine:~/share/OS_Set$ cd linux-imx/
    banner@virtual-machine:~/share/OS_Set/linux-imx$ cd ..
    banner@virtual-machine:~/share/OS_Set$ cd linux-imx/
    banner@virtual-machine:~/share/OS_Set/linux-imx$ make distclean
    banner@virtual-machine:~/share/OS_Set/linux-imx$ make imx_v8_defconfig



yaml.h: No such file or directory
the root case is the ubuntu 20.04 build server needs to install yaml by cmd : 
imx8編譯基於 ubuntu20  所以缺少包

    sudo apt-get install libyaml-dev libpython2.7-dev