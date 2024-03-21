[TOC]

## Bus Types
	Definition
	~~~~~~~~~~

	struct bus_type {
		char			* name;

		struct subsystem	subsys;
		struct kset		drivers;
		struct kset		devices;

		struct bus_attribute	* bus_attrs;
		struct device_attribute	* dev_attrs;
		struct driver_attribute	* drv_attrs;

		int		(*match)(struct device * dev, struct device_driver * drv);
		int		(*hotplug) (struct device *dev, char **envp, 
						int num_envp, char *buffer, int buffer_size);
		int		(*suspend)(struct device * dev, pm_message_t state);
		int		(*resume)(struct device * dev);
	};

	int bus_register(struct bus_type * bus);

	Declaration
	~~~~~~~~~~~

	Each bus type in the kernel (PCI, USB, etc) should declare one static object of this type.
	They must initialize the name field, and may optionally initialize the match callback.
	内核中的每一个总线类型应该声明一个有关于它自身的静态对象。
	必须初始化name字段，以及可选的初始化match回调。

	struct bus_type pci_bus_type = {
		   .name	= "pci",
		   .match	= pci_bus_match,
	};

	The structure should be exported to drivers in a header file:
	该结构对象应在头文件中对外声明：

	extern struct bus_type pci_bus_type;


### Registration
	~~~~~~~~~~~~
	When a bus driver is initialized, it calls bus_register.
	This initializes the rest of the fields in the bus object and inserts it into a global list of bus types.
	Once the bus object is registered, the fields in it are usable by the bus driver. 
	当一个总线驱动完成初始化后，它调用 bus_register。
	这将初始化该总线对象中的其余字段，并将其插入全局总线列表中。
	一旦该总线对象被注册，其中的字段就可以被总线驱动使用。

### Callbacks
	~~~~~~~~~
	match(): Attaching Drivers to Devices
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	The format of device ID structures and the semantics for comparing them are inherently bus-specific.
	Drivers typically declare an array of device IDs of devices they support that reside in a bus-specific driver structure.
	设备ID结构的格式和比较它们的语义是固有的总线特定的。
	驱动程序通常声明他们支持的设备ID数组，这些设备ID位于总线特定的驱动程序结构中。

	The purpose of the match callback is provide the bus an opportunity to determine 
	if a particular driver supports a particular device by comparing the device IDs the driver supports with the device ID of a particular device,
	without sacrificing bus-specific functionality or type-safety. 
	match回调的目的是允许总线通过比较驱动程序的设备支持ID和特定设备自身ID来确定该驱动程序是否支持该设备，而不牺牲总线的特定功能或类型安全。

	When a driver is registered with the bus, the bus's list of devices is iterated over,
	and the match callback is called for each device that does not have a driver associated with it.
	当一个驱动程序在总线上被注册时，总线上的设备列表被遍历，对于每个没有与之相关的驱动程序的设备，匹配回调被调用。


### Device and Driver Lists
	~~~~~~~~~~~~~~~~~~~~~~~
	The lists of devices and drivers are intended to replace the local lists that many buses keep.
	They are lists of struct devices and struct device_drivers, respectively.
	Bus drivers are free to use the lists as they please, but conversion to the bus-specific type may be necessary.
	这些设备和驱动程序的列表旨在取代许多当前的总线列表。
	分别是struct devices和struct device_drivers的列表。
	总线可以随意使用这些列表，但可能需要转换为其特殊的总线类型。

	The LDM core provides helper functions for iterating over each list.
	LDM核心提供了用于迭代每个列表的辅助函数。

	int bus_for_each_dev(struct bus_type * bus, struct device * start, void * data,
				 int (*fn)(struct device *, void *));

	int bus_for_each_drv(struct bus_type * bus, struct device_driver * start, 
				 void * data, int (*fn)(struct device_driver *, void *));

	These helpers iterate over the respective list, and call the callback for each device or driver in the list.
	All list accesses are synchronized by taking the bus's lock (read currently).
	The reference count on each object in the list is incremented before the callback is called;
	it is decremented after the next object has been obtained.
	The lock is not held when calling the callback. 
	这些辅助函数遍历列表，为列表中的每个设备或驱动调用回调。
	所有的列表访问都是通过获取总线锁（目前是读）来同步的。
	在调用回调之前，列表中每个对象的引用计数被增加；
	它在得到下一个对象后被减去。
	当回调被调用时，锁不会被保留。

### sysfs
	~~~~~~~~
	There is a top-level directory named 'bus'.
	有一个名为 "bus"的顶层目录。

	Each bus gets a directory in the bus directory, along with two default directories:
		/sys/bus/pci/
		|-- devices
		`-- drivers
	每一种总线类型都会在bus下生成一个目录，同时还有两个默认文件夹。

	Drivers registered with the bus get a directory in the bus's drivers directory:
		/sys/bus/pci/
		|-- devices
		`-- drivers
			|-- Intel ICH
			|-- Intel ICH Joystick
			|-- agpgart
			`-- e100
	在总线类型下注册的设备会生成在该总线类型下的一个子目录。

	Each device that is discovered on a bus of that type gets a symlink in the bus's devices directory to the device's directory in the physical hierarchy:
		/sys/bus/pci/
		|-- devices
		|   |-- 00:00.0 -> ../../../root/pci0/00:00.0
		|   |-- 00:01.0 -> ../../../root/pci0/00:01.0
		|   `-- 00:02.0 -> ../../../root/pci0/00:02.0
		`-- drivers
	在这种该总线类型上发现的每个设备在其总线的设备目录中都有一个符号链接，指向物理层次结构中的设备目录：

### Exporting Attributes
	~~~~~~~~~~~~~~~~~~~~
	struct bus_attribute {
		struct attribute	attr;
		ssize_t (*show)(struct bus_type *, char * buf);
		ssize_t (*store)(struct bus_type *, const char * buf, size_t count);
	};

	Bus drivers can export attributes using the BUS_ATTR macro that works similarly to the DEVICE_ATTR macro for devices.
	For example, a definition  like this:
	总线驱动器可以使用BUS_ATTR宏导出属性，其工作原理与设备的DEVICE_ATTR宏相似。
	例如，像这样的定义：

	static BUS_ATTR(debug,0644,show_debug,store_debug);

	is equivalent to declaring:
	等价于：

	static bus_attribute bus_attr_debug;

	This can then be used to add and remove the attribute from the bus's sysfs directory using:
	然后，这可以用来从总线的sysfs目录中添加和删除该属性，使用：

	int bus_create_file(struct bus_type *, struct bus_attribute *);
	void bus_remove_file(struct bus_type *, struct bus_attribute *);


