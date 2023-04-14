[TOC]


## The Basic Device Structure
    ~~~~~~~~~~~~~~~~~~~~~~~~~~

    See the kerneldoc for the struct device.
    参见内核文档中的struct device。

### Programming Interface
    ~~~~~~~~~~~~~~~~~~~~~
    The bus driver that discovers the device uses this to register the device with the core:

    int device_register(struct device * dev);
    发现设备的总线驱动器使用device_register将设备注册到内核上：

    The bus should initialize the following fields:
    总线应该初始化以下字段
        - parent
        - name
        - bus_id
        - bus

    A device is removed from the core when its reference count goes to　0.
    The reference count can be adjusted using:
    当一个设备的引用为0时，它将被移除。
    可以使用以下方式来引用设备：

    struct device * get_device(struct device * dev);
    void put_device(struct device * dev);

    get_device() will return a pointer to the struct device passed to it　if the reference is not already 0 (if it's in the process of being　removed already).
    get_device()将返回一个指向传递给它的结构体设备的指针，如果该引用尚未为0（如果它已经在被删除的过程中）。

    A driver can access the lock in the device structure using:
    驱动程序可以通过以下方式访问设备结构中的锁：

    void lock_device(struct device * dev);
    void unlock_device(struct device * dev);


### Attributes
    ~~~~~~~~~~
    struct device_attribute {
        struct attribute	attr;
        ssize_t (*show)(struct device *dev, struct device_attribute *attr,
                char *buf);
        ssize_t (*store)(struct device *dev, struct device_attribute *attr,
                 const char *buf, size_t count);
    };

    Attributes of devices can be exported by a device driver through sysfs.
    设备的属性可以由设备驱动程序通过sysfs导出。

    Please see Documentation/filesystems/sysfs.txt for more information on how sysfs works.
    关于sysfs如何工作的更多信息，请参见文档/文件系统/sysfs.txt。

    As explained in Documentation/kobject.txt,
    device attributes must be be created before the KOBJ_ADD uevent is generated.
    The only way to realize that is by defining an attribute group.
    正如文档/kobject.txt中所解释的、
    设备属性必须在KOBJ_ADD uevent产生之前被创建。
    实现的唯一方法是定义一个属性组。

    Attributes are declared using a macro called DEVICE_ATTR:
    属性是用一个叫做DEVICE_ATTR的宏来声明的：

    #define DEVICE_ATTR(name,mode,show,store)

    Example:

    static DEVICE_ATTR(type, 0444, show_type, NULL);
    static DEVICE_ATTR(power, 0644, show_power, store_power);

    This declares two structures of type struct device_attribute with respective names 'dev_attr_type' and 'dev_attr_power'.
    These two attributes can be organized as follows into a group:
    这声明了两个类型为struct device_attribute 的结构，分别命名为'dev_attr_type'和'dev_attr_power'。
    这两个属性可以如下组织成一个组：

    static struct attribute *dev_attrs[] = {
        &dev_attr_type.attr,
        &dev_attr_power.attr,
        NULL,
    };

    static struct attribute_group dev_attr_group = {
        .attrs = dev_attrs,
    };

    static const struct attribute_group *dev_attr_groups[] = {
        &dev_attr_group,
        NULL,
    };

    This array of groups can then be associated with a device by setting the group pointer in struct device before device_register() is invoked:
    在调用device_register()之前，通过在struct device中设置组指针，可以将这个组阵列与一个设备联系起来：
          dev->groups = dev_attr_groups;
          device_register(dev);

    The device_register() function will use the 'groups' pointer to create the device attributes
        and the device_unregister() function will use this pointer to remove the device attributes.
    device_register()函数将使用'group'指针来创建设备属性
        而device_unregister()函数将使用这个指针来删除设备属性。

    Word of warning:
    While the kernel allows device_create_file() and device_remove_file() to be called on a device at any time,
    userspace has strict expectations on when attributes get created.
    When a new device is registered in the kernel, a uevent is generated to notify userspace (like udev) that a new device is available.
    If attributes are added after the device is registered, then userspace won't get notified and userspace will not know about the new attributes.
    警告一下：
    虽然内核允许在任何时候在一个设备上调用device_create_file()和device_remove_file()、
    而用户空间对属性的创建时间有严格的要求。
    当一个新的设备在内核中被注册时，会产生一个uevent来通知用户空间（比如udev），一个新的设备是可用的。
    如果属性是在设备注册后添加的，那么用户空间将不会得到通知，用户空间也不会知道新的属性。

    This is important for device driver that need to publish additional attributes for a device at driver probe time.
    If the device driver simply calls device_create_file() on the device structure passed to it, then userspace will never be notified of the new attributes.
    这对于需要在驱动探测时为设备发布额外属性的设备驱动来说非常重要。
    如果设备驱动只是简单地在传递给它的设备结构上调用device_create_file()，那么用户空间将永远不会得到新属性的通知。