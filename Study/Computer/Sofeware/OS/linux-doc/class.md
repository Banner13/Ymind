[TOC]

## Device Classes


### Introduction
	~~~~~~~~~~~~
	A device class describes a type of device, like an audio or network device. 
	The following device classes have been identified:
	一个device class描述同一类型的设备，比如音频或网络设备。
	已经确定了以下设备类别：

	<Insert List of Device Classes Here>
	<在此插入设备类别列表>。

	Each device class defines a set of semantics and a programming interface that devices of that class adhere to.
	Device drivers are the implementation of that programming interface for a particular device on a particular bus.
	每个设备类别都定义了一套语义和编程接口，该类型的设备都要遵守。
	设备驱动程序是对特定总线上特定设备的该编程接口的实现。

	Device classes are agnostic with respect to what bus a device resides on.
	device class与设备所处的总线不相干。

### Programming Interface
	~~~~~~~~~~~~~~~~~~~~~
	The device class structure looks like:
	device class的结构体如下：

	typedef int (*devclass_add)(struct device *);
	typedef void (*devclass_remove)(struct device *);

	struct device_class {
		char			* name;
		rwlock_t		lock;
		u32			devnum;
		struct list_head	node;

		struct list_head	drivers;
		struct list_head	intf_list;

		struct driver_dir_entry	dir;
		struct driver_dir_entry	device_dir;
		struct driver_dir_entry	driver_dir;

		devclass_add		add_device;
		devclass_remove		remove_device;
	};

	A typical device class definition would look like:
	一个典型device class定义如下：

	struct device_class input_devclass = {
			.name		= "input",
			.add_device	= input_add_device,
		.remove_device	= input_remove_device,
	};

	Each device class structure should be exported in a header file so it can be used by drivers, extensions and interfaces.
	每个device class结构都应该在头文件中导出，这样它就可以被驱动、扩展和接口使用。

	Device classes are registered and unregistered with the core using:
	device class被注册和取消注册的核心使用：

	int devclass_register(struct device_class * cls);
	void devclass_unregister(struct device_class * cls);


### Devices
	~~~~~~~
	As devices are bound to drivers, they are added to the device class that the driver belongs to.
	Before the driver model core, this would typically happen during the driver's probe() callback, once the device has been initialized.
	It now happens after the probe() callback finishes from the core.
	当设备被驱动绑定后，它们会被添加到驱动所属device class中。
	在驱动模型核心之前，这通常发生在驱动的probe()回调期间，一旦设备被初始化。
	现在，它发生在来自核心的probe()回调完成之后。

	The device is enumerated in the class.
	Each time a device is added to the class, the class's devnum field is incremented and assigned to the device.
	The field is never decremented, so if the device is removed from the class and re-added, it will receive a different enumerated value.
	该设备被枚举到这个class中。
	每次一个设备被添加到类中，class的devnum字段就会被递增并分配给该设备。
	该字段永远不会被递减，所以如果设备被从类中移除并重新添加，它将收到一个不同的枚举值。


	The class is allowed to create a class-specific structure for the device and store it in the device's class_data pointer.
	该类被允许为设备创建一个特定的类结构，并将其存储在设备的class_data指针中。

	There is no list of devices in the device class.
	Each driver has a list of devices that it supports.
	The device class has a list of drivers of that particular class.
	To access all of the devices in the class, iterate over the device lists of each driver in the class.
	在device class中没有设备的列表。
	每个驱动程序都有一个它所支持的设备的列表。
	device class有一个该特定类的驱动程序的列表。
	要访问该类中的所有设备，需要遍历该类中每个驱动程序的设备列表。


### Device Drivers
	~~~~~~~~~~~~~~
	Device drivers are added to device classes when they are registered with the core.
	A driver specifies the class it belongs to by setting the struct device_driver::devclass field.
	当内核完成注册，设备驱动被添加到该设备类。
	驱动程序通过设置struct device_driver::devclass字段来指定它所属的类别。

	sysfs directory structure
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	There is a top-level sysfs directory named 'class'.
	这是"class"的顶层目录。

	Each class gets a directory in the class directory, along with two default subdirectories:
			class/
			`-- input
					|-- devices
					`-- drivers
	每个类在类目录中得到一个目录，同时还有两个默认的子目录：

	Drivers registered with the class get a symlink in the drivers/ directory  that points to the driver's directory (under its bus directory):
	   class/
	   `-- input
		   |-- devices
		   `-- drivers
			   `-- usb:usb_mouse -> ../../../bus/drivers/usb_mouse/
	在该类中注册的驱动程序在drivers/目录中得到一个符号链接，指向驱动程序的目录（在其总线目录下）：

	Each device gets a symlink in the devices/ directory that points to the device's directory in the physical hierarchy:
	   class/
	   `-- input
		   |-- devices
		   |   `-- 1 -> ../../../root/pci0/00:1f.0/usb_bus/00:1f.2-1:0/
		   `-- drivers
	每个设备在devices/目录下得到一个符号链接，指向物理层次结构中的设备目录：

### Exporting Attributes
	~~~~~~~~~~~~~~~~~~~~
	struct devclass_attribute {
			struct attribute        attr;
			ssize_t (*show)(struct device_class *, char * buf, size_t count, loff_t off);
			ssize_t (*store)(struct device_class *, const char * buf, size_t count, loff_t off);
	};

	Class drivers can export attributes using the DEVCLASS_ATTR macro that works similarly to the DEVICE_ATTR macro for devices.
	For example, a definition like this:
	类驱动可以使用DEVCLASS_ATTR宏导出属性，其工作原理与设备的DEVICE_ATTR宏相似。
	例如，像这样的定义：

	static DEVCLASS_ATTR(debug,0644,show_debug,store_debug);

	is equivalent to declaring:
	等效于声明：

	static devclass_attribute devclass_attr_debug;

	The bus driver can add and remove the attribute from the class's sysfs directory using:
	总线驱动器可以使用以下方法从类的sysfs目录中添加和删除该属性：

	int devclass_create_file(struct device_class *, struct devclass_attribute *);
	void devclass_remove_file(struct device_class *, struct devclass_attribute *);

	In the example above, the file will be named 'debug' in placed in the class's directory in sysfs.
	在上面的例子中，该文件将被命名为 "debug"，放在sysfs的类的目录中。

### Interfaces
	~~~~~~~~~~
	There may exist multiple mechanisms for accessing the same device of a particular class type. Device interfaces describe these mechanisms.
	可能存在多种机制来访问某一特定类别类型的同一设备。设备接口描述了这些机制。

	When a device is added to a device class, the core attempts to add it to every interface that is registered with the device class.
	当一个设备被添加到一个设备类中时，核心会尝试将其添加到与该设备类注册的每个接口中。
