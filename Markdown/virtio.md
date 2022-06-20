
# Each device consists of the following parts:
	? Device status field
	? Feature bits
	? Notifications
	? Device Configuration space
	? One or more virtqueues
	
	
##? Device status field 设备状态字段
	设备状态字段表示了驱动初始化的完成情况，驱动不可以清除以下位
		ACKNOWLEDGE (1)		表示the guest OS已经发现该设备，并将其识别为一个有效的虚拟设备
		DRIVER (2)			表示the guest OS知道如何驱动该设备
		FAILED (128)		表示the guest OS中出现了错误，并且它已经放弃了设备
		FEATURES_OK (8)		表示设备与驱动之间已经对其拥有的功能完成校验
		DRIVER_OK (4)		表示驱动程序可用
		DEVICE_NEEDS_RESET (64)	表示驱动程序遇到无法恢复的错误
		## 在DRIVER_OK之前，设备绝对不能消耗缓冲区或者发送任何已经使用的缓冲区通知给驱动。
		## 当设备进入需要重置的错误状态时，应该设置DEVICE_NEEDS_RESET。
		   如果设置了DRIVER_OK，在设置了DEVICE_NEEDS_RESET后，设备必须向驱动发送设备配置变更通知
		   
		   
##? Feature bits 功能描述位
	0 - 23，and 50 - 127 具体设备的功能位
	24 - 40 队列和特性协商机制的功能位，（扩展预留）
	41 - 49，and 大于128  未来功能位，（扩展预留）
	## For example： 功能描述位 0 代表 network ，如果 驱动ID & 0x01 == 1，表示这个设备支持 network 功能
	## 驱动不能接受设备未提供的功能。如果某个功能需要依赖其他功能，而其他功能不被支持，那么驱动不能接受该功能，反之同理
	
	
##? Notifications 驱动和设备之间的通知
	通知使用特殊的方式传输
	There are three types of notifications ：
	? configuration change notification	配置更改通知
	? available buffer notification	有效缓冲通知
	? used buffer notification	使用缓冲通知
	## 配置变更和使用缓冲区的通知由设备发出，驱动接收
	   配置更改通知表示设备配置空间已更改;
	   已使用缓冲区通知表示缓冲区已在通知指定的virtqueue上使用

	## 可用的缓冲区通知是由驱动发送的，接收方是设备
	   这种类型的通知表示，在通知指定的virtqueue上已经有一个缓冲区可用

	大多数传输实现通知使用设备发送给驱动程序的中断。因此，在该规范的以前版本中，这些通知通常被称为中断。这个规范中定义的一些名称仍然保留了这个中断术语。偶尔，事件一词被用来指通知或通知的接收
	
	
##? Device Configuration space
	## 设备配置空间通常用于很少更改或初始化时的参数。配置字段是可选的，它们的存在由功能位表示:该规范的未来版本可能会通过在尾部添加额外的字段来扩展设备配置空间
	## 注意:设备配置空间对多字节字段使用小端格式
	## 每个传输还提供设备配置空间的生成计数，只要对设备配置空间的两次访问可能会看到该空间的不同版本，该生成计数就会发生变化
	## 在驱动程序设置FEATURES_OK之前，设备允许读取任何特定设备的配置字段。这包括特性位条件字段，只要这些特性位是由设备提供的
	
	
##? One or more virtqueues
	Each virtqueue can consist of up to 3 parts:
	? Descriptor Area - used for describing buffers
	? Driver Area - extra data supplied by driver to the device
	? Device Area - extra data supplied by device to the driver
	
	Note that previous versions of this spec used different names for these parts (following 2.7):
	? Descriptor Table - for the Descriptor Area
	? Available Ring - for the Driver Area
	? Used Ring - for the Device Area
	
	每个驱动程序和设备都支持打包或散列的Virtqueue格式，或者两者都支持
	
	## 驱动程序通过向队列添加一个有效缓冲区的方式来向设备提供请求，例如，添加一个缓冲区描述请求到一个virtqueue，并可选地触发一个驱动事件，例如，向设备发送一个可用的缓冲区通知
	## 设备执行请求，完成后，添加一个已使用的缓冲区到队列中，也就是说，通过标记缓冲区已使用，让驱动程序知道。然后设备可以触发一个设备事件，例如，发送一个已使用的缓冲区通知给驱动程序
	## 设备报告它使用缓冲区写入内存的字节数。 这被称为“使用长度”
	## 设备通常不需要按照驱动程序提供缓冲区的相同顺序使用缓冲区
	## 有些设备总是按照可用的顺序使用描述符。这些设备可以提供VIRTIO_F_IN_ORDER特性。\
	   如果经过协商，这一知识可能允许优化或简化驱动程序和/或设备代码

# 设备复位
	驱动程序可能随时对设备进行复位;尤其是在在设备初始化和清除设备期间需要这样做
	驱动程序使用特定的传输用于启动复位机制
	设备必须在收到复位后，必须重新引导设备状态为 0
	在重新引导设备状态为 0 的复位完成之前，设备不能发送通知或者进行队列的交互，直到驱动重新初始化设备
	驱动程序在读取设备状态为 0 时应认为驱动程序发出的复位已完成。

#   This sequence to initialize a device :
	1. Reset the device.	设备复位
	2. Set the ACKNOWLEDGE status bit: the guest OS has noticed the device.	客户机发现设备
	3. Set the DRIVER status bit: the guest OS knows how to drive the device.	客户机找到设备的对应驱动
	4. Read device feature bits, and write the subset of feature bits understood by the OS and driver to the device. \
	   During this step the driver MAY read (but MUST NOT write) the device-specific configuration fields to check that \
	   it can support the device before accepting it.
	   ## 读取功能位，并将操作系统和驱动支持的对应功能位写入设备。
	   ## 在此步骤中，驱动可以读取（但不能写入）设备的配置字段，用以在接收设备前查看是否支持该设备
	5. Set the FEATURES_OK status bit. The driver MUST NOT accept new feature bits after this step.
	   ## 在此步骤后，驱动不接受新的功能
	6. Re-read device status to ensure the FEATURES_OK bit is still set: otherwise, \
	   the device does not support our subset of features and the device is unusable.
	   ## FEATURES_OK状态确认，如果失败，设备不可用
	7. Perform device-specific setup, including discovery of virtqueues for the device, optional per-bus setup, \
	   reading and possibly writing the device’s virtio configuration space, and population of virtqueues.
	   ## 执行特定设备的设置，包括发现设备的 virtqueue、可选的总线设置、读取和可能写入设备的 virtio 配置空间以及填充 virtqueue
	8. Set the DRIVER_OK status bit. At this point the device is “live”.

	## If any of these steps go irrecoverably wrong, the driver SHOULD set the FAILED status bit to indicate that \
	   it has given up on the device (it can reset the device later to restart if desired). \
	   The driver MUST NOT continue initialization in that case.
	   
	   The driver MUST NOT send any buffer available notifications to the device before setting DRIVER_OK.