## 0. 简介

kobject 基础架构执行基本的对象管理，大型数据结构和子系统可以利用这些管理，而不是重新实现类似的功能。这些功能主要涉及:
- 对象引用计数。
- 维护对象列表（集）。
- 对象集上锁。
- 用户空间显示。

该基础架构由许多对象类型组成，以支持这些功能。下文将详细介绍这些对象的编程接口，此处将作简要介绍：
- kobjects  一个简单的对象。
- kset  某种类型的一组对象。
- ktype  一种通用类型对象的辅助工具集。
- subsystem  一个控制多个 ksets 的对象。

kobject 基础架构与 sysfs 文件系统关系密切。每个在 kobject 核心注册的 kobject 都会在 sysfs 中获得一个目录。然后就可以导出 kobject 的属性。更多信息请参阅 Documentation/filesystems/sysfs.txt。

kobject 基础架构提供了灵活的编程接口、
并允许在未注册的情况下使用 kobjects 和 ksets（即不使用 sysfs 表示）。下文将对此进行介绍。

## 1.1 描述

Struct kobject是一种简单的数据类型，它为更复杂的对象类型提供了基础。它提供了几乎所有复杂数据类型共享的一组基本字段。kobjects旨在嵌入到较大的数据结构中，并替换它们重复的字段。

## 1.2 定义
```c
struct kobject {
	char			name[KOBJ_NAME_LEN];
	atomic_t		refcount;
	struct list_head	entry;
	struct kobject		* parent;
	struct kset		    * kset;
	struct kobj_type	* ktype;
	struct dentry		* dentry;
};

void kobject_init(struct kobject *);
int kobject_add(struct kobject *);
int kobject_register(struct kobject *);

void kobject_del(struct kobject *);
void kobject_unregister(struct kobject *);

struct kobject * kobject_get(struct kobject *);
void kobject_put(struct kobject *);
```

## 1.3 kobject 编程接口

可以使用kobject_register()和kobject_unregister()动态地从kobject内核中添加和删除Kobjects。注册包括将kobject插入到它的主kset列表中，并在sysfs中为它创建一个目录。

或者，您可以使用kobject，而不将其添加到kset列表或通过sysfs导出它，只需调用kobject_init()。稍后可以通过调用kobject_add()将初始化的kobject添加到对象层次结构中。初始化的kobject可以用于引用计数。

注意:调用kobject_init()然后调用kobject_add()在功能上等同于调用kobject_register()。

当一个kobject被注销时，它将从它的kset列表中删除，从sysfs文件系统中删除，并且它的引用计数减少。列表和sysfs的删除发生在kobject_del()中，并且可以手动调用。Kobject_put()减少引用计数，也可以手动调用。

kobject的引用计数可以用kobject_get()递增，它返回一个对kobject的有效引用;并使用kobject_put()自减。对象的引用计数只有在已经为正的情况下才能增加。

当kobject的引用计数达到0时，调用方法struct kobj_type::release() (kobject的kset指向它)。这允许释放为对象分配的任何内存。

请注意! !


如果使用kobject引用计数，则必须为动态分配的kobject提供析构函数来释放它们。引用计数控制对象的生存期。如果它变为0，则假定该对象将被释放，无法使用。

更重要的是，您必须在那里释放对象，而不是在取消注册调用之后立即释放对象。如果其他人正在引用该对象(例如通过sysfs文件)，他们将获得对该对象的引用，假设它是有效的并对其进行操作。如果该对象未注册并在此期间释放，则该操作将引用释放的内存并爆炸。

在最简单的情况下，可以通过定义一个释放方法并从中释放对象来防止这种情况。注意，这不会保护引用计数/对象管理模型，这些模型使用双引用计数或使用引用计数做其他奇怪的事情(如网络层)。

## 1.4 sysfs

每个 kobject 都会在 sysfs 中获得一个目录。该目录在 kobject 的父目录下创建。

如果一个kobject在注册时没有父对象，它的父对象将成为它的主导kset。

如果一个kobject既没有父kset也没有主kset，那么它的目录将在sysfs分区的顶层创建。这应该只发生在嵌入到struct子系统中的对象上。

# 2 ksets
## 2.1 描述

kset 是嵌入同一类型的 kobjects 的集合。
```c
struct kset {
	struct subsystem	* subsys;
	struct kobj_type	* ktype;
	struct list_head	list;
	struct kobject		kobj;
};

void kset_init(struct kset * k);
int kset_add(struct kset * k);
int kset_register(struct kset * k);
void kset_unregister(struct kset * k);

struct kset * kset_get(struct kset * k);
void kset_put(struct kset * k);

struct kobject * kset_find_obj(struct kset *, char *);
```

kobject 嵌入的类型由 ktype 指针描述。kobject 所属的子系统由 subsys 指针指向。

kset 本身包含一个 kobject，这意味着它可以在 kobject 层次结构中注册，并通过 sysfs 导出。更重要的是，kset 可以嵌入到更大的数据类型中，也可以是（该对象类型的）另一个 kset 的一部分。

例如，块设备是一个object（struct gendisk），包含在一组块设备中。它还可能包含在该设备上发现的一组分区（struct hd_struct）。下面的代码片段说明了如何正确表达这一点。
```c
	 struct gendisk * disk;
	 ...
	 disk->kset.kobj.kset = &block_kset;
	 disk->kset.ktype = &partition_ktype;
	 kset_register(&disk->kset);
```
- 磁盘嵌入对象所属的 kset 是 block_kset，由 disk->kset.kobj.kset 指向。

- 磁盘_subordinate_列表中的对象类型是分区，在 disk->kset.ktype 中设置。

- 然后注册 kset，处理初始化并将嵌入的 kobject 添加到层次结构中。

## 2.2 kset 编程接口

除了 kset_find_obj()，所有 kset 函数在执行完 kset 特定操作后，最终都会将调用转发给内嵌的 kobjects。ksets 提供了与 kobjects 类似的编程模型：它们可以在初始化后使用，而无需在层次结构中注册。

kset_find_obj() 可用于查找具有特定名称的 kobject。如果找到，将返回该 kobject。

## 2.3 sysfs

ksets 在其嵌入的 kobjects 注册时会在 sysfs 中表示。它们遵循相同的父级规则，但有一个例外。如果一个 kset 没有父系统，其嵌入的 kobject 也不是另一个 kset 的一部分，那么该 kset 的父系统就会成为它的主导subsystem。

如果 kset 没有父节点，则会在 sysfs 根目录下创建其目录。只有当注册的 kset 嵌入 subsystem 时，才会出现这种情况。

# 3 struct ktype
## 3.1 描述
```c
struct kobj_type {
	void (*release)(struct kobject *);
	struct sysfs_ops	* sysfs_ops;
	struct attribute	** default_attrs;
};
```
结构 kobj_type 提供了特定于对象的字段，这些字段包括

- release： 当 kobject 的引用计数达到 0 时调用，将对象转换为更复杂的类型并释放。

- sysfs_ops： 为 sysfs 访问提供转换函数。更多信息请参阅 sysfs 文档。

- default_attrs： 对象注册时通过 sysfs 导出的默认属性。请注意，最后一个属性必须初始化为 NULL！您可以在 drivers/block/genhd.c 中找到完整的实现。

struct kobj_type 的实例不会被注册，只会被 kset 引用。一个 kobj_type 可以被任意数量的 ksets 引用，因为可能存在不同的相同对象集。

# 4 subsystems
## 4.1 描述

子系统代表一个重要的代码实体，它维护着任意数量的各种类型的对象集。由于 ksets 的数量及其包含的对象类型是可变的，因此子系统的通用表示方法是最简单的。
```c
struct subsystem {
	struct kset		kset;
	struct rw_semaphore	rwsem;
};

int subsystem_register(struct subsystem *);
void subsystem_unregister(struct subsystem *);

struct subsystem * subsys_get(struct subsystem * s);
void subsys_put(struct subsystem * s);
```

子系统包含一个嵌入式 kset：

- 它可以通过 kset 的嵌入式 kobject 在对象层次结构中表示。

- 它可以维护一个类型对象的默认列表。

其他 ksets 只需在注册前引用子系统，就可以附加到子系统上（这种单向引用意味着无法确定附加到子系统上的 ksets）。(这种单向引用意味着无法确定附加到子系统的 ksets）。

连接到子系统的所有 ksets 都共享子系统的 R/W semaphore。

## 4.2 subsystem 编程接口

子系统编程接口很简单，不像 kset 和 kobject 编程接口那样灵活。它们可以被注册和取消注册，也可以被引用计数。每次调用都会将调用转发给其嵌入的 ksets（ksets 会将调用转发给其嵌入的 kobjects）。

## 4.3 辅助函数

为了更方便地处理subsystems及其嵌入objects，我们提供了许多宏。

```c
decl_subsys(name,type)

// 声明一个名为"<name>_subsys "的子系统，内嵌类型为 <type> 的 kset。例如 

decl_subsys(devices,&ktype_devices);

// 就等于：

struct subsystem device_subsys = {
       .kset = {
	     .kobj = {
		   .name = "devices",
	     },
	     .ktype = &ktype_devices,
	}
}; 
```

使用子系统默认列表注册的对象必须正确设置其 kset ptr。这些对象可能嵌入了 kobjects、ksets 或其他子系统。下面的帮助程序可以简化 kset 的设置： 

```c
kobj_set_kset_s(obj,subsys)

//- 假设 obj->kobj 存在，并且是一个 kobject 结构。
//- 将该 kobject 的 kset 设置为子系统的嵌入式 kset。

kset_set_kset_s(obj,subsys)

//- 假设 obj->kset 存在，并且是结构 kset。
//- 将嵌入 kobject 的 kset 设置为子系统的嵌入 kset。

subsys_set_kset(obj,subsys)

//- 假设 obj->subsys 存在，并且是结构子系统。
//- 将 obj->subsys.kset.kobj.kset 设置为子系统的嵌入式 kset。
```

## 4.4 sysfs

子系统在 sysfs 中通过嵌入的 kobjects 表示。它们遵循前面提到的相同规则，没有例外。它们通常会在 sysfs 中接收一个顶级目录，除非它们的嵌入 kobject 是另一个 kset 的一部分，或者嵌入 kobject 的父级被明确设置。

请注意，子系统的嵌入式 kset 必须 "附加 "到子系统本身，才能使用其 rwsem。这需要在调用 kset_add() 之后完成。而不是在调用 kset_add() 之前，因为如果子系统还没有默认父节点，则 kset_add() 会使用子系统作为默认父节点）。
