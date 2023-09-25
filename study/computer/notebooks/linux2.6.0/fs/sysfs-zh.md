

sysfs - _The_ filesystem for exporting kernel objects. 

Patrick Mochel	<mochel@osdl.org>

10 January 2003


是什么:

	sysfs 是一种基于 ram 的文件系统，最初以 ramfs 为基础。它提供了一种将内核数据结构、其属性以及它们之间的联系导出到用户空间的方法。
	
	sysfs 与 kobject 基础架构有着内在的联系。有关 kobject 接口的更多信息，请阅读 Documentation/kobject.txt。


使用 sysfs:

	sysfs总是会被编译进来。你可以通过以下方法来访问:
    mount -t sysfs sysfs /sys 


文件夹创建

	系统会为每个注册的 kobject 在 sysfs 中创建一个目录。该目录被 kobject 的父目录所创建，向用户空间表达内部对象层次结构。
	sysfs 中的顶级目录代表了对象层次结构的共同祖先; 即对象所属的子系统。
	
	Sysfs 内部会将拥有目录的 kobject 保存在目录的 dentry 的 ->d_fsdata 指针中。 这允许 sysfs 在打开和关闭文件时直接对 kobject 进行引用计数。


属性
~~~~~~~~~~

kobjects 属性可以以文件系统中普通文件的形式导出。通过将文件 I/O 操作传递给为属性定义的方法，Sysfs 提供了一种读写内核属性的方法。

属性应为 ASCII 文本文件，每个文件最好只有一个值。需要注意的是，每个文件只包含一个值可能效率不高，因此社会上可以接受表达同一类型值的数组。

混合类型、表达多行数据以及对数据进行花哨的格式化都是不允许的。做这些事情可能会让你受到公开羞辱，并在不经通知的情况下重写你的代码。


属性定义很简单：

struct attribute {
        char                    * name;
        mode_t                  mode;
};


int sysfs_create_file(struct kobject * kobj, struct attribute * attr);
void sysfs_remove_file(struct kobject * kobj, struct attribute * attr);


A bare attribute contains no means to read or write the value of the
attribute. Subsystems are encouraged to define their own attribute
structure and wrapper functions for adding and removing attributes for
a specific object type. 

For example, the driver model defines struct device_attribute like:

struct device_attribute {
        struct attribute        attr;
        ssize_t (*show)(struct device * dev, char * buf);
        ssize_t (*store)(struct device * dev, const char * buf);
};

int device_create_file(struct device *, struct device_attribute *);
void device_remove_file(struct device *, struct device_attribute *);

It also defines this helper for defining device attributes: 

#define DEVICE_ATTR(_name,_mode,_show,_store)      \
struct device_attribute dev_attr_##_name = {            \
        .attr = {.name  = __stringify(_name) , .mode   = _mode },      \
        .show   = _show,                                \
        .store  = _store,                               \
};

For example, declaring

static DEVICE_ATTR(foo,0644,show_foo,store_foo);

is equivalent to doing:

static struct device_attribute dev_attr_foo = {
       .attr	= {
		.name = "foo",
		.mode = 0644,
	},
	.show = show_foo,
	.store = store_foo,
};


Subsystem-Specific Callbacks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a subsystem defines a new attribute type, it must implement a
set of sysfs operations for forwarding read and write calls to the
show and store methods of the attribute owners. 

struct sysfs_ops {
        ssize_t (*show)(struct kobject *, struct attribute *,char *);
        ssize_t (*store)(struct kobject *,struct attribute *,const char *);
};

[ Subsystems should have already defined a struct kobj_type as a
descriptor for this type, which is where the sysfs_ops pointer is
stored. See the kobject documentation for more information. ]

When a file is read or written, sysfs calls the appropriate method
for the type. The method then translates the generic struct kobject
and struct attribute pointers to the appropriate pointer types, and
calls the associated methods. 


To illustrate:

#define to_dev_attr(_attr) container_of(_attr,struct device_attribute,attr)
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



Reading/Writing Attribute Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To read or write attributes, show() or store() methods must be
specified when declaring the attribute. The method types should be as
simple as those defined for device attributes:

        ssize_t (*show)(struct device * dev, char * buf);
        ssize_t (*store)(struct device * dev, const char * buf);

IOW, they should take only an object and a buffer as parameters. 


sysfs allocates a buffer of size (PAGE_SIZE) and passes it to the
method. Sysfs will call the method exactly once for each read or
write. This forces the following behavior on the method
implementations: 

- On read(2), the show() method should fill the entire buffer. 
  Recall that an attribute should only be exporting one value, or an
  array of similar values, so this shouldn't be that expensive. 

  This allows userspace to do partial reads and seeks arbitrarily over
  the entire file at will. 

- On write(2), sysfs expects the entire buffer to be passed during the
  first write. Sysfs then passes the entire buffer to the store()
  method. 
  
  When writing sysfs files, userspace processes should first read the
  entire file, modify the values it wishes to change, then write the
  entire buffer back. 

  Attribute method implementations should operate on an identical
  buffer when reading and writing values. 

Other notes:

- The buffer will always be PAGE_SIZE bytes in length. On i386, this
  is 4096. 

- show() methods should return the number of bytes printed into the
  buffer. This is the return value of snprintf().

- show() should always use snprintf(). 

- store() should return the number of bytes used from the buffer. This
  can be done using strlen().

- show() or store() can always return errors. If a bad value comes
  through, be sure to return an error.

- The object passed to the methods will be pinned in memory via sysfs
  referencing counting its embedded object. However, the physical 
  entity (e.g. device) the object represents may not be present. Be 
  sure to have a way to check this, if necessary. 


A very simple (and naive) implementation of a device attribute is:

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


(Note that the real implementation doesn't allow userspace to set the 
name for a device.)


Top Level Directory Layout
~~~~~~~~~~~~~~~~~~~~~~~~~~

The sysfs directory arrangement exposes the relationship of kernel
data structures. 

The top level sysfs diretory looks like:

block/
bus/
class/
devices/
firmware/
net/

devices/ contains a filesystem representation of the device tree. It maps
directly to the internal kernel device tree, which is a hierarchy of
struct device. 

bus/ contains flat directory layout of the various bus types in the
kernel. Each bus's directory contains two subdirectories:

	devices/
	drivers/

devices/ contains symlinks for each device discovered in the system
that point to the device's directory under root/.

drivers/ contains a directory for each device driver that is loaded
for devices on that particular bus (this assumes that drivers do not
span multiple bus types).


More information can driver-model specific features can be found in
Documentation/driver-model/. 


TODO: Finish this section.


Current Interfaces
~~~~~~~~~~~~~~~~~~

The following interface layers currently exist in sysfs:


- devices (include/linux/device.h)
----------------------------------
Structure:

struct device_attribute {
        struct attribute        attr;
        ssize_t (*show)(struct device * dev, char * buf);
        ssize_t (*store)(struct device * dev, const char * buf);
};

Declaring:

DEVICE_ATTR(_name,_str,_mode,_show,_store);

Creation/Removal:

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


