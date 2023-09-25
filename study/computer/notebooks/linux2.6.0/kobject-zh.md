## 0.简介
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

## kobject 编程接口

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

## 1.3 sysfs

每个kobject在sysfs中接收一个目录。这个目录在kobject的父目录下创建。

如果一个kobject在注册时没有父对象，它的父对象将成为它的主导kset。

如果一个kobject既没有父kset也没有主kset，那么它的目录将在sysfs分区的顶层创建。这应该只发生在嵌入到struct子系统中的对象上。