[TOC]

### I2C模块

#### 传输开始信号
```bash
SCL		 |			 |
	--------|-------------|
			|			 |---------
			|             |
SDA		 |             |
	--------|             |
    		|-------------|-------------------
            |             |
```

#### 传输结束信号
```bash
SCL		 |			 |
	--------|-------------|
			|			 |---------
			|             |
SDA		 |             |
	        |-------------|-------------------
    --------|             |
            |             |
```

首字节包括(从机地址(7bit) + 读写信号(1bit))（读 R： ‘1’，写 W： ‘0’）

#### 发送流程
主机: 开始信号 -> 发:首字节(写) -> 收:ACK -> 发:数据字节1 -> 收:ACK -> 发:数据字节n。

#### 接收流程
主机: 开始信号 -> 发:首字节(读) -> 收:ACK -> 收:数据字节1 -> 发:ACK -> 收:数据字节n。