[TOC]

## 适配lan820a网卡
	NXP官方版使用的PHY-IC是KSZ8081RNB，而100ask使用的是lan820a，并且在硬件连接上也有差异，需要进行移植。

### 1.  确认硬件上的差异
相关原理图资料
[[MCIMX6ULL-EVK(NXP)]]
[[100ask_imx6ull_mini]]

<ol>根据硬件得到以下几点信息
<li> phy芯片不同，所以使用不同的驱动-->修改defconfig
<li> 所使用的pin脚有差异-->修改设备树文件
<li> phy芯片复位要求以及地址-->修改驱动文件
</ol>


### 2. 软件上驱动修改
#### 2.1 修改defconfig文件
```xxx_defconfig
删除 CONFIG_PHY_MICREL=y
删除 CONFIG_PHY_MICREL_KSZ8XXX=y
新增 CONFIG_PHY_SMSC=y
```
原因：查看uboot/driver/net/phy/phy.c 中的phy_init()

#### 2.2 修改设备树文件
##### 2.2.1 网络适配器
默认使用fec2，mini只使用了fec1，所以注释了fec2的内容。
```xxx.dtsi
&fec1 {
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_enet1>;
    phy-mode = "rmii";
    phy-handle = <&ethphy0>;
    phy-reset-gpios = <&gpio5 9 GPIO_ACTIVE_LOW>;
    phy-reset-duration = <26>;
    status = "okay";

    mdio {
        #address-cells = <1>;
        #size-cells = <0>;

        ethphy0: ethernet-phy@0 {
            reg = <0>;
            #micrel,led-mode = <1>;
            clocks = <&clks IMX6UL_CLK_ENET_REF>;
            clock-names = "rmii-ref";
        };
    };
};

/*
&fec2 {
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_enet2>;
    phy-mode = "rmii";
    phy-handle = <&ethphy0>;
    status = "disabled";
  
    mdio {
        #address-cells = <1>;
        #size-cells = <0>;
  
        ethphy0: ethernet-phy@0 {
            reg = <0>;
            #micrel,led-mode = <1>;
            clocks = <&clks IMX6UL_CLK_ENET_REF>;
            clock-names = "rmii-ref";
        };

        ethphy1: ethernet-phy@1 {
            reg = <1>;
            micrel,led-mode = <1>;
            clocks = <&clks IMX6UL_CLK_ENET2_REF>;
            clock-names = "rmii-ref";
        };
    };
};
*/
```
##### 2.2.2 新增初始化MDC和MDIO引脚
```xxx.dtsi
    pinctrl_enet1: enet1grp {
        fsl,pins = <
            MX6UL_PAD_GPIO1_IO07__ENET1_MDC     0x1b0b0
            MX6UL_PAD_GPIO1_IO06__ENET1_MDIO    0x1b0b0
            MX6UL_PAD_ENET1_RX_EN__ENET1_RX_EN  0x1b0b0
            MX6UL_PAD_ENET1_RX_ER__ENET1_RX_ER  0x1b0b0
            MX6UL_PAD_ENET1_RX_DATA0__ENET1_RDATA00 0x1b0b0
            MX6UL_PAD_ENET1_RX_DATA1__ENET1_RDATA01 0x1b0b0
            MX6UL_PAD_ENET1_TX_EN__ENET1_TX_EN  0x1b0b0
            MX6UL_PAD_ENET1_TX_DATA0__ENET1_TDATA00 0x1b0b0
            MX6UL_PAD_ENET1_TX_DATA1__ENET1_TDATA01 0x1b0b0
            MX6UL_PAD_ENET1_TX_CLK__ENET1_REF_CLK1  0x4001b031
        >;
    };
```

#### 2.3 修改驱动文件
##### 2.3.1 uboot
uboot/driver/net/phy/phy.c:genphy_config_aneg()函数中新增
```
phy_reset(phydev);
```

##### 2.3.2 linux_kernel
linux/drivers/net/phy/phy_device.c:__genphy_config_aneg()函数中新增
```
phy_soft_reset(phydev);
```

### 3. 进行验证
#### 3.1 重新[[编译Uboot]]
#### 3.2 进行烧录
[[进入烧录模式]]
#### 3.3 验证
[[网络验证]]

### 参考资料
1. 【适合有一定基础参考】嵌入式Linux应用开发完全手册_韦东山全系列视频文档-IMX6ULL开发板(从零移植篇-预览版)-V0.1.pdf (忘记具体在哪个位置了，应该是imx6ull_pro的相关资料中)
2. [详细讲解u-boot之网络移植与调试(强烈推荐)](https://blog.csdn.net/Wang_XB_3434/article/details/130817581?spm=1001.2014.3001.5502)



