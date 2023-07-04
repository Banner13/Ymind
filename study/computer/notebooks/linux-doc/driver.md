[TOC]

## Device Drivers
    See the kernel doc for the struct device_driver.
    请参阅内核文档中的struct device_driver。

### Allocation
    ~~~~~~~~~~
    Device drivers are statically allocated structures.
    Though there may be multiple devices in a system that a driver supports,
    struct device_driver represents the driver as a whole (not a particular device instance).
    设备驱动程序是静态分配的结构。
    尽管在一个系统中可能有多个设备被一个驱动程序支持、
    结构device_driver代表整个驱动程序（而不是一个特定的设备实例）。

### Initialization
    ~~~~~~~~~~~~~~
    The driver must initialize at least the name and bus fields.
    It should also initialize the devclass field (when it arrives), so it may obtain the proper linkage internally.
    It should also initialize as many of the callbacks as possible, though each is optional.
    驱动程序必须至少初始化name和bus字段。
    它还应该初始化devclass字段（当它到达时），这样它可以在内部获得适当的链接。
    它还应该尽可能多地初始化回调，尽管每个回调都是可选的。

Declaration
    ~~~~~~~~~~~
    As stated above, struct device_driver objects are statically allocated.
    Below is an example declaration of the eepro100 driver.
    This declaration is hypothetical only;
    it relies on the driver being converted completely to the new model.
    如上所述，struct device_driver对象是静态分配的。
    下面是一个eepro100驱动的声明实例。
    这个声明只是假设性的；
    它依赖于驱动被完全转换为新的模型。

    static struct device_driver eepro100_driver = {
           .name		= "eepro100",
           .bus		= &pci_bus_type,
           .probe		= eepro100_probe,
           .remove		= eepro100_remove,
           .suspend		= eepro100_suspend,
           .resume		= eepro100_resume,
    };

    Most drivers will not be able to be converted completely to the new model
    because the bus they belong to has a bus-specific structure with bus-specific fields that cannot be generalized.
    大多数驱动程序不能完全转换为新的模式
    因为它们所属的总线有一个特定的总线结构，有特定的总线字段，不能被通用化。

    The most common example of this are device ID structures.
    A driver typically defines an array of device IDs that it supports.
    The format of these structures and the semantics for comparing device IDs are completely bus-specific.
    Defining them as bus-specific entities would sacrifice type-safety, so we keep bus-specific structures around.
    这方面最常见的例子是设备ID结构。
    一个驱动程序通常定义了一个它所支持的设备ID数组。
    这些结构的格式和比较设备ID的语义是完全针对总线的。
    将它们定义为总线专用实体会牺牲类型安全，所以我们保留总线专用结构。

    Bus-specific drivers should include a generic struct device_driver in the definition of the bus-specific driver. Like this:
    总线专用驱动程序应该在总线专用驱动程序的定义中包括一个通用结构device_driver。像这样：

    struct pci_driver {
           const struct pci_device_id *id_table;
           struct device_driver	  driver;
    };

    A definition that included bus-specific fields would look like (using the eepro100 driver again):
    包括总线特定字段的定义看起来像（再次使用eepro100驱动程序）：

    static struct pci_driver eepro100_driver = {
           .id_table       = eepro100_pci_tbl,
           .driver	       = {
            .name		= "eepro100",
            .bus		= &pci_bus_type,
            .probe		= eepro100_probe,
            .remove		= eepro100_remove,
            .suspend	= eepro100_suspend,
            .resume		= eepro100_resume,
           },
    };

    Some may find the syntax of embedded struct initialization awkward or even a bit ugly.
    So far, it's the best way we've found to do what we want...
    有些人可能会发现嵌入式结构初始化的语法很笨拙，甚至有点难看。
    到目前为止，这是我们找到的最好的方法，可以实现我们想要的东西...

### Registration
    ~~~~~~~~~~~~
    int driver_register(struct device_driver * drv);

    The driver registers the structure on startup.
    For drivers that have no bus-specific fields (i.e. don't have a bus-specific driver structure),
    they would use driver_register and pass a pointer to their struct device_driver object.
    驱动程序在启动时注册了该结构。
    对于那些没有总线专用字段的驱动程序(即没有总线专用的驱动结构)、
    他们将使用driver_register并传递一个指向他们的struct device_driver对象的指针。

    Most drivers, however, will have a bus-specific structure and will need to register with the bus using something like pci_driver_register.
    然而，大部分驱动程序会拥有一个特定于总线的结构，需要通过类似于pci_driver_register的方法在总线上进行注册。

    It is important that drivers register their driver structure as early as possible.
    Registration with the core initializes several fields in the struct device_driver object, including the reference count and the lock.
    These fields are assumed to be valid at all times and may be used by the device model core or the bus driver.
    重要的是，驱动要尽早建立起自己的驱动结构。
    向内核注册时，会初始化struct device_driver对象中的几个字段，包括引用计数和锁。
    这些字段被认为在任何时候都是有效的，可以由设备模型内核或总线驱动器使用。

### Transition Bus Drivers
    ~~~~~~~~~~~~~~~~~~~~~~
    By defining wrapper functions, the transition to the new model can be made easier.
    Drivers can ignore the generic structure altogether and let the bus wrapper fill in the fields.
    For the callbacks, the bus can define generic callbacks that forward the call to the bus-specific callbacks of the drivers.
    通过定义包装函数，可以更容易地过渡到新模型。
    驱动程序可以完全忽略通用结构，让总线包装器来填写字段。
    对于回调，总线可以定义通用回调，将调用转发到驱动程序的总线特定回调。

    This solution is intended to be only temporary.
    In order to get class information in the driver, the drivers must be modified anyway.
    Since converting drivers to the new model should reduce some infrastructural complexity and code size,
    it is recommended that they are converted as class information is added.
    这个解决方案的目的只是暂时的。
    为了在驱动中获得类信息，无论如何都必须修改驱动。
    由于将驱动程序转换到新的模型，应该减少一些基础结构的复杂性和代码大小、
    我们建议在添加类信息的同时对它们进行转换。

### Access
    ~~~~~~
    Once the object has been registered, it may access the common fields of the object, like the lock and the list of devices.
    一旦对象被注册，它就可以访问对象的普通字段，如锁和设备列表。

    int driver_for_each_dev(struct device_driver * drv, void * data,
                    int (*callback)(struct device * dev, void * data));

    The devices field is a list of all the devices that have been bound to the driver.
    The LDM core provides a helper function to operate on all the devices a driver controls.
    This helper locks the driver on each node access, and does proper reference counting on each device as it accesses it.
    设备字段是一个所有被绑定到驱动程序的设备的列表。
    LDM核心提供了一个辅助函数来操作驱动控制的所有设备。
    这个辅助函数在每个节点的访问上锁定驱动程序，并在访问每个设备时对其进行适当的引用计数。

### sysfs
    ~~~~~
    When a driver is registered, a sysfs directory is created in its bus's directory.
    In this directory, the driver can export an interface to userspace to control operation of the driver on a global basis;
    e.g. toggling debugging output in the driver.
    当一个驱动程序被注册时，在其总线的目录中会创建一个sysfs目录。
    在这个目录中，驱动程序可以向用户空间输出一个接口，以便在全局基础上控制驱动程序的操作；
    例如，在驱动程序中切换调试输出。

    A future feature of this directory will be a 'devices' directory.
    This directory will contain symlinks to the directories of devices it supports.
    这个目录的一个未来特征将是一个 "devices "目录。
    这个目录将包含指向它所支持的设备目录的符号链接。


### Callbacks
    ~~~~~~~~~
        int	(*probe)	(struct device * dev);

    The probe() entry is called in task context, with the bus's rwsem locked and the driver partially bound to the device.
    Drivers commonly use container_of() to convert "dev" to a bus-specific type, both in probe() and other routines.
    That type often provides device resource data, such as pci_dev.resource[] or platform_device.resources,
    which is used in addition to dev->platform_data to initialize the driver.
    probe()条目是在任务上下文中调用的，总线的rwsem被锁定，驱动部分地与设备绑定。
    驱动程序通常使用container_of()将 "dev "转换为总线专用类型，在probe()和其他例程中都是如此。
    该类型通常提供设备资源数据，如pci_dev.resource[] 或platform_device.resources、
    除了用于dev->platform_data之外，还用于初始化驱动程序。

    This callback holds the driver-specific logic to bind the driver to a given device.
    That includes verifying that the device is present, that it's a version the driver can handle,
    that driver data structures can be allocated and initialized, and that any hardware can be initialized.
    Drivers often store a pointer to their state with dev_set_drvdata().
    When the driver has successfully bound itself to that device,
    then probe() returns zero and the driver model code will finish its part of binding the driver to that device.
    这个回调持有特定的驱动逻辑，以将驱动绑定到一个给定的设备。
    这包括验证设备是否存在，它是否是驱动可以处理的版本、
    驱动程序的数据结构可以被分配和初始化，以及任何硬件可以被初始化。
    驱动程序通常用dev_set_drvdata()存储一个指向其状态的指针。
    当驱动程序成功地将自己绑定到该设备上时、
    然后probe()返回0，驱动模型代码将完成它与该设备的绑定部分。

    A driver's probe() may return a negative errno value to indicate that the driver did not bind to this device,
    in which case it should have released all resources it allocated.
    驱动程序的probe()可能会返回一个负的errno值，表示驱动程序没有绑定到这个设备、
    在这种情况下，它应该释放它分配的所有资源。
        int 	(*remove)	(struct device * dev);

    remove is called to unbind a driver from a device.
    This may be called if a device is physically removed from the system,
    if the driver module is being unloaded, during a reboot sequence, or in other cases.
    remove被调用以解除设备对驱动程序的绑定。
    如果一个设备被从系统中移除，可能会调用这个函数、
    如果驱动模块被卸载，在重启过程中，或者在其他情况下，都可以调用这个功能。


    It is up to the driver to determine if the device is present or not.
    It should free any resources allocated specifically for the device; i.e. anything in the device's driver_data field.
    由驱动来确定设备是否存在。
    它应该释放任何专门为该设备分配的资源；即设备的driver_data字段中的任何资源。

    If the device is still present, it should quiesce the device and place it into a supported low-power state.
    如果设备仍然存在，它应该使设备静止，并将其置于支持的低功率状态。

        int	(*suspend)	(struct device * dev, pm_message_t state);

    suspend is called to put the device in a low power state.
    调用suspend来使设备处于低功率状态。

        int	(*resume)	(struct device * dev);

    Resume is used to bring a device back from a low power state.
    恢复是用来将一个设备从低功率状态恢复过来。

### Attributes
    ~~~~~~~~~~
    struct driver_attribute {
            struct attribute        attr;
            ssize_t (*show)(struct device_driver *driver, char *buf);
            ssize_t (*store)(struct device_driver *, const char * buf, size_t count);
    };

    Device drivers can export attributes via their sysfs directories.
    Drivers can declare attributes using a DRIVER_ATTR macro that works identically to the DEVICE_ATTR macro.
    设备驱动可以通过他们的sysfs目录导出属性。
    驱动程序可以使用DRIVER_ATTR宏来声明属性，其作用与DEVICE_ATTR宏相同。

    Example:

    DRIVER_ATTR(debug,0644,show_debug,store_debug);

    This is equivalent to declaring:
    这相当于声明：

    struct driver_attribute driver_attr_debug;

    This can then be used to add and remove the attribute from the driver's directory using:
    然后，这可以用来从驱动程序的目录中添加和删除该属性，使用：

    int driver_create_file(struct device_driver *, const struct driver_attribute *);
    void driver_remove_file(struct device_driver *, const struct driver_attribute *);
