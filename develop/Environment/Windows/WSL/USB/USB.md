```bash
# Tip 适用于WSL2
```

### WSL2使用串口
[官方文档](https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb)
	WSL1可以直接映射，WSL2需要使用其他工具
[指导原文](https://blog.csdn.net/qq_28695769/article/details/125202748)
#### window配置
1.下载 [usbipd-win_2.3.0](https://github.com/dorssel/usbipd-win/releases)
#### wsl2配置
[链接](https://github.com/dorssel/usbipd-win/wiki/WSL-support)
```bash
sudo apt install linux-tools-virtual hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20
```
#### 使用方法
windows端
1. 通过以_管理员_模式打开 PowerShell 并输入以下命令，列出所有连接到 Windows 的 USB 设备。 列出设备后，选择并复制要附加到 WSL 的设备总线 ID。
``` PowerShell
usbipd list
```

2. 在附加 USB 设备之前，必须使用命令 `usbipd bind` 来共享设备，从而允许它附加到 WSL。 这需要管理员权限。 选择要在 WSL 中使用的设备总线 ID，然后运行以下命令。 运行命令后，请再次使用命令 `usbipd list` 验证设备是否已共享。
```Powershell
 usbipd bind --busid 4-4
```

3. 若要附加 USB 设备，请运行以下命令。 （不再需要使用提升的管理员提示。）确保 WSL 命令提示符处于打开状态，以使 WSL 2 轻型 VM 保持活动状态。 请注意，只要 USB 设备连接到 WSL，Windows 将无法使用它。 附加到 WSL 后，任何作为 WSL 2 运行的分发版本都可以使用 USB 设备。 使用 `usbipd list` 验证设备是否已附加。 在 WSL 提示符下，运行 `lsusb` 以验证 USB 设备是否已列出，并且可以使用 Linux 工具与之交互。
```Powershell
usbipd attach --wsl --busid <busid>
```

4. 打开 Ubuntu（或首选的 WSL 命令行），使用以下命令列出附加的 USB 设备：
```bash
lsusb
```

5. 在 WSL 中完成设备使用后，可物理断开 USB 设备，或者从 PowerShell 运行此命令：
```PowerShell
usbipd detach --busid <busid>
```

备注：
当设备断开之后如何重新连接，操作方式如下两种：
1、见以上2、
2、在Ubuntu下进行如下操作即可：
```bash
usbip list -r $HOSTNAME.local #用于查看已经usbip连接过的设备
sudo usbip attach -r $HOSTNAME.local -b 设备的busid号 #进行设备连接
```

#### Ref
[连接USB设备](https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb#attach-a-usb-device.)
