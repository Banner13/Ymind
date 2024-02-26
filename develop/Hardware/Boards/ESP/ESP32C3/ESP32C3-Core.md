[TOC]

### 开发环境以及硬件
硬件:
合宙ESP32C3-Core(9.9包邮)
![](develop/Hardware/Boards/ESP/ESP32C3/ESP32C3-Core.png)

软件:
Arduino IDE(1.8.19)  2.0本人没有适配成功VScode
VScode


### 环境配置
#### Arduino IDE配置(2.0)
(需要连翻墙),不翻墙老是下载失败，或者去论坛找一下下载包，放在相应位置。
文件->首选项->其他开发板管理器地址->添加
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json

开发版选择 ESP32C3 Dev Module
选择串口()   若设备插入未弹出新的串口，请检查USB线或串口驱动[笔者使用 CH343](https://www.wch.cn/downloads/CH343SER_EXE.html)
工具->FlashMode->DIO


#### VScode配置(Arduino IDE 1.8.19)
加载Arduino官方插件
修改扩展配置
添加ArduinoPath和ArduinoCommandPath
```json
{
	...
    "arduino.path": "D:/MyProgram/Tools/Arduino",	#arduino安装路径
    "arduino.commandPath": "arduino_debug.exe",
    "C_Cpp.intelliSenseEngine": "Tag Parser"
}
```
点击右下角Board Config对板子属性进行配置
![](develop/Hardware/Boards/ESP/ESP32C3/VScode.PNG)
同上，Flash Mode选择 DIO。其余可以使用默认配置。

### 笔者DEMO
#### LED灯闪烁
代码如下
```c
// the setup function runs once when you press reset or power the board
#define led 0
void setup() {
  // initialize  LED
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, HIGH);   // Turn the RGB LED white
  delay(2000);
  digitalWrite(led, LOW);    // Turn the RGB LED off
  delay(2000);
  printf("hello world\r\n");
}
```
项目->上传
```bash
 项目使用 217258 字节（16%）的程序存储空间。最大值为 1310720 字节。
 个全局变量使用 9836 个字节（3%）的动态内存，剩下 317844 个字节用于局部变量。最大值为 327680 字节。
esptool.py v4.2.1
Serial port COM8
Connecting....
Chip is ESP32-C3 (revision 3)
Features: Wi-Fi
Crystal is 40MHz
MAC: 60:55:f9:73:1b:54
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Flash will be erased from 0x00000000 to 0x00002fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Flash will be erased from 0x0000e000 to 0x0000ffff...
Flash will be erased from 0x00010000 to 0x00047fff...
Compressed 12144 bytes to 8800...
Writing at 0x00000000... (100 %)
Wrote 12144 bytes (8800 compressed) at 0x00000000 in 0.9 seconds (effective 104.5 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 128...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (128 compressed) at 0x00008000 in 0.1 seconds (effective 439.6 kbit/s)...
Hash of data verified.
Compressed 8192 bytes to 47...
Writing at 0x0000e000... (100 %)
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.1 seconds (effective 659.5 kbit/s)...
Hash of data verified.
Compressed 227280 bytes to 127913...
Writing at 0x00010000... (12 %)
Writing at 0x0001ab9d... (25 %)
Writing at 0x00021860... (37 %)
Writing at 0x00027832... (50 %)
Writing at 0x0002dbe0... (62 %)
Writing at 0x00033a77... (75 %)
Writing at 0x0003b754... (87 %)
Writing at 0x000426c8... (100 %)
Wrote 227280 bytes (127913 compressed) at 0x00010000 in 11.5 seconds (effective 157.6 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```
上传完成后，即可看见 GPIO00闪烁。并且通过串口监视器可以看到打印的 "hello wrold"。

#### Ref
[官网链接](https://wiki.luatos.com/chips/esp32c3/board.html)









