[TOC]

## The Linux Kernel Device Model

	Patrick Mochel	<mochel@digitalimplant.org>

	Drafted 26 August 2002
	Updated 31 January 2006


### Overview
	~~~~~~~~
	The Linux Kernel Driver Model is a unification of all the disparate driver models that were previously used in the kernel. 
	Linux内核驱动模型是对以前kernel中各种驱动模型的一种统一。

	It is intended to augment the bus-specific drivers for bridges and devices by consolidating a set of data and operations into globally accessible data structures.
	目的是为了通过整合一些数据和操作到一个全局可访问的数据结构中，来增强总线上的桥和设备的特定驱动程序。

	Traditional driver models implemented some sort of tree-like structure (sometimes just a list) for the devices they control.
	经典的驱动模型通常使用树状结构或是链表去控制的。

	There wasn't any uniformity across the different bus types.
	它们没有统一的方式去访问不同的总线类型。

	The current driver model provides a common, uniform data model for describing a bus and the devices that can appear under the bus.
	而当前的驱动模型提供了一种通用、统一的数据模型来描述总线和那些可以挂载在总线上的设备。

	The unified bus model includes a set of common attributes which all busses carry,
		and a set of common callbacks, such as device discovery during bus probing, bus shutdown, bus power management, etc.
	该统一模型包括了一组所有总线都拥有的通用属性。
		还有一些通用回调功能，例如在总线探测期间发现设备，关闭总线，总线电源管理等等。

	The common device and bridge interface reflects the goals of the modern computer:
		namely the ability to do seamless device "plug and play", power management, and hot plug. 
	通用设备和桥接接口反映了现代计算机的目标：
		即“即插即用”的无缝连接能力，电源管理和热插拔。

	In particular,
		the model dictated by Intel and Microsoft (namely ACPI) ensures that almost every device on almost any bus on an x86-compatible system can work within this paradigm.
	尤其是，
		该模型的规范完全符合Intel和Microsoft的ACPI模型，因此所有能在X86上运行的设备都能使用该模型。

	Of course, not every bus is able to support all such operations, although most buses support a most of those operations.
	当然。不是每一个总线都能够支持所有的操作，尽管如此大部分总线都支持大多数的操作。

### Downstream Access
	~~~~~~~~~~~~~~~~~
	Common data fields have been moved out of individual bus layers into a common data structure.
	通用数据字段已经从单独的总线层移入到了一个通用数据结构中。

	These fields must still be accessed by the bus layers, and sometimes by the device-specific drivers.
	总线层需要保持对这些字段的访问，有时特殊的驱动也会去访问它。

	Other bus layers are encouraged to do what has been done for the PCI layer.
	其他的总线层也应该想PCI层一样去处理。

	struct pci_dev now looks like this:
	新的pci-dev 大概是这样：

	struct pci_dev {
		...

		struct device dev;
	};

	Note first that it is statically allocated. 
		This means only one allocation on device discovery. 
	首先注意，这是静态分配的。
		也意味着只会在发现设备的时候去分配一次。

	Note also that it is at the _end_ of struct pci_dev. 
		This is to make people think about what they're doing when switching between the bus driver and the global driver; 
		and to prevent against mindless casts between the two.
	还需要注意，struct device dev 在pci_dev的最后。
		这是为了让人们在总线驱动、全局驱动进行转换的时候意识到他们在做什么。
		防止在不了解的情况下将他们进行转换。

	The PCI bus layer freely accesses the fields of struct device. 
	It knows about the structure of struct pci_dev, and it should know the structure of struct device.
	Individual PCI device drivers that have been converted to the current driver model generally do not and should not touch the fields of struct device,
	unless there is a strong compelling reason to do so.
	PCI总线可以任意访问struct  device字段。
	它了解pic_dev的组成，同样也了解struct device。
	已经转换为当前驱动程序模型的单个PCI设备驱动程序通常是不会，并且也不应该去访问struct device字段。
	除非有必需的原因。

	This abstraction is prevention of unnecessary pain during transitional phases.
	If the name of the field changes or is removed, then every downstream driver will break. 
	On the other hand, if only the bus layer (and not the device layer) accesses struct device, it is only that layer that needs to change.
	这种抽象是防止在过渡阶段出现不必要的麻烦。
	如果struct  device的名字被改变，那么下游的所有驱动都会罢工。
	另一方面，如果只有总线层（而不是设备层）访问struct  device，则只有该层需要改变。

### User Interface
	~~~~~~~~~~~~~~
	By virtue of having a complete hierarchical view of all the devices in the system, 
	exporting a complete hierarchical view to userspace becomes relatively easy. 
	This has been accomplished by implementing a special purpose virtual file system named sysfs.
	It is hence possible for the user to mount the whole sysfs filesystem anywhere in userspace.
	由于拥有系统中所有设备的完整分层视图、 
	将一个完整的分层视图输出到用户空间变得相对容易。
	这是通过实现一个名为sysfs的特殊目的虚拟文件系统来实现的。
	因此，用户有可能在用户空间的任何地方挂载整个sysfs文件系统。

	This can be done permanently by providing the following entry into the /etc/fstab (under the provision that the mount point does exist, of course):
	这可以通过在/etc/fstab中提供以下条目永久完成（当然是在挂载点确实存在的前提下）：

	none     	/sys	sysfs    defaults		0	0

	Or by hand on the command line:
	或者使用以下的命令行：

	# mount -t sysfs sysfs /sys

	Whenever a device is inserted into the tree, a directory is created for it.
	This directory may be populated at each layer of discovery - the global layer, the bus layer, or the device layer.
	每当一个设备被插入树中，就会为它创建一个目录。
	这个目录可以在每一层发现中被填充--全局层、总线层或设备层。

	The global layer currently creates two files - 'name' and 'power'. 
	The former only reports the name of the device. The latter reports the current power state of the device.
	It will also be used to set the current power state. 
	全局层目前创建了两个文件--'name'和'power'。
	前者只报告设备的名称。后者报告设备的当前电源状态。
	它也将被用来设置当前的电源状态。

	The bus layer may also create files for the devices it finds while probing the bus.
	For example, the PCI layer currently creates 'irq' and 'resource' files for each PCI device.
	总线层也可以为它在探测总线时发现的设备创建文件。
	例如，PCI层目前为每个PCI设备创建 "irq "和 "resource "文件。

	A device-specific driver may also export files in its directory to expose device-specific data or tunable interfaces.
	特定设备的驱动程序也可以在其目录中导出文件，以暴露特定设备的数据或可调整接口。

	More information about the sysfs directory layout can be found in the other documents in this directory and in the file  Documentation/filesystems/sysfs.txt.
	关于sysfs目录布局的更多信息可以在本目录的其他文件和文件中找到。

