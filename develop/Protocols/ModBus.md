[TOC]

## ModBus

	ADU 应用数据单元
	PDU 协议数据单元

	Byte = B

	大端模式存储

	四种数据模型
	Discreates Input
		single bit
		read-only
	Coils
		single bit
		read-write
	Input Registers
		word(16bit)
		read-only
	Holding Registers
		word(16bit)
		read-write

### 数据帧格式

	ADU = (设备地址(1B) + PDU(...) + CRC校验(2B))

	RS232 / RS485 ADU = 253 字节+服务器地址(1 byte) + CRC (2 字节) = 256 字节。
	TCP MODBUS ADU = 249 字节+ MBAP (7 字节) = 256 字节。

###
	事务处理流程
![](./modbus.png)

#### PDU
	PDU = (功能码(1B) + 数据(...))
	MODBUS 协议定义了三种 PDU。它们是：
	l MODBUS 请求 PDU，mb_req_pdu
	l MODBUS 响应 PDU，mb_rsp_pdu
	l MODBUS 异常响应 PDU，mb_excep_rsp_pdu (功能码 + 0x80)

#### 功能码
##### 公共功能码
![](modbus3.png)

###### 0x01 读线圈(按位读寄存器位)
		请求：功能码(1B) + 起始地址(2B) + 请求数量(2B)(bit个数)(1 - 2000)
		响应：功能码(1B) + 返回字节数(1B) + 返回寄存器状态(xB)
		响应值8bit对齐，不足补零。
![](modbus1.png)

###### 0x02 读离散量输入
	类似 0x01

###### 0x03 读保持寄存器
		请求：功能码(1B) + 起始地址(2B) + 请求数量(2B)(word个数)(1 - 125)
		响应：功能码(1B) + 返回字节数(1B) + 返回寄存器状态(xB)(word格式)
		响应值8bit对齐，不足补零。
![](modbus2.png)

###### 0x04 读输入寄存器
	类似 0x03

###### 0x05 写单个线圈
		请求：功能码(1B) + 起始地址(2B) + 写入值(2B)(0x00000 or 0xFF00(其他值无效))
		响应：功能码(1B) + 返回地址(1B) + 返回寄存器状态(xB)(word格式)

###### 0x06 写单个寄存器
	类似 0x05

###### 0x0F 写多个线圈
		请求：功能码(1B) + 起始地址(2B) + 输出数量(2B) + 输出字节数(1B) + 输出值(xB)
		响应：功能码(1B) + 返回地址(1B) + 输出数量(2B)

###### 0x10 写多个寄存器
	类似 0x0F

##### 自定义功能码
	范围(65 - 72)和(100 - 110)
##### 保留功能码