[TOC]


### Uboot查看分区内容命令
	mmc 查看设备
    fatls 查看分区内容(FAT格式)
    ext4ls 查看分区内容(ext4格式)

### Uboot替换原有文件以及保存新文件
	1.先将文件通过NFS或者TFTP传输到内存中。
	2.通过save命令保存到硬盘中。

```
=> setenv ipaddr 192.168.1.100
=> setenv gatewayip 192.168.1.255
=> setenv netmask 255.255.255.0
=> setenv serverip 192.168.1.200
=> setenv ethaddr 00:00:00:00:00:00
```