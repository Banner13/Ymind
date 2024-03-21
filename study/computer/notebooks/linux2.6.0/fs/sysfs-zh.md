

sysfs - _The_ filesystem for exporting kernel objects. 

Patrick Mochel	<mochel@osdl.org>

10 January 2003


sysfs是什么:

	sysfs 是一种基于 ram 的文件系统，最初以 ramfs 为基础。它提供了一种将内核数据结构、其属性以及二者间联系导出到用户空间的方法。
	
	sysfs 与 kobject 基础架构有着内在的联系。有关 kobject 接口的更多信息，请阅读 Documentation/kobject.txt。


使用 sysfs:

	sysfs总是会被编译进来。你可以通过以下方法来访问:
    mount -t sysfs sysfs /sys 


文件夹创建

	系统会为每个注册的 kobject 在 sysfs 中创建一个目录。它作为 kobject.parent 的子目录被创建，向用户空间表达内部对象层次结构。
	sysfs 中的顶级目录代表了对象层次结构的共同祖先; 即对象所属的子系统。
	
	Sysfs 内部会将该目录的所有者 kobject 保存在结构成员 dentry 的 ->d_fsdata 指针中。 这允许 sysfs 在打开和关闭文件时直接对 kobject 进行引用计数。


属性
	
	kobjects 属性能够以文件系统中普通文件的形式导出。通过将文件 I/O 操作传递给为属性定义的方法，Sysfs 提供了一种读写内核属性的方法。
	
	属性应为 ASCII 文本文件，每个文件最好只有一个值。需要注意的是，每个文件只包含一个值可能效率不高，因此，表达同一类型的数组值是可以接受的。
	
	混合类型、表达多行数据以及对数据进行花哨的格式化都是不允许的。做这些事情可能会让你受到公开羞辱，并在不经通知的情况下重写你的代码。
	
	
	属性的定义很简单：
	
	struct attribute {
	        char                    * name;
	        mode_t                  mode;
	};
	
	
	int sysfs_create_file(struct kobject * kobj, struct attribute * attr);
	void sysfs_remove_file(struct kobject * kobj, struct attribute * attr);
	
	
	单纯的 attribute，本身没有提供读取或写入属性值的方法。Subsystems 鼓励为特定对象类型定义其自己的属性结构和包装函数，以便添加和删除属性。
	例如，驱动模型定义的 struct device_attribute 是这样的：
	
	struct device_attribute {
	        struct attribute        attr;
	        ssize_t (*show)(struct device * dev, char * buf);
	        ssize_t (*store)(struct device * dev, const char * buf);
	};
	
	int device_create_file(struct device *, struct device_attribute *);
	void device_remove_file(struct device *, struct device_attribute *);
	
	它还定义了用于定义设备属性的辅助函数：
	
	#define DEVICE_ATTR(_name,_mode,_show,_store)      \
	struct device_attribute dev_attr_##_name = {            \
	        .attr = {.name  = __stringify(_name) , .mode   = _mode },      \
	        .show   = _show,                                \
	        .store  = _store,                               \
	};
	
	举例来说，声明：
	
	static DEVICE_ATTR(foo,0644,show_foo,store_foo);
	
	相当于执行以下操作：
	
	static struct device_attribute dev_attr_foo = {
	       .attr	= {
			.name = "foo",
			.mode = 0644,
		},
		.show = show_foo,
		.store = store_foo,
	};


Subsystem-Specific Callbacks
	当一个 Subsystem 定义一个新的属性类型时，它必须实现一组 sysfs 操作，以便将读取和写入调用转发到属性所有者的 show 和 store 方法。
	
	struct sysfs_ops {
	        ssize_t (*show)(struct kobject *, struct attribute *,char *);
	        ssize_t (*store)(struct kobject *,struct attribute *,const char *);
	};
	
	[ Subsystem 应该已经定义了一个 struct kobj_type 作为该类型的描述符，其中存储了 sysfs_ops 指针。有关更多信息，请参阅 kobject 文档。 ]

	当文件被读取或写入时，sysfs 调用适合该类型的方法。然后，该方法将通用的 struct kobject 和 struct attribute 指针转换为适当的指针类型，并调用相关的方法。


举例说明:

	#define to_dev_attr(_attr) container_of(_attr, struct device_attribute, attr) 
	#define to_dev(d) container_of(d, struct device, kobj)

	static ssize_t
	dev_attr_show(struct kobject * kobj, struct attribute * attr, char * buf)
	{
	        struct device_attribute * dev_attr = to_dev_attr(attr);
	        struct device * dev = to_dev(kobj);
	        ssize_t ret = 0;
	
	        if (dev_attr->show)
	                ret = dev_attr->show(dev,buf);
	        return ret;
	}



读/写 Attribute 数据

	要读取或写入属性，必须在声明属性时指定 show() 或 store() 方法。这些方法的类型应该与设备属性定义的方法一样简单：

        ssize_t (*show)(struct device * dev, char * buf);
        ssize_t (*store)(struct device * dev, const char * buf);

	换句话说，这些方法应该只接受一个对象、一个属性和一个缓冲区作为参数。

	sysfs 分配了一个大小为 (PAGE_SIZE) 的缓冲区，并将其传递给方法。Sysfs 将会为每次读取或写入调用该方法一次。这强制了以下行为在方法实现上的表现：

	-在读取时（read(2)调用），show() 方法应该填满整个缓冲区。需要注意的是，一个属性应该只导出一个值，或者一组类似的值，所以这不应该很昂贵。

	这样可以让用户空间以任意方式对整个文件进行部分读取和随意寻址。

	-在写入时（write(2)调用），sysfs 期望在第一次写入时传递整个缓冲区。然后，sysfs 将整个缓冲区传递给 store() 方法。 

	在写入 sysfs 文件时，用户空间进程应该先读取整个文件，修改它希望更改的值，然后将整个缓冲区写回。 

	属性方法的实现应该在读取和写入值时操作相同的缓冲区。

	其他注意事项：

- 写入操作会导致 show() 方法重新启用，不考虑当前文件位置。
- 缓冲区的长度始终为 PAGE_SIZE 字节。在 i386 上，这是 4096 字节。
- show() 方法应返回打印到缓冲区的字节数。这是 snprintf() 的返回值。
- show() 应始终使用 snprintf()。
- store() 应返回从缓冲区使用的字节数。可以使用 strlen() 完成。
- show() 或 store() 可以始终返回错误。如果出现错误的值，请确保返回错误。
- 通过方法传递的对象将通过 sysfs 引用计数其嵌入对象而被固定在内存中。然而，对象表示的物理实体（例如设备）可能不存在。如果必要，确保有一种检查的方法。


	一个非常简单（且幼稚）的设备属性的实现如下：

	static ssize_t show_name(struct device * dev, char * buf)
	{
	        return sprintf(buf,"%s\n",dev->name);
	}
	
	static ssize_t store_name(struct device * dev, const char * buf)
	{
		sscanf(buf,"%20s",dev->name);
		return strlen(buf);
	}
	
	static DEVICE_ATTR(name,S_IRUGO,show_name,store_name);


(需要注意的是，实际的实现不允许用户空间设置设备的名称。)


Top Level Directory Layout

	sysfs 的目录布局展示了内核数据结构之间的关系。
	
	顶级 sysfs 目录如下所示：

	block/
	bus/
	class/
	devices/
	firmware/
	net/

	devices/ 目录包含了设备树的文件系统表示。它直接映射到内核的设备树，这是一个 struct device 层次结构。
	
	bus/ 目录包含了内核中各种总线类型的平面目录布局。每个总线的目录包含两个子目录：

	devices/
	drivers/

	devices/ 目录包含了系统中每个发现的设备的符号链接，指向根目录下设备的目录。
	
	drivers/ 目录包含了为该特定总线上的设备加载的每个设备驱动程序的目录（假设驱动程序不跨越多个总线类型）。


	更多关于驱动模型特定功能的信息可以在 Documentation/driver-model/ 中找到。
	
	待办事项：完成这一部分。


Current Interfaces

	目前在 sysfs 中存在以下接口层：

	- devices (include/linux/device.h)
	----------------------------------
	Structure:
	
	struct device_attribute {
	        struct attribute        attr;
	        ssize_t (*show)(struct device * dev, char * buf);
	        ssize_t (*store)(struct device * dev, const char * buf);
	};

	声明：
	
	DEVICE_ATTR(_name, _str, _mode, _show, _store);
	
	创建/移除：

	int device_create_file(struct device *device, struct device_attribute * attr);
	void device_remove_file(struct device * dev, struct device_attribute * attr);
	
	
	- bus drivers (include/linux/device.h)
	--------------------------------------
	Structure:
	
	struct bus_attribute {
	        struct attribute        attr;
	        ssize_t (*show)(struct bus_type *, char * buf);
	        ssize_t (*store)(struct bus_type *, const char * buf);
	};
	
	Declaring:
	
	BUS_ATTR(_name,_mode,_show,_store)
	
	Creation/Removal:
	
	int bus_create_file(struct bus_type *, struct bus_attribute *);
	void bus_remove_file(struct bus_type *, struct bus_attribute *);
	
	
	- device drivers (include/linux/device.h)
	-----------------------------------------
	
	Structure:
	
	struct driver_attribute {
	        struct attribute        attr;
	        ssize_t (*show)(struct device_driver *, char * buf);
	        ssize_t (*store)(struct device_driver *, const char * buf);
	};
	
	Declaring:
	
	DRIVER_ATTR(_name,_mode,_show,_store)
	
	Creation/Removal:
	
	int driver_create_file(struct device_driver *, struct driver_attribute *);
	void driver_remove_file(struct device_driver *, struct driver_attribute *);


