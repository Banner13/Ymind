
### VMware Tools 不生效问题
	// sudo apt-get autoremove open-vm-tools
	// sudo apt-get install open-vm-tools

```bash
$ sudo apt-get install open-vm-tools-desktop #单步生效
```

	重启

### 千兆网卡
修改 xxx.vmx 文件
ethernet0.virtualDev= "e1000"